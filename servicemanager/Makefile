all: servicemanager 

servicemanager: binder.o service_manager.o
	gcc -o $@ $^

clean:
	rm -f *.o servicemanager
	
%.o: %.c
	gcc -O3 -I.. $(CFLAGS) -c -o $@ $<
	#gcc -O0 -g -I.. $(CFLAGS) -c -o $@ $<