obj-m := hello.o

KDIR := /opt/linux-kernel-labs/src/linux 
PWD := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
