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
library IEEE;
use IEEE.STD_LOGIC_1164.all;

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
--use IEEE.STD_LOGIC_SIGNED.ALL;
--use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.NUMERIC_STD.ALL;
use work.conf.ALL;

entity core is
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
end core;

architecture Behavioral of core is

  -----------------------------------------------------------------------------
  -- BRAM signals
  -----------------------------------------------------------------------------
  
  signal RamAddrxDI : std_logic_vector(BramAddrBusWidthxK-1 downto 0);
  signal RamDataxDI : std_logic_vector(BramDataBusWidthxK-1 downto 0);
  signal RamEnxDI   : std_logic;
  signal RamWexDI   : std_logic_vector(BramWriteEnableWidthxK-1 downto 0);
  signal RamDataxDO : std_logic_vector(BramDataBusWidthxK-1 downto 0);

  -----------------------------------------------------------------------------
  -- State of the Core
  -----------------------------------------------------------------------------
  
  signal CoreStatexS : CoreStatexTYPE;

  -----------------------------------------------------------------------------
  -- Misc Signals
  -----------------------------------------------------------------------------

  signal DimCnt        : std_logic_vector(NumBitsDimCounterxK-1 downto 0);
  signal CoreStateReg1 : std_logic_vector(TupleBusWidthxK-1 downto 0);
  signal CoreStateReg2 : std_logic_vector(TupleBusWidthxK-1 downto 0);

  -- --------------------------------------------------------------------------
  -- Debug
  -- --------------------------------------------------------------------------
  
  --signal debugHasSmaller : std_logic;
  --signal debugHasLarger  : std_logic;


  component singleportbram_sk is 
  generic(
    DATA_WIDTH: integer := 32;
    ADDR_WIDTH: integer := 9
); 
port(
    clk:  in std_logic;
    rst:  in std_logic;
    we:   in std_logic;
    re:   in std_logic;
    addr: in std_logic_vector(ADDR_WIDTH-1 downto 0);
    din:  in std_logic_vector(DATA_WIDTH-1 downto 0);
    dout: out std_logic_vector(DATA_WIDTH-1 downto 0)
);

end component singleportbram_sk;
  
