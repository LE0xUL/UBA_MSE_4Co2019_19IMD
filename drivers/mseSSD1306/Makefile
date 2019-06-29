ifneq ($(KERNELRELEASE),)
obj-m := mseSSD1306.o
else
KDIR := /opt/linux-kernel-labs/src/linux
all:
	$(MAKE) -C $(KDIR) M=$$PWD
endif
