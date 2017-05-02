--
--  Copyright 2016 - 2017 Systems Group, ETH Zurich
-- 
--  This hardware operator is free software: you can redistribute it and/or
--  modify it under the terms of the GNU General Public License as published
--  by the Free Software Foundation, either version 3 of the License, or
--  (at your option) any later version.
-- 
--  This program is distributed in the hope that it will be useful,
--  but WITHOUT ANY WARRANTY; without even the implied warranty of
--  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
--  GNU General Public License for more details.
-- 
--  You should have received a copy of the GNU General Public License
--  along with this program.  If not, see <http://www.gnu.org/licenses/>.
--
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity minmaxsum is
port (
	clk : in std_logic;
	rst_n : in std_logic;

	start_um : in std_logic;
    um_params : in std_logic_vector(511 downto 0);
    um_done : out std_logic;

    -- TX RD
    um_tx_rd_addr : out std_logic_vector(57 downto 0);
    um_tx_rd_tag : out std_logic_vector(7 downto 0);
    um_tx_rd_valid : out std_logic;
    um_tx_rd_ready : in std_logic;

    -- TX WR
    um_tx_wr_addr : out std_logic_vector(57 downto 0);
    um_tx_wr_tag : out std_logic_vector(7 downto 0);
    um_tx_wr_valid : out std_logic;
    um_tx_data : out std_logic_vector(511 downto 0);
    um_tx_wr_ready : in std_logic;

    -- RX RD
    um_rx_rd_tag : in std_logic_vector(7 downto 0);
    um_rx_data : in std_logic_vector(511 downto 0);
    um_rx_rd_valid : in std_logic;
    um_rx_rd_ready : out std_logic;

    -- RX WR
    um_rx_wr_valid : in std_logic;
    um_rx_wr_tag : in std_logic_vector(7 downto 0));
end minmaxsum;

architecture behavioral of minmaxsum is

signal startTriggered : std_logic;

signal Source : unsigned(57 downto 0);
signal Destination : unsigned(57 downto 0);

signal NumberOfCLsToRead : unsigned(31 downto 0);

signal readReadyWasDown : std_logic;

signal um_tx_rd_valid_Internal : std_logic;
signal um_tx_wr_valid_Internal : std_logic;

signal numberOfSourceCLsRequested : unsigned(31 downto 0);
signal numberOfSourceCLsRead : unsigned(31 downto 0);
signal numberOfDestinationCLsWriteRequested : unsigned(31 downto 0);
signal numberOfDestinationCLsWritten : unsigned(31 downto 0);

type CLIntegersType is array (15 downto 0) of signed(31 downto 0);
signal CLIntegers : CLIntegersType;

type OddEvenSortIntegersType is array(1 to 16) of CLIntegersType;
signal OddEvenSortIntegers : OddEvenSortIntegersType;
signal sortingSteps : std_logic_vector(1 to 16);

signal minimum : signed(31 downto 0);
signal maximum : signed(31 downto 0);
signal summation : signed(31 downto 0);

begin

um_rx_rd_ready <= '1';
um_tx_rd_tag <= (others => '0');
um_tx_wr_tag <= (others => '0');

Source <= unsigned(um_params(63 downto 6));
Destination <= unsigned(um_params(127 downto 70));

NumberOfCLsToRead <= unsigned(um_params(159 downto 128));

gen_CLIntegers: for i in 0 to 15 generate
	CLIntegers(i) <= signed(um_rx_data(i*32+31 downto i*32));
end generate gen_CLIntegers;

um_tx_rd_valid <= um_tx_rd_valid_Internal;
um_tx_wr_valid <= um_tx_wr_valid_Internal;

readReadyWasDown <= '1' when um_tx_rd_valid_Internal = '1' AND um_tx_rd_ready = '0' else '0';

