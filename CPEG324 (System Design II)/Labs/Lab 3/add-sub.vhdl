--Created by Shane Cincotta 5/6/19
--8 Bit Adder/Subtractor

library ieee;
use ieee.std_logic_1164.all;

-- ----------------------------------------------------------------------
--add-sub entity

entity add-sub is
    port(in_1, in_2 : in std_logic_vector(7 downto 0); --in_1 and in_2 are the operands
        mode_sel : in std_logic; --controls if we're doing addition or subtraction, 0 if addition, 1 if subtraction
        total : out std_logic_vector(7 downto 0)); --result of doing the addition or subtraction
end entity add-sub;

-- ----------------------------------------------------------------------
--add-sub architecture

architecture structural of add-sub is
component 8bit-adder is
    port(in_1, in_2 : in std_logic_vector(7 downto 0); --8-bit inputs
         total : out std_logic_vector(7 downto 0)); --8bit output
end component 8bit-adder;


signal second_term, in_2_inverse, in_2_negative : std_logic_vector(7 downto 0); --make signals
constant one : std_logic_vector(7 downto 0) := "00000001"; --used for 2's compliment


begin
  8bit-adder_0: 8bit-adder port map(in_1, second_term, total); --Preform the addition

  8bit-adder_1: 8bit-adder port map(in_2_inverse, one, in_2_negative); -- Used for flipping sign of second term.

  in_2_inverse <= not(in_2);

  with mode_sel select second_term <=
      in_2 when '0', --If mode_sel is 0, we just do regular addition with the two inputs
      in_2_negative when others; --if mode_sel is 1, we want to set in_2 to it's negative value: a-b = a + (-b)
end architecture structural;

-- ----------------------------------------------------------------------


-- ----------------------------------------------------------------------
--8-Bit adder entity

entity 8bit-adder is
    port(in_1, in_2 : in std_logic_vector(7 downto 0);
         total : out std_logic_vector(7 downto 0));
end entity 8bit-adder;

-- ----------------------------------------------------------------------
--8-Bit adder architecture

architecture structural of 8bit-adder is
component full_adder is
    port(a, b, carry_in : in std_logic;
        total, carry_out : out std_logic);
end component full_adder;

signal carry_0, carry_1, carry_2, carry_3, carry_4, carry_5, carry_6 : std_logic; --carry signals for adders

--set of 8 full adders which comprise the add-sub command.  Each full adder is made up of 2 half adders.
--(a(in), b(in), carry_in(in), total(out), carry_out(out))
begin 
    fullAdder0: full_adder port map(in_1(0), in_2(0),'0', total(0), carry_0); --carry_in for the first full_adder is always 0
    fullAdder1: full_adder port map(in_1(1), in_2(1), carry_0, total(1), carry_1);
    fullAdder2: full_adder port map(in_1(2), in_2(2), carry_1, total(2), carry_2);
    fullAdder3: full_adder port map(in_1(3), in_2(3), carry_2, total(3), carry_3);
    fullAdder4: full_adder port map(in_1(4), in_2(4), carry_3, total(4), carry_4);
    fullAdder5: full_adder port map(in_1(5), in_2(5), carry_4, total(5), carry_5);
    fullAdder6: full_adder port map(in_1(6), in_2(6), carry_5, total(6), carry_6);
    fullAdder7: full_adder port map(in_1(7), in_2(7), carry_6, total(7), open
    );

end architecture structural;

-- ----------------------------------------------------------------------
--Full Adder Entity

entity full_adder is
    port(a, b, carry_in : in std_logic;
        total, carry_out : out std_logic);
end entity full_adder;

-- ----------------------------------------------------------------------
--Full Adder architecture

architecture structural of full_adder is
component half_adder is
    port(a, b : in std_logic;
        total, carry : out std_logic);
end component half_adder;

signal sig_1, sig_2, sig_3 : std_logic;
begin                    --(a(in), b(in), total(out), carry_out(out))
    h1: half_adder port map(a, b, sig_1, sig_3);
    h2: half_adder port map(sig_1, carry_in, total, sig_2);
    carry_out <= sig_2 or sig_3;
end architecture structural;


-- ----------------------------------------------------------------------
--Half Adder Entity

entity half_adder is
    port(a, b : in std_logic;
        total, carry : out std_logic);
end entity half_adder;

-- ----------------------------------------------------------------------
--Half Adder architecture

architecture behavioral of half_adder is
begin
    total <= a xor b; --Half adder logic is simply xor
    carry <= a and b;
end architecture behavioral;