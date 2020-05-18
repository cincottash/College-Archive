----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date: 02/27/2020 03:01:12 PM
-- Design Name: 
-- Module Name: adder_wrapper - Behavioral
-- Project Name: 
-- Target Devices: 
-- Tool Versions: 
-- Description: 
-- 
-- Dependencies: 
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
-- 
----------------------------------------------------------------------------------


library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx leaf cells in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity adder_wrapper is
    Port ( ARG : in STD_LOGIC_VECTOR (23 downto 0);
           sel : in STD_LOGIC;
           M : in STD_LOGIC;
           clk: in STD_LOGIC;
           SUM : out STD_LOGIC_VECTOR (23 downto 0);
           Overflow : out STD_LOGIC
           );
end adder_wrapper;

architecture Behavioral of adder_wrapper is

-- Component list, add/edit your own here
component ripple24_addsub
  Port
    ( 
     A : in STD_LOGIC_VECTOR (23 downto 0);
     B : in STD_LOGIC_VECTOR (23 downto 0);
     M: in STD_LOGIC;
     S : out STD_LOGIC_VECTOR (23 downto 0);
     Overflow : out STD_LOGIC
    );
end component;

component cla24_addsub2
  Port
    ( 
     A : in STD_LOGIC_VECTOR (23 downto 0);
     B : in STD_LOGIC_VECTOR (23 downto 0);
     M: in STD_LOGIC;
     S : out STD_LOGIC_VECTOR (23 downto 0);
     Overflow : out STD_LOGIC
    );
end component;


signal A_reg, B_reg, S_reg : STD_LOGIC_VECTOR(23 downto 0);
signal M_reg, Overflow_reg : STD_LOGIC;


begin

process(clk) begin
    if rising_edge(clk) then
        if(sel = '1') then
            A_reg <= ARG;
        else
            B_reg <= ARG;
        end if;
        M_reg <= M;
        SUM <= S_reg;
        Overflow <= Overflow_reg;
    end if;
end process;


-- addsub0: cla24_addsub port map(A_reg, B_reg, M_reg, S_reg, Overflow_reg);
addsub0: ripple24_addsub port map(A_reg, B_reg, M_reg, S_reg, Overflow_reg);

end Behavioral;