begin

  -----------------------------------------------------------------------------
  -- count dimensions
  -----------------------------------------------------------------------------
  
  process(CLKxCI, RSTxRI)
  begin
    if rising_edge(CLKxCI) then
      if RSTxRI = '1' then
        DimCnt <= (others => '0');
      else
        if TupleValidxEI = '1' then
          if DimCnt = (TupleNumDimsI+1) then
            DimCnt <= std_logic_vector(to_unsigned(0, NumBitsDimCounterxK));
          else
            DimCnt <= DimCnt + 1;
          end if;
        end if;
      end if;
    end if;
  end process;
  
  -----------------------------------------------------------------------------
  -- instantiate 18 Kilobit Single-Port-BRAM
  -----------------------------------------------------------------------------

 bram18Kb : singleportbram_sk PORT MAP (
    clk     => CLKxCI,
    rst     => RSTxRI,
    we      => RamWexDI(0),
    re      => RamEnxDI,
    addr    => RamAddrxDI,
    din     => RamDataxDI,
    dout    => RamDataxDO
  );

  -- --------------------------------------------------------------------------
  -- core FSM
  -- --------------------------------------------------------------------------
  
  process(CLKxCI, RSTxRI)
    
    variable winHasBetter   : boolean;
    variable tupleHasBetter : boolean;
    variable copyReg1       : boolean;
    variable roundDiff      : signed(30 downto 0);
    variable tupleDiff      : signed(31 downto 0);
    
  begin
    if rising_edge(CLKxCI) then
      if RSTxRI = '1' then 
        
        TupleValidxEO <= '0';
        CoreStatexS   <= L_FREE;
        RamAddrxDI    <= (others => '0');
        RamWexDI      <= (others => '1');
        winHasBetter  := false;
        tupleHasBetter:= false;
        copyReg1      := false;
        roundDiff     := (others => '0');
        tupleDiff     := (others => '0');
        
      else

        --if hasSmaller then
        --  debugHasSmaller <= '1';
        --else
        --  debugHasSmaller <= '0';
        --end if;

        --if hasGreater then
        --  debugHasLarger <= '1';
        --else
        --  debugHasLarger <= '0';
        --end if;
        
        -- propagate TupleValidxDI and TupleDataxDI through pipeline
        TupleValidxEO <= TupleValidxEI;
        TupleDataxDO  <= TupleDataxDI;
        TupleNumDimsO <= TupleNumDimsI;
        TupleDimsCmpsO <= TupleDimsCmpsI;

        -- default : copy data not sent or recieved
        if TupleValidxEI = '1' then
            CopySentxEO     <= '0';
        end if;
        CopyReceivedxEO <= '0';
        
        case CoreStatexS is
          
          -- --------------------------------------------------------------------------
          -- L_FREE
          -- --------------------------------------------------------------------------
          -- Free and last in pipeline
          -- RamWexDI -> In this state we write tuples to the BRAM
          --             If the tuple was invalid, we overwrite it, else we change to state P_OCCP
          -- --------------------------------------------------------------------------
          
          when L_FREE =>

            if TupleValidxEI = '1' then  -- we only update this state when tuple is valid

              -- round counter {31:1}, info bit {0} (n+2) -------------------------------
              if DimCnt = (TupleNumDimsI+1) then
                CoreStateReg2 <= TupleDataxDI;

                -- Tuple valid
                if TupleDataxDI(0) = '1' then
                  TupleDataxDO(0) <= '0';           -- invalidate data point
                  RamAddrxDI      <= RamAddrxDI+1;  -- increment BRAM address
                  CoreStatexS     <= P_OCCP;        -- change state

                --  Tuple invalid
                else
                  RamWexDI <= (others => '1');  -- restart writing
                end if;
                
              -- tuple counter (n+1) ----------------------------------------------------
              elsif DimCnt = (TupleNumDimsI) then
                CoreStateReg1 <= TupleDataxDI;

              -- last dimension (n) -----------------------------------------------------
              elsif DimCnt = (TupleNumDimsI-1) then
                -- after this one stop writing to BRAM, reset BRAM Address = 0
                RamAddrxDI  <= (others => '0');
                RamWexDI    <= (others => '0');
                CopySentxEO <= '1';     -- notify predecessor that copy was sent, this is to propagate L_FREE to the front of the pipeline
                
              -- dimensions 1 to (n-1) --------------------------------------------------
              else
                -- keep writing to BRAM, increment BRAM address
                RamAddrxDI <= RamAddrxDI+1;
              end if;

            end if;


          -- --------------------------------------------------------------------------
          -- N_FREE
          -- --------------------------------------------------------------------------
          -- Free but not last in pipeline
          -- RamWexDI -> In this state we write copies from successors to the BRAM
          --             If copy was successful we change to state of successor
          --             If successor was L_FREE we need to keep on writing, otherwise we stop writing (S_OCCP, P_OCCP)
          -- --------------------------------------------------------------------------
            
          when N_FREE =>

            if CopyValidxEI = '1' then  -- we only update this state when successor copies data into this core

              -- tuple counter (n+1) ----------------------------------------------------
              if copyReg1 then
                CoreStateReg1 <= CoreStateReg1xDI;
                CoreStateReg2 <= CoreStateReg2xDI;
                
                -- switch to state of successor
                if (CopySentxEI = '1') and ((CoreStatexDI /= L_FREE) or (TupleDataxDI(0) = '0')) then
                  CopyReceivedxEO <= '1';
                  RamAddrxDI      <= std_logic_vector(to_unsigned(1, BramAddrBusWidthxK));
                  CoreStatexS     <= CoreStatexDI;

                  -- bug!! ned to reset RamAddrxDI to 0 if we switch to L_FREE
                  if CoreStatexDI = L_FREE then
                    RamAddrxDI <= std_logic_vector(to_unsigned(0, BramAddrBusWidthxK));
                    RamWexDI   <= (others => '1');
                  end if;
                  
                -- stay in this state and start writing again
                else
                  RamWexDI <= (others => '1');
                end if;

                copyReg1 := false;

                
              -- last dimension (n) -----------------------------------------------------
              elsif RamAddrxDI = (TupleNumDimsI-1) then
                RamWexDI   <= (others => '0');  -- stop writing to BRAM
                RamAddrxDI <= (others => '0');  -- reset BRAM address
                copyReg1   := true;

              -- dimensions 1 to (n-1) --------------------------------------------------
              else
                RamAddrxDI <= RamAddrxDI+1;
              end if;
              
            end if;

          
          -- --------------------------------------------------------------------------
          -- P_OCCP
          -- --------------------------------------------------------------------------
          -- Potential skyline tuple
          -- RamWexDI -> In this state we don't write to BRAM
          -- --------------------------------------------------------------------------
            
          when P_OCCP =>

            -- this core has been copied to its predecessor and can be freed
            if CopyReceivedxEI = '1' then

              -- restart writing
              RamWexDI <= (others => '1');
              
              -- previous core was last, and data point was dominated
              --if CoreStatexDI = L_FREE and (hasSmaller and (not hasGreater)) then
              --  CoreStatexS <= L_FREE;
              -- otherwise we have to make it N_FREE unless this is physically
              -- the last core in the pipeline
              --else
              --  if isPhysicallyLast then
              --    CoreStatexS <= L_FREE;
              --  else
              --    CoreStatexS <= N_FREE;
              --  end if;
              --end if;

              if isPhysicallyLast then
                CoreStatexS <= L_FREE;
              else
                CoreStatexS <= N_FREE;
              end if;

              -- window point dominates -> invalidate data point
              if winHasBetter and (not tupleHasBetter) then
                TupleDataxDO(0) <= '0';
              end if;

              -- reset comparator values
              winHasBetter   := false;
              tupleHasBetter := false;
              roundDiff      := (others => '0');
              tupleDiff      := (others => '0');

            -- we only update this state when tuple is valid
            elsif TupleValidxEI = '1' then
              
              -- round counter {31:1}, info bit {0} (n+2) -------------------------------
              if DimCnt = (TupleNumDimsI+1) then

                RamAddrxDI <= RamAddrxDI+1;  -- increment BRAM address
                
                -- window point dominates -> invalidate data point
                if winHasBetter and (not tupleHasBetter) then
                  TupleDataxDO(0) <= '0';  -- invalidate data point
                  
                -- data point dominates -> free this bucket
                elsif (not winHasBetter) and tupleHasBetter then
                  
                  RamAddrxDI <= (others => '0');  -- reset BRAM address = 0
                  RamWexDI   <= (others => '1');  -- restart writing

                  -- free core
                  if isPhysicallyLast then
                    CoreStatexS <= L_FREE;
                  else
                    CoreStatexS <= N_FREE;
                  end if;
                  
                end if;

                -- check if we can output this tuple as part of the skyline
                roundDiff := signed(TupleDataxDI(31 downto 1)) - signed(CoreStateReg2(31 downto 1));

                -- TODO: if timing problems : see if we can have this work with roundDiff = 2 ...
                
                -- if (roundDiff = 2) or ((roundDiff = 1) and (tupleDiff > 0)) then 
                if (roundDiff >= 2) or ((roundDiff = 1) and (tupleDiff > 0)) then
                  CoreStatexS <= S_OCCP;
                end if;
                
                -- reset comparator values
                winHasBetter   := false;
                tupleHasBetter := false;
                roundDiff      := (others => '0');
                tupleDiff      := (others => '0');
                
                
              -- tuple counter (n+1) ----------------------------------------------------
              elsif DimCnt = (TupleNumDimsI) then

                tupleDiff := signed(TupleDataxDI) - signed(CoreStateReg1);
                
              -- last dimension (n) -----------------------------------------------------
              elsif DimCnt = (TupleNumDimsI-1) then 
                -- do comparisons
                if TupleDimsCmpsI = '1' then
                  if unsigned(RamDataxDO) > unsigned(TupleDataxDI) then
                    winHasBetter := true;
                  end if;

                  if unsigned(RamDataxDO) < unsigned(TupleDataxDI) then
                    tupleHasBetter := true;
                  end if;
                else
                  if unsigned(RamDataxDO) < unsigned(TupleDataxDI) then
                    winHasBetter := true;
                  end if;

                  if unsigned(RamDataxDO) > unsigned(TupleDataxDI) then
                    tupleHasBetter := true;
                  end if;
                end if;

                -- if window tuple has smaller dims or does not have greater dims, it was not dominated -> copy valid
                if winHasBetter or (not tupleHasBetter) then
                  CopySentxEO <= '1';
                end if;

              -- second last dimension (n-1) --------------------------------------------
              elsif DimCnt = (TupleNumDimsI-2) then 
                -- do comparisons
                if TupleDimsCmpsI = '1' then
                  if unsigned(RamDataxDO) > unsigned(TupleDataxDI) then
                    winHasBetter := true;
                  end if;

                  if unsigned(RamDataxDO) < unsigned(TupleDataxDI) then
                    tupleHasBetter := true;
                  end if;
                else
                  if unsigned(RamDataxDO) < unsigned(TupleDataxDI) then
                    winHasBetter := true;
                  end if;

                  if unsigned(RamDataxDO) > unsigned(TupleDataxDI) then
                    tupleHasBetter := true;
                  end if;
                end if;
                
                -- reset BRAM address = 0
                RamAddrxDI <= (others => '0');

              -- dimensions 1 to (n-2) --------------------------------------------------
              else
                -- do comparisons
                if TupleDimsCmpsI = '1' then
                  if unsigned(RamDataxDO) > unsigned(TupleDataxDI) then
                    winHasBetter := true;
                  end if;

                  if unsigned(RamDataxDO) < unsigned(TupleDataxDI) then
                    tupleHasBetter := true;
                  end if;
                else
                  if unsigned(RamDataxDO) < unsigned(TupleDataxDI) then
                    winHasBetter := true;
                  end if;

                  if unsigned(RamDataxDO) > unsigned(TupleDataxDI) then
                    tupleHasBetter := true;
                  end if;
                end if;

                -- increment BRAM address
                RamAddrxDI <= RamAddrxDI+1;
              end if;

            end if;

          
          -- --------------------------------------------------------------------------
          -- S_OCCP
          -- --------------------------------------------------------------------------
          -- Definitively a skyline tuple
          -- RamWexDI -> In this state we don't write to BRAM
          -- --------------------------------------------------------------------------
            
          when S_OCCP =>
            
            -- if this is the first core in the pipeline, we can output the skyline tuple and free the core
            if isPhysicallyFirst then

              if TupleValidxEI = '1' then
                
                if DimCnt = (TupleNumDimsI+1) then

                  RamAddrxDI <= (others => '0');  -- reset BRAM address = 0
                  RamWexDI   <= (others => '1');  -- restart writing
                  
                  --if CoreStatexDI = L_FREE then
                  --  CoreStatexS <= L_FREE;
                  --else
                  --  CoreStatexS <= N_FREE;
                  --end if;

                  if isPhysicallyLast then
                    CoreStatexS <= L_FREE;
                  else
                    CoreStatexS <= N_FREE;
                  end if;

                elsif DimCnt = (TupleNumDimsI) then
                  RamAddrxDI <= (others => '0');  -- reset BRAM address = 0
                elsif DimCnt = (TupleNumDimsI-1) then
                  RamAddrxDI <= (others => '0');  -- reset BRAM address = 0
                elsif DimCnt = (TupleNumDimsI-2) then
                  RamAddrxDI <= (others => '0');  -- reset BRAM address = 0
                else
                  RamAddrxDI <= RamAddrxDI+1;
                end if;

              end if;
              
            -- if this is not the first core, we propagate the core to the front as in state P_OCCP
            else

              if CopyReceivedxEI = '1' then

                -- restart writing
                RamWexDI <= (others => '1');
                
                --if CoreStatexDI = L_FREE then
                --  CoreStatexS <= L_FREE;
                --else
                --  if isPhysicallyLast then
                --    CoreStatexS <= L_FREE;
                --  else
                --    CoreStatexS <= N_FREE;
                --  end if;
                --end if;

                if isPhysicallyLast then
                  CoreStatexS <= L_FREE;
                else
                  CoreStatexS <= N_FREE;
                end if;
                
              -- we only update this state when tuple is valid
              elsif TupleValidxEI = '1' then
                
                -- round counter {31:1}, info bit {0} (n+2) -------------------------------
                if DimCnt = (TupleNumDimsI+1) then
                  RamAddrxDI <= RamAddrxDI+1;  -- increment BRAM address

                -- tuple counter (n+1) ----------------------------------------------------
                elsif DimCnt = (TupleNumDimsI) then

                  -- don't do anything here
                  
                -- last dimension (n) -----------------------------------------------------
                elsif DimCnt = (TupleNumDimsI-1) then 
                  CopySentxEO <= '1';     -- notify predecessor that copy was sent

                -- second last dimension (n-1) --------------------------------------------
                elsif DimCnt = (TupleNumDimsI-2) then 
                  RamAddrxDI <= (others => '0');-- reset BRAM address = 0
                  
                -- dimensions 1 to (n-2) --------------------------------------------------
                else
                  RamAddrxDI <= RamAddrxDI+1; -- increment BRAM address
                  
                end if;

              end if;
            end if;  
        end case;
        
      end if;
    end if;
  end process;

  -- enable BRAM and set write data to BRAM
  RamEnxDI   <= CopyValidxEI when CoreStatexS = N_FREE else TupleValidxEI;  -- BRAM enable
  RamDataxDI <= BRAMDataxDI  when CoreStatexS = N_FREE else TupleDataxDI;   -- BRAM input data (writes)
  
  -- for first core, valid when this was a window tuple
  core0_BRAMValid : if isPhysicallyFirst generate
    CopyValidxEO <= '1' when (CoreStatexS = S_OCCP) and (TupleValidxEI = '1') and (DimCnt /= (TupleNumDimsI+1)) else '0';
  end generate;

  -- for other cores, valid when BRAM data and register content is valid
  corei_BRAMValid : if not isPhysicallyFirst generate
    --CopyValidxEO <= '1' when (TupleValidxEI = '1') and ((CoreStatexS = P_OCCP) or (CoreStatexS = S_OCCP)) and (DimCnt /= (NumTupleDimensionsxK-1)) else '0';
    CopyValidxEO <= '1' when (TupleValidxEI = '1') and (CoreStatexS /= N_FREE) and (DimCnt /= (TupleNumDimsI+1)) else '0';
  end generate;

  -- copy BRAM data and register content to previous core
  BRAMDataxDO <= RamDataxDO;

  -- tell previous core what state we are in
  CoreStatexDO <= CoreStatexS;

  -- register channel
  CoreStateReg1xDO <= CoreStateReg1;
  CoreStateReg2xDO <= CoreStateReg2;
  
end Behavioral;
