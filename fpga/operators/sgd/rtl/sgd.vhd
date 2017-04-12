library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

package sgd_constants is
    constant MAX_DIMENSION_BITS : integer := 13;
    constant MAX_DIMENSION : integer := 2**MAX_DIMENSION_BITS;
    
    constant FIFO_DEPTH_BITS : integer := MAX_DIMENSION_BITS-4;
    constant FIFO_DEPTH : integer := 2**FIFO_DEPTH_BITS-10;
    constant X_CL_COUNT : integer := MAX_DIMENSION/16;

    constant MAX_GATHER_DEPTH_BITS : integer := 8;
    constant MAX_GATHER_DEPTH : integer := 2**MAX_GATHER_DEPTH_BITS;
end package;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.sgd_constants.all;

entity sgd is
port (
	clk : in std_logic;
	rst_n : in std_logic;

	start_um : in std_logic;
    um_params : in std_logic_vector(1535 downto 0);
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
end sgd;

architecture behavioral of sgd is

signal started : std_logic;

signal source_addresses : std_logic_vector(1023 downto 0); -- 16 addresses
signal destination_address : std_logic_vector(63 downto 0);
signal mini_batch_size : std_logic_vector(15 downto 0);
signal step_size : std_logic_vector(31 downto 0);
signal number_of_epochs : std_logic_vector(13 downto 0);
signal dimension : std_logic_vector(17 downto 0);
signal number_of_samples : std_logic_vector(31 downto 0);
signal number_of_CL_to_process : std_logic_vector(31 downto 0);
signal binarize_b_value : std_logic;
signal b_value_to_binarize_to : std_logic_vector(31 downto 0);
signal do_gather : std_logic;
signal gather_depth : std_logic_vector(7 downto 0);

signal internal_tx_rd_addr : std_logic_vector(57 downto 0);
signal internal_tx_rd_tag : std_logic_vector(7 downto 0);
signal internal_tx_rd_valid : std_logic;
signal internal_rx_data : std_logic_vector(511 downto 0);
signal internal_rx_rd_valid : std_logic;

-- GATHER SIGNALS
signal gather_enable : std_logic := '0';
signal gather_start : std_logic := '0';

signal gather_tx_rd_addr : std_logic_vector(57 downto 0);
signal gather_tx_rd_tag : std_logic_vector(7 downto 0);
signal gather_tx_rd_valid : std_logic;
signal gather_rx_rd_ready : std_logic;

signal gather_number_of_requested_reads : std_logic_vector(31 downto 0);
signal gather_number_of_completed_reads : std_logic_vector(31 downto 0);
signal gather_out_valid : std_logic;
signal gather_out_data : std_logic_vector(511 downto 0);
signal gather_number_of_dimensions : std_logic_vector(4 downto 0);

signal accumulation_count : integer;
signal remainder : integer;

signal NumberOfCLToProcess : unsigned(31 downto 0) := (others => '0');
signal NumberOfRequestedReads : unsigned(31 downto 0) := (others => '0');
signal NumberOfCompletedReads : unsigned(31 downto 0) := (others => '0');
signal NumberOfRequestedWrites : unsigned(31 downto 0) := (others => '0');
signal NumberOfCompletedWrites : unsigned(31 downto 0) := (others => '0');
signal NumberOfEpochs : unsigned(13 downto 0);
signal NumberOfEpochsCompleted : unsigned(13 downto 0);

signal NumberOfSamples : unsigned(31 downto 0) := (others => '0');
signal sample_index_to_read : integer;
signal sample_index_to_read_unsigned : unsigned(31 downto 0);
signal gradient_valid_counter : integer;
signal gradient_valid_counter_unsigned : unsigned(31 downto 0);

signal count_upto_a_whole_row : integer range 0 to X_CL_COUNT-1;
signal new_CL_available : std_logic_vector(9 downto 0);
signal new_row_available : std_logic_vector(9 downto 0);

signal dot_product_result_almost_valid : std_logic;
signal dot_product_result_valid : std_logic;
signal dot_product_result : std_logic_vector(31 downto 0);

signal minus_b_times_alpha_almost_valid : std_logic;
signal minus_b_times_alpha_valid : std_logic;
signal minus_b_times_alpha : std_logic_vector(31 downto 0);

signal gradient_almost_valid : std_logic;
signal gradient_valid : std_logic;
signal gradient_valid_1d : std_logic;
signal gradient : std_logic_vector(511 downto 0);
signal gradient_fixed : std_logic_vector(511 downto 0);

signal new_x_almost_valid : std_logic;
signal new_x_valid : std_logic;
signal new_x : std_logic_vector(511 downto 0);

type x_type is array (X_CL_COUNT-1 downto 0) of std_logic_vector(511 downto 0);
signal x : x_type;
signal x_loading : x_type;
signal x_reset_index : integer range 0 to X_CL_COUNT-1;
signal x_index1 : integer range 0 to X_CL_COUNT-1;
signal x_index2 : integer range 0 to X_CL_COUNT-1;
signal x_index3 : integer range 0 to X_CL_COUNT-1;
signal x_for_dot_product : std_logic_vector(511 downto 0);
signal x_for_dot_product_fp : std_logic_vector(511 downto 0);
signal x_for_update : std_logic_vector(511 downto 0);

signal write_back_the_model : std_logic;
signal write_back_index : integer range 0 to X_CL_COUNT-1 := 0;
signal model_is_written : std_logic;

signal ififo_we : std_logic;
signal ififo_din : std_logic_vector(511 downto 0);
signal ififo_re : std_logic;
signal ififo_valid : std_logic;
signal ififo_dout : std_logic_vector(511 downto 0);
signal ififo_dout_valid : std_logic_vector(511 downto 0);
signal ififo_count : std_logic_vector(FIFO_DEPTH_BITS-1 downto 0);
signal ififo_empty : std_logic;
signal ififo_full : std_logic;
signal ififo_almostfull: std_logic;
signal ififo_free_count : unsigned(FIFO_DEPTH_BITS-1 downto 0);

signal a_row_fifo_we : std_logic;
signal a_row_fifo_din : std_logic_vector(511 downto 0);
signal a_row_fifo_re : std_logic;
signal a_row_fifo_valid : std_logic;
signal a_row_fifo_dout : std_logic_vector(511 downto 0);
signal a_row_fifo_count : std_logic_vector(FIFO_DEPTH_BITS-1 downto 0);
signal a_row_fifo_empty : std_logic;
signal a_row_fifo_full : std_logic;
signal a_row_fifo_almostfull: std_logic;
signal a_row_fifo_free_count : unsigned(FIFO_DEPTH_BITS-1 downto 0);

signal b_to_subtract_fifo_we : std_logic;
signal b_to_subtract_fifo_din : std_logic_vector(31 downto 0);
signal b_to_subtract_fifo_re : std_logic;
signal b_to_subtract_fifo_valid : std_logic;
signal b_to_subtract_fifo_dout : std_logic_vector(31 downto 0);
signal b_to_subtract_fifo_count : std_logic_vector(FIFO_DEPTH_BITS-1 downto 0);
signal b_to_subtract_fifo_empty : std_logic;
signal b_to_subtract_fifo_full : std_logic;
signal b_to_subtract_fifo_almostfull: std_logic;
signal b_to_subtract_fifo_free_count : unsigned(FIFO_DEPTH_BITS-1 downto 0);

component gather
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

    addresses : in std_logic_vector(1023 downto 0);
    number_of_samples : in std_logic_vector(31 downto 0);
    number_of_dimensions : in std_logic_vector(4 downto 0);
    gather_depth : in std_logic_vector(MAX_GATHER_DEPTH_BITS-1 downto 0));
