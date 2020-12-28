all: test_client

test_client: binderAddInts.cpp
	g++ -O3 -std=c++11 -o $@ -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 $< testUtil.c -lpthread -lbinder
	#g++ -O0 -g -std=c++11 -o $@ -I../libs/include -I.. -L../libs -DHAVE_PTHREADS -DHAVE_SYS_UIO_H -DHAVE_ENDIAN_H -DHAVE_ANDROID_OS=1 $< testUtil.c -lpthread -lbinder

clean:
	rm -f test_client