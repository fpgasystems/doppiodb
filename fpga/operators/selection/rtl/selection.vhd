library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity selection is
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
end selection;

architecture behavioral of selection is

signal startTriggered : std_logic;

signal PredicateSource : unsigned(57 downto 0);
signal Source : unsigned(57 downto 0);
signal Destination : unsigned(57 downto 0);

signal SelectionType : integer range 0 to 5;
signal LowerThreshold : signed(31 downto 0);
signal UpperThreshold : signed(31 downto 0);

signal NumberOfCLsToRead : unsigned(31 downto 0);

type CLIntegersType is array (15 downto 0) of signed(31 downto 0);
signal CLIntegers : CLIntegersType;
signal predicatesInCL : signed(31 downto 0);
signal equalCLIntegers : CLIntegersType;
signal nonequalCLIntegers : CLIntegersType;
signal smallerCLIntegers : CLIntegersType;
signal smallerequalCLIntegers : CLIntegersType;
signal largerCLIntegers : CLIntegersType;
signal largerequalCLIntegers : CLIntegersType;

signal outputReg : std_logic_vector(511 downto 0);

signal um_rx_rd_ready_Internal : std_logic;
signal um_tx_rd_valid_Internal : std_logic;
signal um_tx_wr_valid_Internal : std_logic;

signal readReadyWasDown : std_logic;
signal writeReadyWasDown : std_logic;

signal predicateAddressWaiting : std_logic;
signal predicateAddress : unsigned(31 downto 0);

signal shouldPredicateBeRead : std_logic;
signal numberOfPredicateCLsRequested : unsigned(31 downto 0);
signal numberOfSourceCLsRequested : unsigned(31 downto 0);
signal numberOfPredicateCLsRead : unsigned(31 downto 0);
signal numberOfSourceCLsRead : unsigned(31 downto 0);
signal numberOfDestinationCLsWriteRequested : unsigned(31 downto 0);
signal numberOfDestinationCLsWritten : unsigned(31 downto 0);

begin

PredicateSource <= unsigned(um_params(63 downto 6));
Source <= unsigned(um_params(127 downto 70));
Destination <= unsigned(um_params(191 downto 134));

SelectionType <= to_integer(unsigned(um_params(223 downto 192)));
LowerThreshold <= signed(um_params(255 downto 224));
UpperThreshold <= signed(um_params(287 downto 256));

NumberOfCLsToRead <= unsigned(um_params(319 downto 288));

gen_CLIntegers: for i in 0 to 15 generate
	CLIntegers(i) <= signed(um_rx_data(i*32+31 downto i*32));

	equalCLIntegers(i) <= CLIntegers(i) when CLIntegers(i) = LowerThreshold else (others => '0');
	nonequalCLIntegers(i) <= CLIntegers(i) when CLIntegers(i) /= LowerThreshold else (others => '0');
	smallerCLIntegers(i) <= CLIntegers(i) when CLIntegers(i) < UpperThreshold else (others => '0');
	smallerequalCLIntegers(i) <= CLIntegers(i) when CLIntegers(i) <= UpperThreshold else (others => '0');
	largerCLIntegers(i) <= CLIntegers(i) when CLIntegers(i) > LowerThreshold else (others => '0');
	largerequalCLIntegers(i) <= CLIntegers(i) when CLIntegers(i) >= LowerThreshold else (others => '0');
end generate gen_CLIntegers;
predicatesInCL <= 	CLIntegers(15) or CLIntegers(14) or CLIntegers(13) or CLIntegers(12) or
					CLIntegers(11) or CLIntegers(10) or CLIntegers(9) or CLIntegers(8) or
					CLIntegers(7) or CLIntegers(6) or CLIntegers(5) or CLIntegers(4) or
					CLIntegers(3) or CLIntegers(2) or CLIntegers(1) or CLIntegers(0);

shouldPredicateBeRead <= '0' when PredicateSource = X"3FFFFFF" else '1';

um_tx_rd_valid <= um_tx_rd_valid_Internal;
um_tx_wr_valid <= um_tx_wr_valid_Internal;

readReadyWasDown <= '1' when um_tx_rd_valid_Internal = '1' AND um_tx_rd_ready = '0' else '0';
writeReadyWasDown <= '1' when um_tx_wr_valid_Internal = '1' AND um_tx_wr_ready = '0' else '0';

um_rx_rd_ready_Internal <= um_tx_wr_ready;
um_rx_rd_ready <= um_rx_rd_ready_Internal;

um_tx_data <= outputReg;