end component;

component simple_dual_port_ram_single_clock
generic(
    DATA_WIDTH : integer := 32;
    ADDR_WIDTH : integer := 8);
port(
    clk :   in std_logic;
    raddr : in std_logic_vector(ADDR_WIDTH-1 downto 0);
    waddr : in std_logic_vector(ADDR_WIDTH-1 downto 0);
    data :  in std_logic_vector(DATA_WIDTH-1 downto 0);
    we :    in std_logic;
    q :     out std_logic_vector(DATA_WIDTH-1 downto 0));
end component;

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

component my_fp_converter
port (
    clock       : IN STD_LOGIC ;
    dataa       : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
    result      : OUT STD_LOGIC_VECTOR (31 DOWNTO 0));
end component;

component my_fp_converter27
port (
    clock       : IN STD_LOGIC ;
    dataa       : IN STD_LOGIC_VECTOR (31 DOWNTO 0);
    result      : OUT STD_LOGIC_VECTOR (31 DOWNTO 0));
end component;

component hybrid_dot_product
port (
    clk : in std_logic;
    resetn : in std_logic;

    trigger : in std_logic;
    dimension : in std_logic_vector(17 downto 0);
    vector1 : in std_logic_vector(511 downto 0);
    vector2 : in std_logic_vector(511 downto 0);
    result_almost_valid : out std_logic;
    result_valid : out std_logic;
    result : out std_logic_vector(31 downto 0));
