ifneq ($(KERNELRELEASE),)
obj-m := hello_version.o
else
KDIR := /opt/linux-kernel-labs/src/linux
all:
	$(MAKE) -C $(KDIR) M=$$PWD
endif
