--Created By Shane Cincotta 5/7/19

library ieee;
use ieee.std_logic_1164.all;
use std.textio.all;


entity Calc_tb is
end entity Calc_tb;

architecture structural of Calc_tb is

component Calc is
  port(
    I : in std_logic_vector(7 downto 0); --instruction input
    clk : in std_logic
  );
end component Calc;

signal clk : std_logic; --clock sig
signal I : std_logic_vector(7 downto 0); --instruction input


begin
    Calc_0 : Calc port map(I, clk);

    process
      variable instruction_line : line;
      variable intruction_vector : bit_vector(7 downto 0);
      file testBenchCode : text is in "testbench.txt"; --txt file containing the instructions to run in binary
    begin
      while (not(endfile(testBenchCode))) loop --Loop over the instructions
        clk <= '0';
        readline(testBenchCode, instruction_line); --Read in instruction from testbench.txt
        read(instruction_line, intruction_vector); 
        I <= to_stdlogicvector(intruction_vector); --Pass instruction to the Calc input as logic vector

        wait for 1 ns;
        clk <= '1';
        wait for 1 ns;
      end loop;
      wait;
    end process;
end architecture structural;