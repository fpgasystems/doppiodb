CC = libtool
SRC_DIR     = $(PWD)
CT_DIR      = $(CENTAUR_HOME)/sw


MON_SRC_DIR = $(SRC_DIR)
COR_SRC_DIR = $(CT_DIR)/core
OPR_SRC_DIR = $(SRC_DIR)/operators
PLT_SRC_DIR = $(CT_DIR)/platform

INC_DIR     = $(COR_SRC_DIR) $(OPR_SRC_DIR) $(PLT_SRC_DIR) $(MON_SRC_DIR)

OBJ_DIR = 

COR_SRCS = $(COR_SRC_DIR)/fpgaapi.cpp $(COR_SRC_DIR)/utils.cpp $(COR_SRC_DIR)/memory_manager.cpp $(COR_SRC_DIR)/workload_manager.cpp $(COR_SRC_DIR)/fthread.cpp
OPR_SRCS = $(OPR_SRC_DIR)/regex/sw/regex_operator.cpp $(OPR_SRC_DRIR)/regex/sw/regex-util/fregex.cpp $(OPR_SRC_DIR)/copy/sw/copy_operator.cpp $(OPR_SRC_DIR)/testcount/sw/testcount_operator.cpp $(OPR_SRC_DIR)/percentage/sw/percentage_operator.cpp $(OPR_SRC_DIR)/addmul/sw/addmul_operator.cpp $(OPR_SRC_DIR)/selection/sw/selection_operator.cpp $(OPR_SRC_DIR)/minmaxsum/sw/minmaxsum_operator.cpp $(OPR_SRC_DIR)/skyline/sw/skyline.cpp $(OPR_SRC_DIR)/sgd/sw/sgd_operator.cpp
PLT_SRCS = $(PLT_SRC_DIR)/platform.cpp
MON_SRCS = $(MON_SRC_DIR)/fpga.cpp 

SRCS     =  $(MON_SRCS) $(COR_SRCS) $(OPR_SRCS) $(PLT_SRCS)

COR_OBJS = $(COR_SRC_DIR)/fpgaapi.lo $(COR_SRC_DIR)/utils.lo $(COR_SRC_DIR)/memory_manager.lo $(COR_SRC_DIR)/workload_manager.lo $(COR_SRC_DIR)/fthread.lo
OPR_OBJS = $(OPR_SRC_DIR)/regex/sw/regex_operator.lo $(OPR_SRC_DIR)/regex/sw/regex-util/fregex.lo $(OPR_SRC_DIR)/copy/sw/copy_operator.lo $(OPR_SRC_DIR)/testcount/sw/testcount_operator.lo $(OPR_SRC_DIR)/percentage/sw/percentage_operator.lo $(OPR_SRC_DIR)/addmul/sw/addmul_operator.lo $(OPR_SRC_DIR)/selection/sw/selection_operator.lo $(OPR_SRC_DIR)/minmaxsum/sw/minmaxsum_operator.lo $(OPR_SRC_DIR)/skyline/sw/skyline.lo $(OPR_SRC_DIR)/sgd/sw/sgd_operator.lo
PLT_OBJS = $(PLT_SRC_DIR)/platform.lo
MON_OBJS = $(MON_SRC_DIR)/fpga.lo 

OBJS     =  $(MON_OBJS) $(COR_OBJS) $(OPR_OBJS) $(PLT_OBJS)
LTFLAGS  = --mode=compile g++ -O2 -Wall -std=c++11 -D__AAL_USER__=1 -fPIC -c -shared -I$(INC_DIR) -lOSAL -lAAS -lxlrt

LIBS     = $(COR_SRC_DIR)/.libs $(OPR_SRC_DIR)/regex/.libs $(OPR_SRC_DIR)/copy/.libs $(OPR_SRC_DIR)/testcount/.libs $(PLT_SRC_DIR)/.libs $(MON_SRC_DIR)/.libs

all: $(OBJS)
	libtool --mode=link gcc -o libfpga.la $(OBJS)


%.lo: %.cpp
	$(CC) $(LTFLAGS)  $< -o $@

clean:
	rm -rf .libs $(LIBS) $(OBJS) libfpga.la
