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
