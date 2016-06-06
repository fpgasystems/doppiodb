SOURCES = src/platform.cpp src/fpgaapi.cpp src/utils.cpp

all:
	libtool --mode=compile g++ -O2 -Wall -std=c++11 -D__AAL_USER__=1 -fPIC -c -shared -lOSAL -lAAS -lxlrt fpga.cpp
	libtool --mode=compile g++ -O2 -Wall -std=c++11 -D__AAL_USER__=1 -fPIC -c -shared -lOSAL -lAAS -lxlrt src/platform.cpp
	libtool --mode=compile g++ -O2 -Wall -std=c++11 -D__AAL_USER__=1 -fPIC -c -shared -lOSAL -lAAS -lxlrt src/fpgaapi.cpp
	libtool --mode=compile g++ -O2 -Wall -std=c++11 -D__AAL_USER__=1 -fPIC -c -shared -lOSAL -lAAS -lxlrt src/utils.cpp
	libtool --mode=link gcc -o libfpga.la fpga.lo platform.lo fpgaapi.lo utils.lo 

clean:
	rm -rf .libs *.o *.lo *.la libfpga.la
