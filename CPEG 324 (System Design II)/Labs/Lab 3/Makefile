
GHDL = ghdl-0.33-x86_64-linux/bin/ghdl
COMP = -a --ieee=standard
EXE = -e --ieee=standard
RUN = -r


default: run-Calc

Calc:
	$(GHDL) $(COMP) regFile.vhdl
	$(GHDL) $(COMP) clock-filter.vhdl
	$(GHDL) $(COMP) add-sub.vhdl
	$(GHDL) $(COMP) Calc.vhdl
	$(GHDL) $(COMP) Calc_tb.vhdl
	$(GHDL) $(EXE) Calc_tb

run-Calc: Calc

	$(GHDL) $(RUN) Calc_tb

dump-calculator_tb: Calc
	$(GHDL) $(RUN) Calc_tb --vcd=Calc_tb.vcd

clean:
	rm -f *.o *.cf *.out *.vcd