end component;

component fp_subtract_mult
port (
    clk : in std_logic;
    trigger : in std_logic;
    dot_product : in std_logic_vector(31 downto 0);
    b_to_subtract : in std_logic_vector(31 downto 0);
    step_size : in std_logic_vector(31 downto 0);
    result_almost_valid : out std_logic;
    result_valid : out std_logic;
    result : out std_logic_vector(31 downto 0));
end component;

component fp_scalar_vector_mult
generic (VECTOR_SIZE : integer := 16);
port (
    clk : in std_logic;
    trigger : in std_logic;
    scalar : in std_logic_vector(31 downto 0);
    vector : in std_logic_vector(32*VECTOR_SIZE-1 downto 0);
    result_almost_valid : out std_logic;
    result_valid : out std_logic;
    result : out std_logic_vector(32*VECTOR_SIZE-1 downto 0));
end component;

component fixed_vector_subtract
generic (VECTOR_SIZE : integer := 16);
port (
    clk : in std_logic;
    trigger : in std_logic;
    vector1 : in std_logic_vector(32*VECTOR_SIZE-1 downto 0);
    vector2 : in std_logic_vector(32*VECTOR_SIZE-1 downto 0);
    result_almost_valid : out std_logic;
    result_valid : out std_logic;
    result : out std_logic_vector(32*VECTOR_SIZE-1 downto 0));
end component;

function convert_fp_to_signed(fp : std_logic_vector(31 downto 0)) return std_logic_vector is
variable exponent : unsigned(7 downto 0);
variable mantissa : unsigned(22 downto 0);
variable temp : unsigned(31 downto 0);
variable result : signed(31 downto 0);
begin
    exponent := unsigned(fp(30 downto 23));
    mantissa := unsigned(fp(22 downto 0));
    temp := X"00" & '1' & mantissa;
    if exponent >= 127 then
        temp := shift_left(temp, to_integer(exponent-127));
    else
        temp := shift_right(temp, to_integer(127-exponent));
    end if;
    result := signed(std_logic_vector(temp));
    if fp(31) = '1' then
        result := -result;
    end if;
    return std_logic_vector(result);
end function;

function convert_fp_to_signed27(fp : std_logic_vector(31 downto 0)) return std_logic_vector is
variable exponent : unsigned(7 downto 0);
variable mantissa : unsigned(22 downto 0);
variable temp : unsigned(35 downto 0);
variable result : signed(31 downto 0);
begin
    exponent := unsigned(fp(30 downto 23));
    mantissa := unsigned(fp(22 downto 0));
    temp := X"00" & '1' & mantissa & X"0";
    if exponent >= 127 then
        temp := shift_left(temp, to_integer(exponent-127));
    else
        temp := shift_right(temp, to_integer(127-exponent));
    end if;
    result := signed(std_logic_vector(temp(31 downto 0)));
    if fp(31) = '1' then
        result := -result;
    end if;
    return std_logic_vector(result);
end function;

begin

um_tx_rd_addr <= internal_tx_rd_addr when do_gather = '0' else gather_tx_rd_addr;
um_tx_rd_tag <= internal_tx_rd_tag when do_gather = '0' else gather_tx_rd_tag;
um_tx_rd_valid <= internal_tx_rd_valid when do_gather = '0' else gather_tx_rd_valid;
um_rx_rd_ready <= '1' when do_gather = '0' else gather_rx_rd_ready;

internal_rx_data <= um_rx_data when do_gather = '0' else gather_out_data;
internal_rx_rd_valid <= um_rx_rd_valid when do_gather = '0' else gather_out_valid;

internal_tx_rd_tag <= (others => '0');
um_tx_wr_tag <= (others => '0');

GATHERER: gather
port map (
    clk => clk,
    resetn => rst_n,

    enable => gather_enable,
    start => gather_start,

    -- TX RD
    um_tx_rd_addr => gather_tx_rd_addr,
    um_tx_rd_tag => gather_tx_rd_tag,
    um_tx_rd_valid => gather_tx_rd_valid,
    um_tx_rd_ready => um_tx_rd_ready,

    -- RX RD
    um_rx_rd_tag => um_rx_rd_tag,
    um_rx_data => um_rx_data,
    um_rx_rd_valid => um_rx_rd_valid,
    um_rx_rd_ready => gather_rx_rd_ready,

    number_of_requested_reads => gather_number_of_requested_reads,
    number_of_completed_reads => gather_number_of_completed_reads,
    out_valid => gather_out_valid,
    out_data => gather_out_data,

    addresses => source_addresses,
    number_of_samples => number_of_samples,
    number_of_dimensions => gather_number_of_dimensions,
    gather_depth => gather_depth);
