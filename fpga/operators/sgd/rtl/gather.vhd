library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package gather_constants is
    constant Ks : integer := 16;
    constant MAX_DIMENSION_BITS : integer := 4;
    constant MAX_DIMENSION : integer := 2**MAX_DIMENSION_BITS;
    constant MAX_GATHER_FACTOR : integer := MAX_DIMENSION*Ks;
    constant MAX_GATHER_DEPTH_BITS : integer := 8;
    constant MAX_GATHER_DEPTH : integer := 2**MAX_GATHER_DEPTH_BITS;
end package;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.gather_constants.all;

entity gather is
port (
	clk : in std_logic;
	resetn : in std_logic;

	enable : in std_logic;
	start : in std_logic;

	-- TX RD
	um_tx_rd_addr : out std_logic_vector(57 downto 0);
	um_tx_rd_tag : out std_logic_vector(7 downto 0);
	um_tx_rd_valid : out std_logic;
	um_tx_rd_ready : in std_logic;

	-- RX RD
	um_rx_rd_tag : in std_logic_vector(7 downto 0);
	um_rx_data : in std_logic_vector(511 downto 0);
	um_rx_rd_valid : in std_logic;
	um_rx_rd_ready : out std_logic;

	number_of_requested_reads : out std_logic_vector(31 downto 0);
	number_of_completed_reads : out std_logic_vector(31 downto 0);
	out_valid : out std_logic;
	out_data : out std_logic_vector(511 downto 0);

	addresses : in std_logic_vector(64*MAX_DIMENSION-1 downto 0);
	number_of_samples : in std_logic_vector(31 downto 0);
	number_of_dimensions : in std_logic_vector(MAX_DIMENSION_BITS downto 0);
	gather_depth : in std_logic_vector(MAX_GATHER_DEPTH_BITS-1 downto 0));
end gather;

architecture behavioral of gather is

signal started : std_logic;
signal start_1d : std_logic;
signal start_2d : std_logic;

signal NumberOfSamples : unsigned(31 downto 0) := (others => '0');
signal NumberOfDimensions : integer range 0 to MAX_DIMENSION := MAX_DIMENSION;
signal GatherDepth : unsigned(MAX_GATHER_DEPTH_BITS-1 downto 0) := (others => '1');

signal k : integer range 0 to MAX_DIMENSION-1;
signal i : integer range 0 to MAX_DIMENSION-1;
signal r : integer range 0 to MAX_DIMENSION-1;

signal Remainder : integer range 0 to 1;
signal NumberOfCLsForOneColumn : unsigned(31 downto 0) := (others => '0');

signal NumberOfRequestedReads : unsigned(31 downto 0);
signal NumberOfCompletedReads : unsigned(31 downto 0);
signal NumberOfForwarded : unsigned(31 downto 0) := (others => '0');

signal ReadingAddress : std_logic_vector(57 downto 0);
type ReadingAddressOffsetType is array (MAX_DIMENSION-1 downto 0) of unsigned(31 downto 0);
signal ReadingAddressOffset : ReadingAddressOffsetType;

type in_collection_type is array (MAX_DIMENSION-1 downto 0) of std_logic_vector(32*Ks-1 downto 0);
signal in_we : std_logic_vector(MAX_DIMENSION-1 downto 0);
signal in_CLs : in_collection_type;

type out_collection_type is array (Ks-1 downto 0) of std_logic_vector(32*MAX_DIMENSION-1 downto 0);
signal out_re : std_logic_vector(Ks-1 downto 0);
signal out_Cls : out_collection_type;

signal gather_we : std_logic_vector(MAX_GATHER_FACTOR-1 downto 0);
signal gather_re : std_logic_vector(MAX_GATHER_FACTOR-1 downto 0);
signal gather_valid : std_logic_vector(MAX_GATHER_FACTOR-1 downto 0);
signal gather_empty : std_logic_vector(MAX_GATHER_FACTOR-1 downto 0);
signal gather_full : std_logic_vector(MAX_GATHER_FACTOR-1 downto 0);
signal gather_almostfull : std_logic_vector(MAX_GATHER_FACTOR-1 downto 0);
type gather_data_type is array (MAX_GATHER_FACTOR-1 downto 0) of std_logic_vector(31 downto 0);
signal gather_data_in : gather_data_type;
signal gather_data_out : gather_data_type;
type gather_count_type is array (MAX_GATHER_FACTOR-1 downto 0) of std_logic_vector(MAX_GATHER_DEPTH_BITS-1 downto 0);
signal gather_count : gather_count_type;

signal FinishedReading : std_logic;

component my_fifo
generic(
    FIFO_WIDTH : integer := 32;
    FIFO_DEPTH_BITS : integer := 8;
    FIFO_ALMOSTFULL_THRESHOLD : integer := 220);
port(
    clk :       in std_logic;
    reset_n :   in std_logic;

    we :        in std_logic;
    din :       in std_logic_vector(FIFO_WIDTH-1 downto 0); 
    re :        in std_logic;
    valid :     out std_logic;
    dout :      out std_logic_vector(FIFO_WIDTH-1 downto 0);
    count :     out std_logic_vector(FIFO_DEPTH_BITS-1 downto 0);
    empty :     out std_logic;
    full :      out std_logic;
    almostfull: out std_logic);