process(clk)
begin
if clk'event and clk = '1' then
	if rst_n = '0' then
		startTriggered <= '0';

		um_tx_rd_valid_Internal <= '0';
		um_tx_wr_valid_Internal <= '0';

		numberOfSourceCLsRequested <= (others => '0');
		numberOfSourceCLsRead <= (others => '0');
		numberOfDestinationCLsWriteRequested <= (others => '0');
		numberOfDestinationCLsWritten <= (others => '0');

		minimum <= X"7FFFFFFF";
		maximum <= X"80000000";
		summation <= (others => '0');
	else
		if start_um = '1' then
			startTriggered <= '1';
		end if;

		-- Request CLs
		if startTriggered = '1' and um_tx_rd_ready = '1' and readReadyWasDown = '0' then
			if numberOfSourceCLsRequested < NumberOfCLsToRead then
				um_tx_rd_valid_Internal <= '1';
				um_tx_rd_addr <= std_logic_vector(Source + numberOfSourceCLsRequested);
				numberOfSourceCLsRequested <= numberOfSourceCLsRequested + 1;
			else
				um_tx_rd_valid_Internal <= '0';
			end if;
		end if;

		-- Read CLs
		sortingSteps(1) <= um_rx_rd_valid;
		for j in 1 to 15 loop
			sortingSteps(j+1) <= sortingSteps(j);
		end loop;
		-- 1. Cycle
		for i in 0 to 7 loop
			if CLIntegers(2*i) > CLIntegers(2*i+1) then
				OddEvenSortIntegers(1)(2*i) <= CLIntegers(2*i+1); OddEvenSortIntegers(1)(2*i+1) <= CLIntegers(2*i);
			else
				OddEvenSortIntegers(1)(2*i) <= CLIntegers(2*i); OddEvenSortIntegers(1)(2*i+1) <= CLIntegers(2*i+1);
			end if;
		end loop;
		-- 3.5.7.9.11.13.15. Cycle
		for j in 1 to 7 loop
			for i in 0 to 7 loop
				if OddEvenSortIntegers(2*j)(2*i) > OddEvenSortIntegers(2*j)(2*i+1) then
					OddEvenSortIntegers(2*j+1)(2*i) <= OddEvenSortIntegers(2*j)(2*i+1); OddEvenSortIntegers(2*j+1)(2*i+1) <= OddEvenSortIntegers(2*j)(2*i);
				else
					OddEvenSortIntegers(2*j+1)(2*i) <= OddEvenSortIntegers(2*j)(2*i); OddEvenSortIntegers(2*j+1)(2*i+1) <= OddEvenSortIntegers(2*j)(2*i+1);
				end if;
			end loop;
		end loop;
		-- 2.4.6.8.10.12.14.16. Cycle
		for j in 1 to 8 loop
			OddEvenSortIntegers(2*j)(0) <= OddEvenSortIntegers(2*j-1)(0);
			OddEvenSortIntegers(2*j)(15) <= OddEvenSortIntegers(2*j-1)(15);
			for i in 1 to 7 loop
				if OddEvenSortIntegers(2*j-1)(2*i-1) > OddEvenSortIntegers(2*j-1)(2*i) then
					OddEvenSortIntegers(2*j)(2*i-1) <= OddEvenSortIntegers(2*j-1)(2*i); OddEvenSortIntegers(2*j)(2*i) <= OddEvenSortIntegers(2*j-1)(2*i-1);
				else
					OddEvenSortIntegers(2*j)(2*i-1) <= OddEvenSortIntegers(2*j-1)(2*i-1); OddEvenSortIntegers(2*j)(2*i) <= OddEvenSortIntegers(2*j-1)(2*i);
				end if;
			end loop;
		end loop;

		if sortingSteps(16) = '1' then
			numberOfSourceCLsRead <= numberOfSourceCLsRead + 1;
			if OddEvenSortIntegers(16)(0) < minimum then
				minimum <= OddEvenSortIntegers(16)(0);
			end if;
			if OddEvenSortIntegers(16)(15) > maximum then
				maximum <= OddEvenSortIntegers(16)(15);
			end if;
			summation <= summation + 	OddEvenSortIntegers(16)(0) + OddEvenSortIntegers(16)(1) + OddEvenSortIntegers(16)(2) + OddEvenSortIntegers(16)(3) +
										OddEvenSortIntegers(16)(4) + OddEvenSortIntegers(16)(5) + OddEvenSortIntegers(16)(6) + OddEvenSortIntegers(16)(7) +
										OddEvenSortIntegers(16)(8) + OddEvenSortIntegers(16)(9) + OddEvenSortIntegers(16)(10) + OddEvenSortIntegers(16)(11) + 
										OddEvenSortIntegers(16)(12) + OddEvenSortIntegers(16)(13) + OddEvenSortIntegers(16)(14) + OddEvenSortIntegers(16)(15);
		end if;

		um_tx_wr_valid_Internal <= '0';
		if um_tx_wr_ready = '1' and numberOfSourceCLsRead = NumberOfCLsToRead and numberOfDestinationCLsWriteRequested = X"00000000" and startTriggered = '1' then
			um_tx_wr_valid_Internal <= '1';
			um_tx_wr_addr <= std_logic_vector(Destination);
			um_tx_data(511 downto 96) <= (others => '0');
			um_tx_data(95 downto 0) <= std_logic_vector(minimum) & std_logic_vector(maximum) & std_logic_vector(summation);
			numberOfDestinationCLsWriteRequested <= numberOfDestinationCLsWriteRequested + 1;
		end if;

		if um_rx_wr_valid = '1' then
			numberOfDestinationCLsWritten <= numberOfDestinationCLsWritten + 1;
		end if;

		um_done <= '0';
		if numberOfDestinationCLsWritten = X"00000001" and startTriggered = '1' then
			startTriggered <= '0';
			um_done <= '1';
		end if;

	end if;
end if;
end process;


end architecture;