gather_number_of_dimensions <= std_logic_vector( unsigned(dimension(4 downto 0)) + 1 );

source_addresses <=         um_params(1023 downto 0);
destination_address <=      um_params(1087 downto 1024);
mini_batch_size <=          um_params(1103 downto 1088);
step_size <=                um_params(1151 downto 1120);
number_of_epochs <=         um_params(1165 downto 1152);
dimension <=                um_params(1201 downto 1184);
number_of_samples <=        um_params(1247 downto 1216);
number_of_CL_to_process <=  um_params(1279 downto 1248);
binarize_b_value <=         um_params(1280);
b_value_to_binarize_to <=   um_params(1343 downto 1312);
do_gather <=                um_params(1344);
gather_depth <=             um_params(1383 downto 1376);

ififo: my_fifo
generic map (
    FIFO_WIDTH => 512,
    FIFO_DEPTH_BITS => FIFO_DEPTH_BITS,
    FIFO_ALMOSTFULL_THRESHOLD => 2**FIFO_DEPTH_BITS-30)
port map (
    clk => clk,
    reset_n => rst_n,

    we => ififo_we,
    din => ififo_din,
    re => ififo_re,
    valid => ififo_valid,
    dout => ififo_dout,
    count => ififo_count,
    empty => ififo_empty,
    full => ififo_full,
    almostfull => ififo_almostfull);

a_row_fifo_free_count <= FIFO_DEPTH - unsigned(a_row_fifo_count) when unsigned(a_row_fifo_count) < FIFO_DEPTH else (others => '0');

a_row_fifo_re <= minus_b_times_alpha_almost_valid;
a_row_fifo: my_fifo
generic map (
    FIFO_WIDTH => 512,
    FIFO_DEPTH_BITS => FIFO_DEPTH_BITS,
    FIFO_ALMOSTFULL_THRESHOLD => 2**FIFO_DEPTH_BITS-30)
port map (
    clk => clk,
    reset_n => rst_n,

    we => a_row_fifo_we,
    din => a_row_fifo_din,
    re => a_row_fifo_re,
    valid => a_row_fifo_valid,
    dout => a_row_fifo_dout,
    count => a_row_fifo_count,
    empty => a_row_fifo_empty,
    full => a_row_fifo_full,
    almostfull => a_row_fifo_almostfull);

b_to_subtract_fifo_re <= dot_product_result_almost_valid;
b_to_subtract_fifo: my_fifo
generic map (
    FIFO_WIDTH => 32,
    FIFO_DEPTH_BITS => FIFO_DEPTH_BITS,
    FIFO_ALMOSTFULL_THRESHOLD => 2**FIFO_DEPTH_BITS-30)
port map (
    clk => clk,
    reset_n => rst_n,

    we => b_to_subtract_fifo_we,
    din => b_to_subtract_fifo_din,
    re => b_to_subtract_fifo_re,
    valid => b_to_subtract_fifo_valid,
    dout => b_to_subtract_fifo_dout,
    count => b_to_subtract_fifo_count,
    empty => b_to_subtract_fifo_empty,
    full => b_to_subtract_fifo_full,
    almostfull => b_to_subtract_fifo_almostfull);

convert_to_fp: for k in 0 to 15 generate
    fp_converter: my_fp_converter
    port map (
        clock => clk,
        dataa => x_for_dot_product(32*k+31 downto 32*k),
        result => x_for_dot_product_fp(32*k+31 downto 32*k));
end generate convert_to_fp;

ififo_dout_valid <= ififo_dout when ififo_valid = '1' else (others => '0');

dot_product: hybrid_dot_product
port map (
    clk => clk,
    resetn => rst_n,

    trigger => ififo_valid,
    dimension => dimension,
    vector1 => ififo_dout_valid,
    vector2 => x_for_dot_product_fp,
    result_almost_valid => dot_product_result_almost_valid,
    result_valid => dot_product_result_valid,
    result => dot_product_result);

