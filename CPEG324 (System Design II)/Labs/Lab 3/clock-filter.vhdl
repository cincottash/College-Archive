--Created by Shane Cincotta 5/7/19

library ieee;
use ieee.std_logic_1164.all;

-- -------------------------------------------------------------------
--clock-filter entity

--Used to skip instructions.
entity clock-filter is
  port(
    clk_in : in std_logic;
    clk_out : out std_logic;
    S: in std_logic;
    skip: in std_logic
  );
end entity clock-filter;

-- -------------------------------------------------------------------
--clock-filter archtitecture

architecture structural of clock-filter is
  component flipflop is
     port(
      clk : in std_logic;
      R : in std_logic;
      D : in std_logic;
      Q : out std_logic
     );
  end component flipflop;
  component dLatch is
     port(
      E : in std_logic;
      D : in std_logic;
      Q : out std_logic
     );
  end component dLatch;

signal Q0, Q1, Q2, Q3, Q4, D3, D4 : std_logic := '1';

begin
  flipflop0 : flipflop port map(clk_in, Q3, '1', Q0);
  flipflop1 : flipflop port map(clk_in, Q4, Q0, Q1);
  flipflop2 : flipflop port map(clk_in, '0', Q1, Q2);
  dLatch0 : dLatch port map(clk_in, D3, Q3);
  dLatch1 : dLatch port map(clk_in, D4, Q4);

  D3 <= S and D4;
  D4 <= skip and Q2 and Q1 and Q0;
  clk_out <= Q2 and clk_in after 1 ps;
end architecture structural;

-- -------------------------------------------------------------------
--Flip-flop entity

--D Flip-Flop
entity flipflop is
   port(
      clk : in std_logic;
      R : in std_logic;
      D : in std_logic;
      Q : out std_logic
   );
end entity flipflop;

-- -------------------------------------------------------------------
--Flip-flop archtitecture

architecture behavioral of flipflop is
  signal qt : std_logic :='1';
begin
   process (clk,R) is
   begin
      if (R = '1') then
        qt <= '0';
      elsif clk'event and clk = '1' then
          qt <= D;
      end if;
   end process;
   Q<=qt;
end architecture behavioral;

-- -------------------------------------------------------------------
--D-latch entity

--D-latch
entity dLatch is
   port(
      E : in std_logic;
      D : in std_logic;
      Q : out std_logic
   );
end entity dLatch;

-- -------------------------------------------------------------------
--D-latch archtitecture

architecture behavioral of dLatch is
  signal t : std_logic := '0';
begin
   with E select t<=
    D when '1',
    t when others;
   Q<=t;
end architecture behavioral;
-- -------------------------------------------------------------------