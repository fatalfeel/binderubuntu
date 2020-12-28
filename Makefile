SUBDIRS := driver/ashmem driver/binder libs servicemanager test_client test_server

.PHONY: all clean

all clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir -f Makefile $@; \
	done
