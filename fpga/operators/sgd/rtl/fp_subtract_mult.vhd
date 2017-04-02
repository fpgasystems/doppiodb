library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity fp_subtract_mult is
port (
	clk : in std_logic;
	trigger : in std_logic;
	dot_product : in std_logic_vector(31 downto 0);
	b_to_subtract : in std_logic_vector(31 downto 0);
	step_size : in std_logic_vector(31 downto 0);
	result_almost_valid : out std_logic;
	result_valid : out std_logic;
	result : out std_logic_vector(31 downto 0));
end fp_subtract_mult;

architecture behavioral of fp_subtract_mult is

signal internal_trigger : std_logic_vector(11 downto 0);

signal dot_product_minus_b : std_logic_vector(31 downto 0);

component my_fp_adder
port (
	add_sub		: IN STD_LOGIC ;
	clock		: IN STD_LOGIC ;
	dataa		: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	datab		: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	result		: OUT STD_LOGIC_VECTOR (31 DOWNTO 0));
end component;

component my_fp_mult
port (
	clock		: IN STD_LOGIC ;
	dataa		: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	datab		: IN STD_LOGIC_VECTOR (31 DOWNTO 0);
	result		: OUT STD_LOGIC_VECTOR (31 DOWNTO 0));
end component;

begin

subtract: my_fp_adder
port map (
	add_sub => '0',
	clock => clk,
	dataa => dot_product,
	datab => b_to_subtract,
	result => dot_product_minus_b);

step_size_mult: my_fp_mult
port map (
	clock => clk,
	dataa => step_size,
	datab => dot_product_minus_b,
	result => result);

result_almost_valid <= internal_trigger(8);
result_valid <= internal_trigger(11);

process(clk)
begin
if clk'event and clk = '1' then
	internal_trigger(0) <= trigger;
	for k in 1 to 11 loop
		internal_trigger(k) <= internal_trigger(k-1);
	end loop;
end if;
end process;

end architecture;