end component;

begin

FIFOS: for k in 0 to MAX_GATHER_FACTOR-1 generate
	FIFOx: my_fifo
	generic map (
		FIFO_WIDTH => 32,
		FIFO_DEPTH_BITS => MAX_GATHER_DEPTH_BITS,
		FIFO_ALMOSTFULL_THRESHOLD => MAX_GATHER_DEPTH-32)
	port map (
		clk => clk,
		reset_n => start,

		we => gather_we(k),
		din => gather_data_in(k),
		re => gather_re(k),
		valid => gather_valid(k),
		dout => gather_data_out(k),
		count => gather_count(k),
		empty => gather_empty(k),
		full => gather_full(k),
		almostfull => gather_almostfull(k));
end generate FIFOS;

COLLECTION_IN: for i in 0 to MAX_DIMENSION-1 generate
	DISTRIBUTE_IN: for j in 0 to Ks-1 generate
		gather_we(i*Ks + j) <= in_we(i);
		gather_data_in(i*Ks + j) <= in_CLs(i)(31+32*j downto 32*j);
	end generate DISTRIBUTE_IN;
end generate COLLECTION_IN;

COLLECTION_OUT: for j in 0 to Ks-1 generate
	DISTRIBUTE_OUT: for i in 0 to MAX_DIMENSION-1 generate
		gather_re(i*Ks + j) <= out_re(j);
		out_Cls(j)(31+32*i downto 32*i) <= gather_data_out(i*Ks + j);
	end generate DISTRIBUTE_OUT;
end generate COLLECTION_OUT;


GatherDepth <= unsigned(gather_depth);

i <= to_integer(unsigned(um_rx_rd_tag));

Remainder <= 1 when unsigned(number_of_samples(3 downto 0)) > 0 else 0;
NumberOfCLsForOneColumn <= shift_right(unsigned(number_of_samples), 4) + to_unsigned(Remainder, 1);

ReadingAddress <= addresses(63+64*k downto 6+64*k);

um_rx_rd_ready <= '1';
number_of_requested_reads <= std_logic_vector(NumberOfRequestedReads);
number_of_completed_reads <= std_logic_vector(NumberOfCompletedReads);

started <= start and start_1d and start_2d;

process(clk)
begin
if clk'event and clk = '1' then
	start_1d <= start;
	start_2d <= start_1d;

	if started = '0' then
		NumberOfSamples <= unsigned(number_of_samples);
		NumberOfDimensions <= MAX_DIMENSION;

		k <= 0;
		r <= 0;
	
		NumberOfRequestedReads <= (others => '0');
		NumberOfCompletedReads <= (others => '0');
		NumberOfForwarded <= (others => '0');

		ReadingAddressOffset <= (others => (others => '0'));

		FinishedReading <= '0';

		um_tx_rd_addr <= (others => '0');
		um_tx_rd_tag <= (others => '0');
		um_tx_rd_valid <= '0';
	else
		NumberOfDimensions <= to_integer( unsigned(number_of_dimensions) );
		
		um_tx_rd_valid <= '0';
		if enable = '1' and um_tx_rd_ready = '1' and FinishedReading = '0' then
			um_tx_rd_valid <= '1';
			um_tx_rd_addr <= std_logic_vector( unsigned(ReadingAddress) + ReadingAddressOffset(k) );
			um_tx_rd_tag <= std_logic_vector(to_unsigned(k, 8));
			ReadingAddressOffset(k) <= ReadingAddressOffset(k) + 1;
			NumberOfRequestedReads <= NumberOfRequestedReads +1;

			if ReadingAddressOffset(k) = NumberOfCLsForOneColumn-1 then
				if k = NumberOfDimensions-1 then
					FinishedReading <= '1';
					k <= 0;
				else
					k <= k + 1;
				end if;
			elsif (ReadingAddressOffset(k)(MAX_GATHER_DEPTH_BITS-1 downto 0) AND (GatherDepth-1)) = (GatherDepth-1) then
				if k = NumberOfDimensions-1 then
					k <= 0;
				else
					k <= k + 1;
				end if;
			end if;
		end if;

		in_we <= (others => '0');
		if um_rx_rd_valid = '1' then
			NumberOfCompletedReads <= NumberOfCompletedReads + 1;
			in_we(i) <= '1';
			in_CLs(i) <= um_rx_data;
		end if;

		out_re <= (others => '0');
		if gather_empty(NumberOfDimensions*Ks-1) = '0' and NumberOfForwarded < NumberOfSamples then
			NumberOfForwarded <= NumberOfForwarded + 1;
			out_re(r) <= '1';
			if r = Ks-1 then
				r <= 0;
			else
				r <= r + 1;
			end if;
		end if;

		out_valid <= '0';
		for p in 0 to Ks-1 loop
			if gather_valid(p) = '1' then
				out_valid <= '1';
				out_data <= out_Cls(p);
			end if;
		end loop;

    end if;
end if;
end process;

end architecture;