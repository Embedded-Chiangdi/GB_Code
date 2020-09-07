.PHONY : clean all
KERN_VERSION := $(shell uname -r)
KERNDIR := /lib/modules/$(KERN_VERSION)/build
PWD := $(shell pwd)
obj-m := writebuf.o
all:
	make -C $(KERNDIR) M=$(PWD)  modules
	gcc app.c -o app
clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm app
