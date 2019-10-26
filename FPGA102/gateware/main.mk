
all: $(PROJ).rpt $(PROJ).bin

%.blif: %.v $(ADD_SRC) $(ADD_DEPS)
	yosys -ql $*.log -p 'synth_ice40 -top top -blif $@' $< $(ADD_SRC)

%.json: %.v $(ADD_SRC) $(ADD_DEPS)
	yosys -ql $*.log -p 'synth_ice40 -top top -json $@' $< $(ADD_SRC)

ifeq ($(USE_ARACHNEPNR),)
%.asc: $(PIN_DEF) %.json
	nextpnr-ice40 -q --$(DEVICE) --json $(filter-out $<,$^) --pcf $< --asc $@ --package sg48
else
%.asc: $(PIN_DEF) %.blif
	arachne-pnr -d $(subst up,,$(subst hx,,$(subst lp,,$(DEVICE)))) -o $@ -p $^
endif

%.bin: %.asc
	icepack $< $@
	icebox_stat $(PROJ).asc

%.rpt: %.asc
	icetime -d $(DEVICE) -mtr $@ $<

%_tb: %_tb.v %.v
	iverilog -o $@ $^

%_tb.vcd: %_tb
	vvp -N $< +vcd=$@

%_syn.v: %.blif
	yosys -p 'read_blif -wideports $^; write_verilog $@'

%_syntb: %_tb.v %_syn.v
	iverilog -o $@ $^ `yosys-config --datdir/ice40/cells_sim.v`

%_syntb.vcd: %_syntb
	vvp -N $< +vcd=$@

prog: $(PROJ).bin
	iceprog $<

sudo-prog: $(PROJ).bin
	@echo 'Executing prog as root!!!'
	sudo iceprog $<

simulate:
	iverilog -Wall -o sim/$(PROJ)_tb $(PROJ)_tb.v
	vvp sim/$(PROJ)_tb -lxt2
	mv $(PROJ)_tb.lxt sim/$(PROJ)_tb.lxt
	gtkwave sim/$(PROJ)_tb.lxt sim/gtkwaveConfig.gtkw

new: 
	cp -r blink $(NAME) && cd $(NAME) && \
	find ./ -type f -exec sed -i 's/blink/$(NAME)/' * \; && \
	rename 's/blink/$(NAME)/' *.v
	
clean:
	rm -f $(PROJ).blif $(PROJ).asc $(PROJ).rpt $(PROJ).bin $(PROJ).json $(PROJ).log sim/$(PROJ)_tb sim/$(PROJ)_tb.lxt $(ADD_CLEAN)

.SECONDARY:
.PHONY: all prog clean
