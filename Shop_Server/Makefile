ROOT := $(shell pwd)
INCLUDE := $(ROOT)/include
SRC := $(ROOT)/src

USR_SUB_DIR := $(SRC) 

default:usr

usr:
	@for n in $(USR_SUB_DIR); do $(MAKE) -C $$n ; done

clean:
	@for n in $(USR_SUB_DIR); do $(MAKE) -C $$n clean; done