subtract_mult: fp_subtract_mult
port map (
    clk => clk,
    trigger => dot_product_result_valid,
    dot_product => dot_product_result,
    b_to_subtract => b_to_subtract_fifo_dout,
    step_size => step_size,
    result_almost_valid => minus_b_times_alpha_almost_valid,
    result_valid => minus_b_times_alpha_valid,
    result => minus_b_times_alpha);

scalar_vector_mult: fp_scalar_vector_mult
generic map (
    VECTOR_SIZE => 16)
port map (
    clk => clk,
    trigger => a_row_fifo_valid,
    scalar => minus_b_times_alpha,
    vector => a_row_fifo_dout,
    result_almost_valid => gradient_almost_valid,
    result_valid => gradient_valid,
    result => gradient);

vector_subtract: fixed_vector_subtract
generic map (
    VECTOR_SIZE => 16)
port map (
    clk => clk,
    trigger => gradient_valid_1d,
    vector1 => x_for_update,
    vector2 => gradient_fixed,
    result_almost_valid => new_x_almost_valid,
    result_valid => new_x_valid,
    result => new_x);

remainder <= 1 when unsigned(dimension(3 downto 0)) > 0 else 0;
accumulation_count <= to_integer(shift_right(unsigned(dimension), 4)) + remainder;

sample_index_to_read_unsigned <= to_unsigned(sample_index_to_read, 32);
gradient_valid_counter_unsigned <= to_unsigned(gradient_valid_counter, 32);


