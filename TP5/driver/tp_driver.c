#include <linux/module.h>   
#include <linux/kernel.h>   
#include <linux/init.h>     

// Función que se ejecuta cuando el módulo se carga
static int __init tp_driver_init(void)
{
    printk(KERN_INFO "tp_driver: modulo cargado correctamente\n");
    return 0;
}

// Función que se ejecuta cuando el módulo se descarga
static void __exit tp_driver_exit(void)
{
    printk(KERN_INFO "tp_driver: modulo descargado correctamente\n");
}

// Registrar funciones de inicio y salida
module_init(tp_driver_init);
module_exit(tp_driver_exit);

// Información del módulo
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Tu Nombre");
MODULE_DESCRIPTION("Primer modulo kernel para TP");
MODULE_VERSION("1.0");