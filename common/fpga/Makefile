
all:
	libtool --mode=compile g++ -O2 -Wall -D__AAL_USER__=1 -fPIC -shared -lOSAL -lAAS -lxlrt -c fpga.cpp
	libtool --mode=link gcc -o libfpga.la fpga.lo

clean:
	rm -rf .libs fpga.o fpga.lo fpga.la libfpga.la
