#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

#include <linux/fs.h>       
#include <linux/cdev.h>     
#include <linux/device.h>   
#include <linux/uaccess.h> 

#define DEVICE_NAME "tp_driver"

static dev_t dev_num;
static struct cdev tp_cdev;
static struct class *tp_class;

// Operaciones
static ssize_t my_read(struct file *file,
                       char __user *buffer,
                       size_t len,
                       loff_t *offset)
{
    char msg[] = "Hola desde kernel space\n";
    int msg_len = strlen(msg);

    /* Evitar lectura infinita */
    if (*offset >= msg_len)
    {
        return 0;
    }

    /* Copiar datos a user-space */
    if (copy_to_user(buffer, msg, msg_len))
    {
        return -EFAULT;
    }

    *offset += msg_len;

    printk(KERN_INFO "tp_driver: lectura realizada\n");

    return msg_len;
}

static int my_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "tp_driver: dispositivo abierto\n");
    return 0;
}

static int my_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "tp_driver: dispositivo cerrado\n");
    return 0;
}

// File operations
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
};

// Init del modulo
static int __init tp_driver_init(void)
{
    int ret;

    printk(KERN_INFO "tp_driver: iniciando modulo\n");

    /* Reservar major/minor */
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);

    if (ret < 0)
    {
        printk(KERN_ALERT "tp_driver: error al registrar dispositivo\n");
        return ret;
    }

    printk(KERN_INFO "tp_driver: major=%d minor=%d\n",
           MAJOR(dev_num), MINOR(dev_num));

    /* Inicializar cdev */
    cdev_init(&tp_cdev, &fops);

    /* Agregar cdev al kernel */
    ret = cdev_add(&tp_cdev, dev_num, 1);

    if (ret < 0)
    {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "tp_driver: error al agregar cdev\n");
        return ret;
    }

    /* Crear clase */
    tp_class = class_create(DEVICE_NAME);

    if (IS_ERR(tp_class))
    {
        cdev_del(&tp_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ALERT "tp_driver: error al crear clase\n");
        return PTR_ERR(tp_class);
    }

    /* Crear dispositivo en /dev */
    device_create(tp_class, NULL, dev_num, NULL, DEVICE_NAME);

    printk(KERN_INFO "tp_driver: modulo cargado correctamente\n");

    return 0;
}

// Exit del modulo
static void __exit tp_driver_exit(void)
{
    device_destroy(tp_class, dev_num);

    class_destroy(tp_class);

    cdev_del(&tp_cdev);

    unregister_chrdev_region(dev_num, 1);

    printk(KERN_INFO "tp_driver: modulo descargado correctamente\n");
}

module_init(tp_driver_init);
module_exit(tp_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Character Device Driver basico");
MODULE_VERSION("1.0");