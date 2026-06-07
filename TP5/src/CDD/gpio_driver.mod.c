#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xdee352ff, "__platform_driver_register" },
	{ 0xdf237453, "timer_shutdown_sync" },
	{ 0x3665a943, "device_destroy" },
	{ 0x09474a06, "class_destroy" },
	{ 0x6d86443f, "cdev_del" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x92997ed8, "_printk" },
	{ 0x15ba50a6, "jiffies" },
	{ 0xc38c83b8, "mod_timer" },
	{ 0x77613bf4, "gpiod_get_value" },
	{ 0x08778b8f, "devm_gpiod_get" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0x47c11e94, "cdev_init" },
	{ 0xee983164, "cdev_add" },
	{ 0xc1c92698, "class_create" },
	{ 0x397131a4, "device_create" },
	{ 0xf9ddb5d9, "timer_init_key" },
	{ 0xdbd4b560, "platform_driver_unregister" },
	{ 0x656e4a6e, "snprintf" },
	{ 0x6cbbfc54, "__arch_copy_to_user" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x12a4e128, "__arch_copy_from_user" },
	{ 0xdcb764ad, "memset" },
	{ 0x91d66ee9, "module_layout" },
};

MODULE_INFO(depends, "");

MODULE_ALIAS("of:N*T*Cthe-pipeliners,gpio-driver");
MODULE_ALIAS("of:N*T*Cthe-pipeliners,gpio-driverC*");

MODULE_INFO(srcversion, "F454391F91E782C61C6B1CB");
