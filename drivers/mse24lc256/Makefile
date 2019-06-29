ifneq ($(KERNELRELEASE),)
obj-m := mse24lc256.o
else
KDIR := /opt/linux-kernel-labs/src/linux
all:
	$(MAKE) -C $(KDIR) M=$$PWD
endif
