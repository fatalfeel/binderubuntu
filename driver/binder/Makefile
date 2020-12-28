ccflags-y += -O3 -I$(src) -Wno-int-conversion -DCONFIG_ANDROID_BINDER_DEVICES="\"binder\""
obj-m := binder_linux.o
binder_linux-y := deps.o binder.o

KERNEL_SRC ?= /lib/modules/$(shell uname -r)/build

all:
	$(MAKE) -C $(KERNEL_SRC) V=1 M=$$PWD

install:
	cp binder_linux.ko $(DESTDIR)/

clean:
	rm -rf deps.h *.a *.o *.ko *.mod *.mod.c *.symvers *.order .*.cmd .tmp_versions
