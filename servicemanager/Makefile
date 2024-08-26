TARGET = servicemanager

CFLAGS = -I.. -O3
#CFLAGS = -I.. -O0 -g

%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

$(TARGET): binder.o service_manager.o
	gcc $^ -o $@

all: $(TARGET)

clean:
	rm -f *.o $(TARGET)
