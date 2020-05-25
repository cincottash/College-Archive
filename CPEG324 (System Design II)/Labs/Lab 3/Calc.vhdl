--Created By Shane Cincotta 5/7/19

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

-- -------------------------------------------------------------------
--Calc entity

entity Calc is
  port(
    I : in std_logic_vector(7 downto 0); --instruction input
    clk : in std_logic
  );
end entity Calc;

-- -------------------------------------------------------------------
--Calc architecture

architecture structural of Calc is
  component add-sub is
      port(
          in_1, in_2 : in std_logic_vector(7 downto 0); --in_1 and in_2 are the operands
          mode_sel : in std_logic; --controls if Were doing addition or subtraction, 0 if addition, 1 if subtraction
          total : out std_logic_vector(7 downto 0)
        );
  end component add-sub;

  component regFile is
    port(
      RD : in std_logic_vector(1 downto 0);
      RS : in std_logic_vector(1 downto 0);
      RT : in std_logic_vector(1 downto 0);
      Write_Data : in std_logic_vector(7 downto 0);
      CLK : in std_logic;
      Write_Enable : in std_logic;
      RS_DATA : out std_logic_vector(7 downto 0);
      RT_DATA : out std_logic_vector(7 downto 0)
    );
  end component regFile;

  component clk_filter is
    port(
      clk_in : in std_logic;
      clk_out : out std_logic;
      S: in std_logic;
      skip: in std_logic
    );
  end component clk_filter;


signal RS, RT, RD : std_logic_vector(1 downto 0); --2 bits to represent our 4 registers
signal filtered_clk, Write_Enable, display, WD_sel, skip, skip_compare : std_logic;
signal Write_Data, RS_DATA, RT_DATA, extended_immediate, ALU_OUTPUT: std_logic_vector(7 downto 0);


begin
  regFile_0 : regFile port map(RS, RT, RD, Write_Data, filtered_clk, Write_Enable, RS_DATA, RT_DATA);
  ALU: add-sub port map(RS_DATA, RT_DATA, I(7), ALU_OUTPUT);
  clk_filter_0 : clk_filter port map(clk, filtered_clk, I(4), skip);

  --Making control signals (see data path)
  RD <= I(5 downto 4);
  RT <= I(1 downto 0);
  

  display <= not (I(7) or I(6) or I(5)); --Used for printing contents of register

  with display select RS <=
    I(3 downto 2) when '0',
    I(4 downto 3) when others;

  --Make immediate sign extended
  extended_immediate(3 downto 0) <= I(3 downto 0);
  with I(3) select extended_immediate(7 downto 4) <=
    "1111" when '1',
    "0000" when others;

  WD_sel <= not(I(7) and I(6));
  with WD_sel select Write_Data <=
    extended_immediate when '0', --sign extended value written to RD
    ALU_OUTPUT when others; --ALU result written to RD

  --Write Data is written to RD if instruction is add, sub or LI
  Write_Enable <= I(7) or I(6);

  --checks opcode and skip bit
  skip <= (not I(7)) and (not I(6)) and I(5) and skip_compare;

  --Compare registers to determine if Write_Enable should skip or not
  skip_compare <= (RS_DATA(7) xnor RT_DATA(7)) and
            (RS_DATA(6) xnor RT_DATA(6)) and
            (RS_DATA(5) xnor RT_DATA(5)) and
            (RS_DATA(4) xnor RT_DATA(4)) and
            (RS_DATA(3) xnor RT_DATA(3)) and
            (RS_DATA(2) xnor RT_DATA(2)) and
            (RS_DATA(1) xnor RT_DATA(1)) and
            (RS_DATA(0) xnor RT_DATA(0)
            );


  --Prints value to display
  process(filtered_clk, display) is
    variable value : integer;
    begin
      if((filtered_clk'event and filtered_clk = '1') and (display = '1')) then
        value := to_integer(signed(RS_DATA));
        report integer'image(value) severity note; --print the value
      end if;
  end process;
end architecture structural;
-- -------------------------------------------------------------------

