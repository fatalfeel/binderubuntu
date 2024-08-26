TARGET = libbinder.a

include cutils/Makefile
include utils/Makefile
include binder/Makefile

CFLAGS = -O3 -I.. -I./include -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 -std=c++11
#CFLAGS = -O0 -g -I.. -Iinclude -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 -std=c++11

%.o: %.cpp
	gcc -c $(CFLAGS) $< -o $@
%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

$(TARGET): $(objects)
	ar cr $@ $^

all: $(TARGET)

clean:
	rm -f libbinder.a `find -name \*.o`
