/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0.  If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Copyright 2016 - 2017 Systems Group, ETH Zurich
 */
#ifndef FILE_FPGA_HPP_INCLUDED
#define FILE_FPGA_HPP_INCLUDED


#include "operators/hwoperators.h"
#include "fpga_udf.h"

static FPGA * my_fpga;
static pthread_mutex_t fpga_mutex;
static int* use_sw;

struct datapoint {
  struct datapoint *next;
  uint64_t timestamp;
  uint32_t dimensions[16]; 
};

#define FALSE 0
#define TRUE 1
#define BOOL uint32_t
#endif /* !FILE_FPGA_INCLUDED */
