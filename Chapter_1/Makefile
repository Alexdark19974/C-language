.PHONY: all clean
DIRS := $(shell find 1.* -maxdepth 0 -type d)

all:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) script && $(MAKE) -C $(var) all && ) true	
clean:
	$(foreach var, $(DIRS), $(MAKE) -C $(var) clean && ) true
