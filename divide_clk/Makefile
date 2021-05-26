CC     = g++
OPT    = -O2 # -O3
DEBUG  = -g
OTHER  = -Wall -Wno-deprecated
CFLAGS = $(OPT) $(OTHER)

INCDIR = -I$(SYSTEMC_INCLUDE)
LIBDIR = -L$(SYSTEMC_LIBDIR)
LIBS = -lsystemc
APP=main
SRCS=divide_main.cpp

all:
	g++ -o $(APP) $(SRCS) $(LIBDIR) $(INCDIR) $(LIBS)  -std=c++14

clean:
	rm -rf *.o