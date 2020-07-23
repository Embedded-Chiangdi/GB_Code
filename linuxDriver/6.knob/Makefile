.PHONY : clean all
KERN_VERSION := $(shell uname -r)
KERNDIR := /lib/modules/$(KERN_VERSION)/build
PWD := $(shell pwd)
obj-m := knob.o
all:
	make -C $(KERNDIR) M=$(PWD)  modules
	gcc app.c -o test
clean:
	make -C $(KERNDIR) M=$(PWD) clean
	rm test
