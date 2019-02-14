#all: yuv_test
#yuv_test: yuv_test.o conversion.o
	#gcc -Wall -g -std=c++11 -o yuv_test yuv_test.o conversion.o
#yuv_test.o: yuv_test.cc conversion.h
	#gcc -Wall -g -std=c++11 -c yuv_test.cc
#conversion.o: conversion.cc conversion.h
	#gcc -Wall -g -std=c++11 -c conversion.cc
#clean:
	#rm -rf yuv_test *.o *~ yuv_test.dSYM
	
	
CXX = g++
CFLAGS = -g -Wall -std=c++11
EXE = yuv_test
OBJS = yuv_test.o conversion.o
# this is the default rule that fires if a user
# just types "make" in the same directory as this Makefile.
all: $(EXE)

$(EXE): $(OBJS)
	$(CXX) $(CFLAGS) -o $@ $^ 

%.o: %.cc 
	$(CXX) $(CFLAGS) -c $< 

clean: FORCE
	/bin/rm -rf $(EXE) *.o *~ *.dSYM

FORCE:
