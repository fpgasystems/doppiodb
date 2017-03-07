-- configuration package
library IEEE;
use IEEE.STD_LOGIC_1164.all;

package conf is 

  constant TupleBusWidthxK        : positive := 32;
  constant BramAddrBusWidthxK     : positive := 9;   -- 2^BramAddrBusWidthxK*BramDataBusWidthxK should equal 16,384 (16 Kbit)
  constant BramDataBusWidthxK     : positive := 32;  -- should be the same as TupleBusWidthxK
  constant BramWriteEnableWidthxK : positive := 4;   -- should be BramDataBusWidthxK/8
  constant NumCoresxK             : positive := 128;
  constant NumDimensionsxK        : positive := 16;
  constant NumTupleDimensionsxK   : positive := NumDimensionsxK+2;
--  constant NumBitsDimCounterxK    : positive := 5;   -- number of bits require to count from 0 to NumTupleDimensionsxK
    
  type CoreStatexTYPE is (
    L_FREE,
    N_FREE,
    P_OCCP,
    S_OCCP
    );
  
end conf;
