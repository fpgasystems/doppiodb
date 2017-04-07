library IEEE;
use IEEE.STD_LOGIC_1164.all;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use IEEE.numeric_std.ALL;
use work.conf.ALL;

entity corepipe is
 generic(NUM_CORES : integer := 128;
         NumBitsDimCounterxK : integer := 5);
  port(
    ClkxCI           : in  std_logic                                    := '0';
    RstxRI           : in  std_logic                                    := '0';
    TupleValidxEI    : in  std_logic                                    := '0';
    TupleDataxDI     : in  std_logic_vector(TupleBusWidthxK-1 downto 0) := (others => '0');
    TupleNumDimsI    : in  std_logic_vector(NumBitsDimCounterxK-1 downto 0) := (others => '0');
    TupleDimsCmpsI   : in  std_logic                                    := '0';
    TupleValidxEO    : out std_logic                                    := '0';
    TupleDataxDO     : out std_logic_vector(TupleBusWidthxK-1 downto 0) := (others => '0');
    WinTupleValidxEO : out std_logic                                    := '0';
    WinTupleDataxDO  : out std_logic_vector(TupleBusWidthxK-1 downto 0) := (others => '0');
    EmptyxEO         : out std_logic
    );
end corepipe;

architecture Implementation of corepipe is
  
  -----------------------------------------------------------------------------
  -- tuple pipeline
  -----------------------------------------------------------------------------
  
  signal TupleValidPipexE : std_logic_vector(NUM_CORES downto 0) := (others => '0');
  signal TupleDimsCmpsPipexE : std_logic_vector(NUM_CORES downto 0) := (others => '0');

  type TupleNumDimsPipexTYPE is array (0 to NUM_CORES) of std_logic_vector(NumBitsDimCounterxK-1 downto 0);
  signal TupleNumDimsPipexD  : TupleNumDimsPipexTYPE;

  type TupleDataPipexTYPE is array (0 to NUM_CORES) of std_logic_vector(TupleBusWidthxK-1 downto 0);
  signal TupleDataPipexD  : TupleDataPipexTYPE;

  -----------------------------------------------------------------------------
  -- BRAM pipeline
  -----------------------------------------------------------------------------
  
  signal CopyValidPipexE : std_logic_vector(NUM_CORES downto 0);
  type BRAMDataPipexTYPE is array (0 to NUM_CORES) of std_logic_vector(BramDataBusWidthxK-1 downto 0);
  signal BRAMDataPipexD  : BRAMDataPipexTYPE;
  
  signal CopySentxE     : std_logic_vector(NUM_CORES downto 0);
  signal CopyReceivedxE : std_logic_vector(NUM_CORES downto 0);

  -----------------------------------------------------------------------------
  -- Core state pipeline
  -----------------------------------------------------------------------------
  
  signal CoreStateReg1xD : BRAMDataPipexTYPE;
  signal CoreStateReg2xD : BRAMDataPipexTYPE;

  type CoreStatePipexTYPE is array (0 to NUM_CORES) of CoreStatexTYPE;
  signal CoreStatePipexD : CoreStatePipexTYPE;

  -----------------------------------------------------------------------------
  -- Dim Counter
  -----------------------------------------------------------------------------
  
  signal DimCnt : std_logic_vector(NumBitsDimCounterxK-1 downto 0);
  
component core
  generic(
    isPhysicallyLast  : boolean := false;
    isPhysicallyFirst : boolean := false;
    NumBitsDimCounterxK: integer := 5
  );

  port(
    CLKxCI           : in  std_logic                                       := '0';
    RSTxRI           : in  std_logic                                       := '0';
    TupleValidxEI    : in  std_logic                                       := '0';
    TupleDataxDI     : in  std_logic_vector(TupleBusWidthxK-1 downto 0)    := (others => '0');
    TupleNumDimsI    : in  std_logic_vector(NumBitsDimCounterxK-1 downto 0):= (others => '0');
    TupleDimsCmpsI   : in  std_logic                                       := '0';         
    TupleValidxEO    : out std_logic                                       := '0';
    TupleDataxDO     : out std_logic_vector(TupleBusWidthxK-1 downto 0)    := (others => '0');
    TupleNumDimsO    : out std_logic_vector(NumBitsDimCounterxK-1 downto 0):= (others => '0');
    TupleDimsCmpsO   : out std_logic                                       := '0'; 
    CopyValidxEI     : in  std_logic                                       := '0';
    CopyValidxEO     : out std_logic                                       := '0';
    CopySentxEI      : in  std_logic                                       := '0';
    CopySentxEO      : out std_logic                                       := '0';
    CopyReceivedxEI  : in  std_logic                                       := '0';
    CopyReceivedxEO  : out std_logic                                       := '0';
    BRAMDataxDI      : in  std_logic_vector(BramDataBusWidthxK-1 downto 0) := (others => '0');
    BRAMDataxDO      : out std_logic_vector(BramDataBusWidthxK-1 downto 0) := (others => '0');
    CoreStateReg1xDI : in  std_logic_vector(BramDataBusWidthxK-1 downto 0) := (others => '0');
    CoreStateReg1xDO : out std_logic_vector(BramDataBusWidthxK-1 downto 0) := (others => '0');
    CoreStateReg2xDI : in  std_logic_vector(BramDataBusWidthxK-1 downto 0) := (others => '0');
    CoreStateReg2xDO : out std_logic_vector(BramDataBusWidthxK-1 downto 0) := (others => '0');
    CoreStatexDI     : in  CoreStatexTYPE                                  := L_FREE;
    CoreStatexDO     : out CoreStatexTYPE                                  := L_FREE
    );