process(clk)
begin
if clk'event and clk = '1' then
	if rst_n = '0' then
		startTriggered <= '0';

		um_tx_rd_valid_Internal <= '0';
		um_tx_wr_valid_Internal <= '0';

		um_tx_wr_addr <= (others => '0');
		um_tx_wr_tag <= (others => '0');

		numberOfPredicateCLsRequested <= (others => '0');
		numberOfSourceCLsRequested <= (others => '0');
		numberOfPredicateCLsRead <= (others => '0');
		numberOfSourceCLsRead <= (others => '0');
		numberOfDestinationCLsWriteRequested <= (others => '0');
		numberOfDestinationCLsWritten <= (others => '0');
	else
		if start_um = '1' then
			startTriggered <= '1';
		end if;

		if startTriggered = '1' and um_tx_rd_ready = '1' and readReadyWasDown = '0' then
			if shouldPredicateBeRead = '1' then
				if predicateAddressWaiting = '1' then
					predicateAddressWaiting <= '0';
					um_tx_rd_valid_Internal <= '1';
					um_tx_rd_tag <= B"00000010";
					um_tx_rd_addr <= std_logic_vector(Source + predicateAddress);
					numberOfSourceCLsRequested <= numberOfSourceCLsRequested + 1;
				elsif numberOfPredicateCLsRequested < NumberOfCLsToRead then
					um_tx_rd_valid_Internal <= '1';
					um_tx_rd_tag <= B"00000001";
					um_tx_rd_addr <= std_logic_vector(PredicateSource + numberOfPredicateCLsRequested);
					numberOfPredicateCLsRequested <= numberOfPredicateCLsRequested + 1;
				else
					um_tx_rd_valid_Internal <= '0';
				end if;
			elsif numberOfSourceCLsRequested < NumberOfCLsToRead then
				um_tx_rd_valid_Internal <= '1';
				um_tx_rd_tag <= B"00000010";
				um_tx_rd_addr <= std_logic_vector(Source + numberOfSourceCLsRequested);
				numberOfSourceCLsRequested <= numberOfSourceCLsRequested + 1;
			else
				um_tx_rd_valid_Internal <= '0';
			end if;
		end if;

		
		if um_tx_wr_valid_Internal = '1' and um_tx_wr_ready = '0' then
			um_tx_wr_valid_Internal <= '1';
		else
			um_tx_wr_valid_Internal <= '0';
		end if;

		if um_rx_rd_valid = '1' and um_rx_rd_ready_Internal = '1' and writeReadyWasDown = '0' then
			if um_rx_rd_tag = B"00000001" then
				--if predicatesInCL < 0 or predicatesInCL > 0 then
					predicateAddress <= numberOfPredicateCLsRead;
					predicateAddressWaiting <= '1';
					numberOfPredicateCLsRead <= numberOfPredicateCLsRead + 1;
				--end if;
			elsif um_rx_rd_tag = B"00000010" then
				numberOfSourceCLsRead <= numberOfSourceCLsRead + 1;
				case SelectionType is
					when 0 => outputReg <= 	std_logic_vector(equalCLIntegers(15)) & std_logic_vector(equalCLIntegers(14)) & 
											std_logic_vector(equalCLIntegers(13)) & std_logic_vector(equalCLIntegers(12)) &
											std_logic_vector(equalCLIntegers(11)) & std_logic_vector(equalCLIntegers(10)) &
											std_logic_vector(equalCLIntegers(9)) & std_logic_vector(equalCLIntegers(8)) &
											std_logic_vector(equalCLIntegers(7)) & std_logic_vector(equalCLIntegers(6)) &
											std_logic_vector(equalCLIntegers(5)) & std_logic_vector(equalCLIntegers(4)) &
											std_logic_vector(equalCLIntegers(3)) & std_logic_vector(equalCLIntegers(2)) &
											std_logic_vector(equalCLIntegers(1)) & std_logic_vector(equalCLIntegers(0));

					when 1 => outputReg <= 	std_logic_vector(nonequalCLIntegers(15)) & std_logic_vector(nonequalCLIntegers(14)) & 
											std_logic_vector(nonequalCLIntegers(13)) & std_logic_vector(nonequalCLIntegers(12)) &
											std_logic_vector(nonequalCLIntegers(11)) & std_logic_vector(nonequalCLIntegers(10)) &
											std_logic_vector(nonequalCLIntegers(9)) & std_logic_vector(nonequalCLIntegers(8)) &
											std_logic_vector(nonequalCLIntegers(7)) & std_logic_vector(nonequalCLIntegers(6)) &
											std_logic_vector(nonequalCLIntegers(5)) & std_logic_vector(nonequalCLIntegers(4)) &
											std_logic_vector(nonequalCLIntegers(3)) & std_logic_vector(nonequalCLIntegers(2)) &
											std_logic_vector(nonequalCLIntegers(1)) & std_logic_vector(nonequalCLIntegers(0));

					when 2 => outputReg <= 	std_logic_vector(smallerCLIntegers(15)) & std_logic_vector(smallerCLIntegers(14)) & 
											std_logic_vector(smallerCLIntegers(13)) & std_logic_vector(smallerCLIntegers(12)) &
											std_logic_vector(smallerCLIntegers(11)) & std_logic_vector(smallerCLIntegers(10)) &
											std_logic_vector(smallerCLIntegers(9)) & std_logic_vector(smallerCLIntegers(8)) &
											std_logic_vector(smallerCLIntegers(7)) & std_logic_vector(smallerCLIntegers(6)) &
											std_logic_vector(smallerCLIntegers(5)) & std_logic_vector(smallerCLIntegers(4)) &
											std_logic_vector(smallerCLIntegers(3)) & std_logic_vector(smallerCLIntegers(2)) &
											std_logic_vector(smallerCLIntegers(1)) & std_logic_vector(smallerCLIntegers(0));

					when 3 => outputReg <= 	std_logic_vector(smallerequalCLIntegers(15)) & std_logic_vector(smallerequalCLIntegers(14)) & 
											std_logic_vector(smallerequalCLIntegers(13)) & std_logic_vector(smallerequalCLIntegers(12)) &
											std_logic_vector(smallerequalCLIntegers(11)) & std_logic_vector(smallerequalCLIntegers(10)) &
											std_logic_vector(smallerequalCLIntegers(9)) & std_logic_vector(smallerequalCLIntegers(8)) &
											std_logic_vector(smallerequalCLIntegers(7)) & std_logic_vector(smallerequalCLIntegers(6)) &
											std_logic_vector(smallerequalCLIntegers(5)) & std_logic_vector(smallerequalCLIntegers(4)) &
											std_logic_vector(smallerequalCLIntegers(3)) & std_logic_vector(smallerequalCLIntegers(2)) &
											std_logic_vector(smallerequalCLIntegers(1)) & std_logic_vector(smallerequalCLIntegers(0));

					when 4 => outputReg <= 	std_logic_vector(largerCLIntegers(15)) & std_logic_vector(largerCLIntegers(14)) & 
											std_logic_vector(largerCLIntegers(13)) & std_logic_vector(largerCLIntegers(12)) &
											std_logic_vector(largerCLIntegers(11)) & std_logic_vector(largerCLIntegers(10)) &
											std_logic_vector(largerCLIntegers(9)) & std_logic_vector(largerCLIntegers(8)) &
											std_logic_vector(largerCLIntegers(7)) & std_logic_vector(largerCLIntegers(6)) &
											std_logic_vector(largerCLIntegers(5)) & std_logic_vector(largerCLIntegers(4)) &
											std_logic_vector(largerCLIntegers(3)) & std_logic_vector(largerCLIntegers(2)) &
											std_logic_vector(largerCLIntegers(1)) & std_logic_vector(largerCLIntegers(0));

					when 5 => outputReg <= 	std_logic_vector(largerequalCLIntegers(15)) & std_logic_vector(largerequalCLIntegers(14)) & 
											std_logic_vector(largerequalCLIntegers(13)) & std_logic_vector(largerequalCLIntegers(12)) &
											std_logic_vector(largerequalCLIntegers(11)) & std_logic_vector(largerequalCLIntegers(10)) &
											std_logic_vector(largerequalCLIntegers(9)) & std_logic_vector(largerequalCLIntegers(8)) &
											std_logic_vector(largerequalCLIntegers(7)) & std_logic_vector(largerequalCLIntegers(6)) &
											std_logic_vector(largerequalCLIntegers(5)) & std_logic_vector(largerequalCLIntegers(4)) &
											std_logic_vector(largerequalCLIntegers(3)) & std_logic_vector(largerequalCLIntegers(2)) &
											std_logic_vector(largerequalCLIntegers(1)) & std_logic_vector(largerequalCLIntegers(0));
				end case;
				um_tx_wr_valid_Internal <= '1';
				um_tx_wr_addr <= std_logic_vector(Destination + numberOfDestinationCLsWriteRequested);
				numberOfDestinationCLsWriteRequested <= numberOfDestinationCLsWriteRequested + 1;
			end if;
		end if;

		if um_rx_wr_valid = '1' then
			numberOfDestinationCLsWritten <= numberOfDestinationCLsWritten + 1;
		end if;

		um_done <= '0';
		if numberOfDestinationCLsWritten = NumberOfCLsToRead and startTriggered = '1' then
			startTriggered <= '0';
			um_done <= '1';
		end if;

	end if;
end if;
end process;

end architecture;