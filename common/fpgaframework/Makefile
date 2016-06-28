CC = libtool
INC_DIR = $(HARP_FRAMEWORK)/SW
SRC_DIR = $(HARP_FRAMEWORK)/SW/src
OBJ_DIR = 
SRCS = fpga.cpp $(SRC_DIR)/platform.cpp $(SRC_DIR)/fpgaapi.cpp $(SRC_DIR)/utils.cpp $(SRC_DIR)/memory_manager.cpp $(SRC_DIR)/fthread.cpp 
OBJS = fpga.lo $(SRC_DIR)/platform.lo $(SRC_DIR)/fpgaapi.lo $(SRC_DIR)/utils.lo $(SRC_DIR)/memory_manager.lo $(SRC_DIR)/fthread.lo
LTFLAGS = --mode=compile g++ -O2 -Wall -std=c++11 -D__AAL_USER__=1 -fPIC -c -shared -I$(INC_DIR) -lOSAL -lAAS -lxlrt


all: $(OBJS)
	libtool --mode=link gcc -o libfpga.la $(OBJS)


%.lo: %.cpp
	$(CC) $(LTFLAGS) $< -o $@

clean:
	rm -rf .libs $(SRC_DIR)/.libs $(OBJS) libfpga.la