end component;

begin

  -----------------------------------------------------------------------------
  -- set values for start and end of pipeline
  -----------------------------------------------------------------------------

  TupleValidPipexE(0)    <= TupleValidxEI;
  TupleDataPipexD(0)     <= TupleDataxDI;
  TupleDimsCmpsPipexE(0) <= TupleDimsCmpsI;
  TupleNumDimsPipexD(0)  <= TupleNumDimsI;
  TupleValidxEO          <= TupleValidPipexE(NUM_CORES);
  TupleDataxDO           <= TupleDataPipexD(NUM_CORES);
  
  CopyValidPipexE(NUM_CORES) <= '0';
  BRAMDataPipexD(NUM_CORES)  <= (others => '0');

  CopySentxE(NUM_CORES) <= '0';
  CopyReceivedxE(0)      <= '0';

  CoreStateReg1xD(NUM_CORES) <= (others => '0');
  CoreStateReg2xD(NUM_CORES) <= (others => '0');
  
  CoreStatePipexD(NUM_CORES) <= L_FREE;

  WinTupleValidxEO <= CopyValidPipexE(0);
  
  -----------------------------------------------------------------------------
  -- count dimensions
  -----------------------------------------------------------------------------
  
  process(CLKxCI, RSTxRI)
  begin
    if rising_edge(CLKxCI) then
      if RSTxRI = '1' then
        DimCnt <= (others => '0');
      else
        if CopyValidPipexE(0) = '1' then
          if DimCnt = (TupleNumDimsI) then
            DimCnt <= std_logic_vector(to_unsigned(0, NumBitsDimCounterxK));
          else
            DimCnt <= DimCnt + 1;
          end if;
        end if;
      end if;
    end if;
  end process;

  --WinTupleDataxDO <= BRAMDataPipexD(0);
  
  winTupleS : process( CoreStateReg1xD(0),  BRAMDataPipexD(0), DimCnt)
  begin
    if DimCnt = TupleNumDimsI then
      WinTupleDataxDO <= CoreStateReg1xD(0);
    else
      WinTupleDataxDO <= BRAMDataPipexD(0);
    end if;
  end process ; -- winTupleS
  
  --with DimCnt select
  --  WinTupleDataxDO <=
  --  CoreStateReg1xD(0) when std_logic_vector(to_unsigned(TupleNumDimsI, NumBitsDimCounterxK)),
  --  BRAMDataPipexD(0)  when others;
  
  -----------------------------------------------------------------------------
  -- instantiate N cores of the pipeline
  -----------------------------------------------------------------------------
  
  core_pipe : for i in 0 to NUM_CORES-1 generate
    core_i : core
      generic map (
        isPhysicallyLast  => (i = (NUM_CORES-1)),
        isPhysicallyFirst => (i = 0),
        NumBitsDimCounterxK => NumBitsDimCounterxK
      )
      port map (
        CLKxCI           => CLKxCI,
        RSTxRI           => RSTxRI,
        TupleValidxEI    => TupleValidPipexE(i),
        TupleDataxDI     => TupleDataPipexD(i),
        TupleNumDimsI    => TupleNumDimsPipexD(i),
        TupleDimsCmpsI   => TupleDimsCmpsPipexE(i),
        TupleValidxEO    => TupleValidPipexE(i+1),
        TupleDataxDO     => TupleDataPipexD(i+1),
        TupleNumDimsO    => TupleNumDimsPipexD(i+1),
        TupleDimsCmpsO   => TupleDimsCmpsPipexE(i+1),
        CopyValidxEI     => CopyValidPipexE(i+1),
        CopyValidxEO     => CopyValidPipexE(i),
        CopySentxEI      => CopySentxE(i+1),
        CopySentxEO      => CopySentxE(i),
        CopyReceivedxEI  => CopyReceivedxE(i),
        CopyReceivedxEO  => CopyReceivedxE(i+1),
        BRAMDataxDI      => BRAMDataPipexD(i+1),
        BRAMDataxDO      => BRAMDataPipexD(i),
        CoreStateReg1xDI => CoreStateReg1xD(i+1),
        CoreStateReg1xDO => CoreStateReg1xD(i),
        CoreStateReg2xDI => CoreStateReg2xD(i+1),
        CoreStateReg2xDO => CoreStateReg2xD(i),
        CoreStatexDI     => CoreStatePipexD(i+1),
        CoreStatexDO     => CoreStatePipexD(i)
      );
  end generate core_pipe;

  EmptyxEO <= '1' when CoreStatePipexD(0) = L_FREE else '0';
  
end Implementation;