process(clk)
begin
if clk'event and clk = '1' then
    for k in 0 to 15 loop
        gradient_fixed(32*k+31 downto 32*k) <= convert_fp_to_signed(gradient(32*k+31 downto 32*k));
    end loop;
    gradient_valid_1d <= gradient_valid;

    NumberOfCLToProcess <= unsigned(number_of_CL_to_process);
    NumberOfEpochs <= unsigned(number_of_epochs);
    NumberOfSamples <= unsigned(number_of_samples);

    if rst_n = '0' then
        started <= '0';
    elsif start_um = '1' and started = '0' then
        started <= '1';
    end if;

    if started = '0' then
        internal_tx_rd_addr <= (others => '0');
        internal_tx_rd_valid <= '0';

        gather_enable <= '0';
        gather_start <= '0';

        NumberOfRequestedReads <= (others => '0');
        NumberOfCompletedReads <= (others => '0');
        NumberOfRequestedWrites <= (others => '0');
        NumberOfCompletedWrites <= (others => '0');
        NumberOfEpochsCompleted <= (others => '0');

        sample_index_to_read <= 0;
        gradient_valid_counter <= 0;

        count_upto_a_whole_row <= 0;
        new_CL_available <= (others => '0');
        new_row_available <= (others => '0');
        
        x(x_reset_index) <= (others => '0');
        x_loading(x_reset_index) <= (others => '0');
        if x_reset_index = X_CL_COUNT-1 then
            x_reset_index <= 0;
        else
            x_reset_index <= x_reset_index + 1;
        end if;
        x_index1 <= 0;
        x_index2 <= 0;
        x_index3 <= 0;
        x_for_dot_product <= (others => '0');
        x_for_update <= (others => '0');

        write_back_the_model <= '0';
        write_back_index <= 0;
        model_is_written <= '0';

        ififo_we <= '0';
        ififo_re <= '0';

        a_row_fifo_we <= '0';

        b_to_subtract_fifo_we <= '0';

        um_done <= '0';
    else
        internal_tx_rd_valid <= '0';
        if do_gather = '0' and NumberOfRequestedReads < NumberOfCLToProcess and um_tx_wr_ready = '1' and um_tx_rd_ready = '1' and NumberOfRequestedReads - NumberOfCompletedReads < a_row_fifo_free_count then
            internal_tx_rd_valid <= '1';
            internal_tx_rd_addr <= std_logic_vector(unsigned(source_addresses(63 downto 6)) + NumberOfRequestedReads);
            NumberOfRequestedReads <= NumberOfRequestedReads + 1;
        end if;

        gather_enable <= '0';
        if do_gather = '0' then
            if internal_rx_rd_valid = '1' then
                NumberOfCompletedReads <= NumberOfCompletedReads + 1;
            end if;
        else
            gather_start <= '1';
            if NumberOfRequestedReads - NumberOfCompletedReads < a_row_fifo_free_count then
                gather_enable <= '1';
            end if;
            NumberOfRequestedReads <= unsigned(gather_number_of_requested_reads);
            NumberOfCompletedReads <= unsigned(gather_number_of_completed_reads);
        end if;

        ififo_we <= '0';
        a_row_fifo_we <= '0';
        b_to_subtract_fifo_we <= '0';
        new_CL_available(0) <= '0';
        new_row_available(0) <= '0';
        if internal_rx_rd_valid = '1' then
            ififo_we <= '1';
            a_row_fifo_we <= '1';
            
            new_CL_available(0) <= '1';

            if count_upto_a_whole_row = accumulation_count-1 then
                count_upto_a_whole_row <= 0;
                new_row_available(0) <= '1';
                
                b_to_subtract_fifo_we <= '1';
                if binarize_b_value = '0' then
                    b_to_subtract_fifo_din <= internal_rx_data(511 downto 480);
                else
                    if internal_rx_data(511 downto 480) = b_value_to_binarize_to then
                        b_to_subtract_fifo_din <= X"3f800000";
                    else
                        b_to_subtract_fifo_din <= X"00000000";
                    end if;
                end if;

                ififo_din <= X"00000000" & internal_rx_data(479 downto 0);
                a_row_fifo_din <= X"00000000" & internal_rx_data(479 downto 0);
            else
                ififo_din <= internal_rx_data;
                a_row_fifo_din <= internal_rx_data;
                count_upto_a_whole_row <= count_upto_a_whole_row + 1;
            end if;
        end if;

        ififo_re <= '0';
        if new_CL_available(3) = '1' then
            ififo_re <= '1';
        end if;

        if new_CL_available(0) = '1' then
            x_for_dot_product <= x(x_index1);
            if x_index1 = accumulation_count-1 then
                x_index1 <= 0;
            else
                x_index1 <= x_index1 + 1;
            end if;
        end if;

        if gradient_valid = '1' then
            if new_x_valid = '1' and x_index2 = x_index3 then
                x_for_update <= new_x;
            else
                x_for_update <= x_loading(x_index2);
            end if;
            if x_index2 = accumulation_count-1 then
                x_index2 <= 0;
                if gradient_valid_counter = NumberOfSamples-1 then
                    gradient_valid_counter <= 0;
                else
                    gradient_valid_counter <= gradient_valid_counter + 1;
                end if;
            else
                x_index2 <= x_index2 + 1;
            end if;
        end if;

        if new_x_valid = '1' then
            if ( std_logic_vector(sample_index_to_read_unsigned(15 downto 0)) and mini_batch_size(15 downto 0) ) = mini_batch_size(15 downto 0) or sample_index_to_read = NumberOfSamples-1 then
                x(x_index3) <= new_x;
            end if;

            x_loading(x_index3) <= new_x;
            if x_index3 = accumulation_count-1 then
                x_index3 <= 0;
                if sample_index_to_read = NumberOfSamples-1 then
                    sample_index_to_read <= 0;
                    write_back_the_model <= '1';
                else
                    sample_index_to_read <= sample_index_to_read + 1;
                end if;
            else
                x_index3 <= x_index3 + 1;
            end if;
        end if;

        for k in 1 to 9 loop
            new_CL_available(k) <= new_CL_available(k-1);
            new_row_available(k) <= new_row_available(k-1);
        end loop;

        um_tx_wr_valid <= '0';
        if write_back_the_model = '1' and um_tx_wr_ready = '1' and new_CL_available(0) /= '1' then
            um_tx_wr_valid <= '1';
            um_tx_data <= x(write_back_index);
            um_tx_wr_addr <= std_logic_vector(unsigned(destination_address(63 downto 6)) + NumberOfRequestedWrites);
            if write_back_index = accumulation_count-1 then
                write_back_index <= 0;
                write_back_the_model <= '0';

                NumberOfEpochsCompleted <= NumberOfEpochsCompleted + 1;
                if NumberOfEpochsCompleted = NumberOfEpochs-1 then
                    model_is_written <= '1';
                else
                    NumberOfRequestedReads <= (others => '0');
                    NumberOfCompletedReads <= (others => '0');
                    gather_start <= '0';
                end if;
            else
                write_back_index <= write_back_index + 1;
            end if;
            NumberOfRequestedWrites <= NumberOfRequestedWrites + 1;
        end if;

        if um_rx_wr_valid = '1' then
            NumberOfCompletedWrites <= NumberOfCompletedWrites + 1;
        end if;

        if NumberOfCompletedWrites = NumberOfRequestedWrites and NumberOfEpochsCompleted = NumberOfEpochs and model_is_written = '1' then
            um_done <= '1';
            started <= '0';
        end if;

    end if;
end if;
end process;


end architecture;