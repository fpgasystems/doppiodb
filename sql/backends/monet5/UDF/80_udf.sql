-- This Source Code Form is subject to the terms of the Mozilla Public
-- License, v. 2.0.  If a copy of the MPL was not distributed with this
-- file, You can obtain one at http://mozilla.org/MPL/2.0/.
--
-- Copyright 1997 - July 2008 CWI, August 2008 - 2016 MonetDB B.V.

-- add function signatures to SQL catalog


-- Reverse a string
create function reverse(src string)
returns string external name udf.reverse;

-- Regex function using fpga
create function regexfpga(regex string, src string)
returns smallint external name udf.regexfpga;

-- Parallel Regex function using fpga
create function parregexfpga(regex string, src string)
returns smallint external name udf.parregexfpga;

-- Copy function using fpga
create function copyfpga(src integer)
returns integer external name udf.copyfpga;

-- MAC function using fpga
create function macfpga(mularg smallint, addarg integer, src integer)
returns integer external name udf.macfpga;

-- Regex count function using fpga
create function regexcountfpga(regex string, src string)
returns integer external name udf.regexcountfpga;

-- Regex percentage function using fpga
create function regexpercfpga(regex string, src1 string, src2 integer)
returns real external name udf.regexpercfpga;

-- Regex percentage function using fpga and cpu
create function regexpercfpga_cpu(regex string, src1 string, src2 integer)
returns real external name udf.regexpercfpga_cpu;

-- Regex count function using fpga  and sw
create function regexcountfpgasw(regex string, src string)
returns integer external name udf.regexcountfpgasw;

-- test_count function using fpga
create function testcountfpga(test string, threshold smallint, src smallint)
returns integer external name udf.testcountfpga;

-- percentage function using fpga
create function percentagefpga(src1 smallint, src2 integer)
returns real external name udf.percentagefpga;

-- mull-add + percentage function using fpga
create function madpercfpga(a integer, b integer, src1 smallint, src2 integer)
returns real external name udf.madpercfpga;

-- hwselection function using fpga
create function hwselection(one integer, selectionType1 string, lowerThreshold1 integer, upperThreshold1 integer)
returns integer external name udf.hwselection;

-- hwselection2 function using fpga
create function hwselection2(	one integer, selectionType1 string, lowerThreshold1 integer, upperThreshold1 integer, two integer, selectionType2 string, lowerThreshold2 integer, upperThreshold2 integer)
returns integer external name udf.hwselection2;

-- minmaxsum function using fpga
create function hwminmaxsum(one integer)
returns integer external name udf.hwminmaxsum;

--skyline function using fpga
create function skylinefpga(src1 integer, src2 integer, src3 integer, src4 integer, src5 integer, src6 integer, src7 integer, src8 integer, src9 integer, src10 integer, src11 integer, src12 integer, src13 integer, src14 integer, src15 integer, src16 integer)
returns integer external name udf.skylinefpga;

--skyline function using sw
create function skylinesw(src1 integer, src2 integer, src3 integer, src4 integer, src5 integer, src6 integer, src7 integer, src8 integer, src9 integer, src10 integer, src11 integer, src12 integer, src13 integer, src14 integer, src15 integer, src16 integer)
returns integer external name udf.skylinesw;

--SGD function using fpga
create function sgdfpga_column(numFeatures integer, numIterations integer, stepSizeShifter integer, gatherDepth integer, a1 real, a2 real, a3 real, a4 real, a5 real, a6 real, a7 real, a8 real, a9 real, a10 real, a11 real, a12 real, a13 real, a14 real, a15 real, b real)
returns real external name udf.sgdfpga_column;

--SGD function using sw
create function sgdsw_column(numFeatures integer, numIterations integer, stepSizeShifter integer, a1 real, a2 real, a3 real, a4 real, a5 real, a6 real, a7 real, a8 real, a9 real, a10 real, a11 real, a12 real, a13 real, a14 real, a15 real, b real)
returns real external name udf.sgdsw_column;

--SGD function using fpga
create function sgdfpga_row(numFeatures integer, numIterations integer, stepSizeShifter integer, ab real)
returns real external name udf.sgdfpga_row;

--SGD function using sw
create function sgdsw_row(numFeatures integer, numIterations integer, stepSizeShifter integer, ab real)
returns real external name udf.sgdsw_row;

--create function calc_test(one double, two double)
--returns double external name udf.calc_test;

-- fuse two (1-byte) tinyint values into one (2-byte) smallint value
create function fuse(one tinyint, two tinyint)
returns smallint external name udf.fuse;

-- fuse two (2-byte) smallint values into one (4-byte) integer value
create function fuse(one smallint, two smallint)
returns integer external name udf.fuse;

-- fuse two (4-byte) integer values into one (8-byte) bigint value
create function fuse(one integer, two integer)
returns bigint external name udf.fuse;
