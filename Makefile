VSRCS = $(shell find ./vsrc -name "*.v")

all:
	@echo "Write this Makefile by your self."

sim:
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	verilator -Wall --cc $(VSRCS) --top-module npc --exe ./csrc/sim_main.cpp

run:
	make -C obj_dir -f Vnpc.mk Vnpc
	./obj_dir/Vnpc

del:
	rm -rf obj_dir

include ../Makefile
