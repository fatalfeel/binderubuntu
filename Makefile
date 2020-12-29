SUBDIRS := driver/ashmem driver/binder libs servicemanager test_client test_server

all:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -j8 -C $$dir -f Makefile all; \
		echo make $$dir done; echo; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -j8 -C $$dir -f Makefile clean; \
		echo clean $$dir done; echo; \
	done

.PHONY: all clean
