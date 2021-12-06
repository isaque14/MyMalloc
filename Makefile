CXXFLAGS = -O3 -Wall -std=c++11 -lstdc++fs
CXX = g++

all:clean  malloc mallinfo

malloc:
	$(CXX) -c -fpic src/mymalloc/mymalloc.cpp
	ar -cvq -o src/mymalloc/libmymalloc.a mymalloc.o

mallinfo:
	$(CXX) -c -fpic src/mymallinfo/mymallinfo.cpp
	ar -cvq -o src/mymallinfo/libmymallinfo.a mymallinfo.o

test:
	$(CXX) tests/test.cpp -lmymalloc -L. -o test

clean:
	rm libmymallinfo.a
	rm libmymalloc.a
	rm mymallinfo.o
	rm mymalloc.o