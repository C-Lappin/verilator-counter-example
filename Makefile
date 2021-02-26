.PHONY: all
all: counter_tb

VERILATOR=verilator
VERILATOR_ROOT ?= $(shell bash -c 'verilator -V|grep VERILATOR_ROOT | head -1 | sed -e "s/^.*=\s*//"')
VINC := $(VERILATOR_ROOT)/include

obj_dir/Vcounter.cpp: ./rtl/counter.v
	$(VERILATOR) --trace -Wall -cc ./rtl/counter.v

obj_dir/Vcounter__ALL.a: obj_dir/Vcounter.cpp
	make --no-print-directory -C obj_dir -f Vcounter.mk

counter_tb: ./csrc/counter.cpp obj_dir/Vcounter__ALL.a
	g++ -I$(VINC) -I obj_dir $(VINC)/verilated.cpp		\
		$(VINC)/verilated_vcd_c.cpp ./csrc/counter.cpp	\
		obj_dir/Vcounter__ALL.a -o counter_tb

.PHONY: clean
clean:
	rm -rf obj_dir/ counter/ counter_tb counter_output.vcd
