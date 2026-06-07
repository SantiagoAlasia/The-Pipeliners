obj-m += gpio_driver.o

KDIR := /home/santiagoalasia/linux-rpi618
PWD  := $(shell pwd)

RPI_USER_IP := santiagoalasia@raspberrypi.local
RPI_DEST_DIR := /home/santiagoalasia/Documentos/TP5-SdC/CDD

all:
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KDIR) M=$(PWD) modules


deploy: all
	@echo "=============================================="
	@echo "Enviando gpio_driver.ko a la Raspberry Pi ... "
	@echo "=============================================="

	scp gpio_driver.ko $(RPI_USER_IP):$(RPI_DEST_DIR)

clean:
	make ARCH=arm64 CROSS_COMPILE=aarch64-linux-gnu- -C $(KDIR) M=$(PWD) clean