#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>       
#include <linux/cdev.h>     
#include <linux/device.h>   
#include <linux/uaccess.h> 
#include <linux/timer.h> 
#include <linux/jiffies.h>
#include <linux/platform_device.h> 
#include <linux/gpio/consumer.h>   
#include <linux/of.h>        

#define DEVICE_NAME "gpio_driver"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Grupo: The-Pipeliners");
MODULE_DESCRIPTION("Character Device Driver for GPIO signal acquisition");
MODULE_VERSION("5.0");

static dev_t dev_num;
static struct cdev gpio_driver_cdev;
static struct class *gpio_driver_class;

static struct timer_list mi_timer;

static int sensor_actual = 1;
static int lectura_sensor = 0;

static struct gpio_desc *desc_sensor1 = NULL;
static struct gpio_desc *desc_sensor2 = NULL;


/* Timer callback: 20 Hz */
static void mi_timer_callback(struct timer_list *t)
{
    if (sensor_actual == 1 && desc_sensor1) {
        lectura_sensor = gpiod_get_value(desc_sensor1);
    } else if (sensor_actual == 2 && desc_sensor2) {
        lectura_sensor = gpiod_get_value(desc_sensor2);
    }

    mod_timer(&mi_timer, jiffies + msecs_to_jiffies(50));
}

/* READ */
static ssize_t my_read(struct file *file, char __user *buffer, size_t len, loff_t *offset)
{
    char msg[16];
    int msg_len;

    if (*offset > 0) return 0;

    msg_len = snprintf(msg, sizeof(msg), "%d\n", lectura_sensor);
    if (copy_to_user(buffer, msg, msg_len)) return -EFAULT;

    *offset += msg_len;
    return msg_len;
}

/* WRITE */
static ssize_t my_write(struct file *file, const char __user *buffer, size_t len, loff_t *offset)
{
    char kbuffer[10];

    if (len > sizeof(kbuffer) - 1) len = sizeof(kbuffer) - 1;
    if (copy_from_user(kbuffer, buffer, len)) return -EFAULT;
   
    kbuffer[len] = '\0';

    if (kbuffer[0] == '1') {
        sensor_actual = 1;
        printk(KERN_INFO "gpio_driver: Se selecciono Sensor 1\n");
    } else if (kbuffer[0] == '2') {
        sensor_actual = 2;
        printk(KERN_INFO "gpio_driver: Se selecciono Sensor 2\n");
    }
    else
    {
        printk(KERN_WARNING "gpio_driver: Comando invalido recibido\n");
    }

    return len;
}

/* OPEN */
static int my_open(struct inode *inode, struct file *file)
{
    //printk(KERN_INFO "gpio_driver: Dispositivo abierto\n");
    return 0;
}

/* RELEASE */
static int my_release(struct inode *inode, struct file *file)
{
    //printk(KERN_INFO "gpio_driver: Dispositivo cerrado\n");
    return 0;
}

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write,
};

static int gpio_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    struct device *my_device;
    int ret;

    printk(KERN_INFO "gpio_driver: Probe ejecutado. Buscando labels en DTS...\n");

    desc_sensor1 = devm_gpiod_get(dev, "sensor1", GPIOD_IN);
    if (IS_ERR(desc_sensor1)) {
        printk(KERN_ERR "gpio_driver: No se pudo mapear la linea del Sensor 1\n");
        return PTR_ERR(desc_sensor1);
    }

    desc_sensor2 = devm_gpiod_get(dev, "sensor2", GPIOD_IN);
    if (IS_ERR(desc_sensor2)) {
        printk(KERN_ERR "gpio_driver: No se pudo mapear la linea del Sensor 2\n");
        return PTR_ERR(desc_sensor2);
    }

    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) return ret;

    cdev_init(&gpio_driver_cdev, &fops);
    ret = cdev_add(&gpio_driver_cdev, dev_num, 1);
    if (ret < 0) goto Error_Chrdev;

    gpio_driver_class = class_create(DEVICE_NAME);
    if (IS_ERR(gpio_driver_class)) goto Error_Cdev;

    my_device = device_create(gpio_driver_class, NULL, dev_num, NULL, DEVICE_NAME);
    if (IS_ERR(my_device)) goto Error_Class;

    timer_setup(&mi_timer, mi_timer_callback, 0);
    mod_timer(&mi_timer, jiffies + msecs_to_jiffies(50));

    printk(KERN_INFO "gpio_driver: Pines mapeados y driver activo.\n");
    return 0;

Error_Class: class_destroy(gpio_driver_class);
Error_Cdev: cdev_del(&gpio_driver_cdev);
Error_Chrdev: unregister_chrdev_region(dev_num, 1);
    return -1;
}

static void gpio_remove(struct platform_device *pdev)
{
    timer_shutdown_sync(&mi_timer);
    device_destroy(gpio_driver_class, dev_num);
    class_destroy(gpio_driver_class);
    cdev_del(&gpio_driver_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "gpio_driver: Modulo removido.\n");
}

/* Enlace de compatibilidad con el Device Tree */
static const struct of_device_id tp_gpio_of_match[] = {
    { .compatible = "the-pipeliners,gpio-driver", },
    { }
};
MODULE_DEVICE_TABLE(of, tp_gpio_of_match);

/* Registro de Plataforma */
static struct platform_driver tp_gpio_platform_driver = {
    .probe = gpio_probe,
    .remove = gpio_remove,
    .driver = {
        .name = "tp_platform_gpio",
        .of_match_table = tp_gpio_of_match,
    },
};

module_platform_driver(tp_gpio_platform_driver);