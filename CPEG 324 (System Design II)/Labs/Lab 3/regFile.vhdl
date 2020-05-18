--Created By Shane Cincotta 5/7/19

library ieee;
use ieee.std_logic_1164.all;

-- -------------------------------------------------------------------
--regFile entity

--Contains 4, 8 bit registers that are initialized to 0
entity regFile is
  port(
    RD : in std_logic_vector(1 downto 0); --RD Reg
    RS : in std_logic_vector(1 downto 0); --RS Reg
    RT : in std_logic_vector(1 downto 0); --RT Reg
    Write_Data : in std_logic_vector(7 downto 0); --Write Data
    CLK : in std_logic; --Clock
    Write_Enable : in std_logic; --Write Enable
    RS_DATA : out std_logic_vector(7 downto 0);
    RT_DATA : out std_logic_vector(7 downto 0)
  );
end entity regFile;


-- -------------------------------------------------------------------
--regFile archtitecture

architecture behavioral of regFile is
  --signals for all our registers which are 8 bits and filled with 0's
  signal R1 : std_logic_vector(7 downto 0) := "00000000";
  signal R2 : std_logic_vector(7 downto 0) := "00000000";
  signal R3 : std_logic_vector(7 downto 0) := "00000000";
  signal R4 : std_logic_vector(7 downto 0) := "00000000";

  begin
    --2bits is enough to represent 4 registers
    with RS select RS_DATA <=
      R1 when "00",
      R2 when "01",
      R3 when "10",
      R4 when others;
    with RT select RT_DATA <=
      R1 when "00",
      R2 when "01",
      R3 when "10",
      R4 when others;


    process (CLK) is
      begin
        if (CLK'event and CLK='1') then
          if (Write_Enable = '1') then
            if (RD = "00") then
              R1 <= Write_Data;
            elsif (RD = "01") then
              R2 <= Write_Data;
            elsif (RD = "10") then
              R3 <= Write_Data;
            elsif (RD = "11") then
              R4 <= Write_Data;
            end if;
          end if;
        end if;
      end process;
end architecture;
-- -------------------------------------------------------------------