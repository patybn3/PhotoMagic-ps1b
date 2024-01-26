CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
# SRCS = main.cpp test.cpp FibLFSR.cpp
# Your .hpp files
DEPS = FibLFSR.hpp PhotoMagic.hpp
# Your compiled .o files
OBJECTS = FibLFSR.o PhotoMagic.o
# The name of your program
PROGRAM_MAIN = PhotoMagic
PROGRAM_TEST = test

.PHONY: all clean lint

all: $(PROGRAM_MAIN) $(PROGRAM_TEST) PhotoMagic.a

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM_MAIN): main.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

$(PROGRAM_TEST): test.o $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

PhotoMagic.a: $(OBJECTS)
	ar rcs PhotoMagic.a $(OBJECTS)

clean:
	rm *.o $(PROGRAM_MAIN) $(PROGRAM_TEST) PhotoMagic.a

lint:
	cpplint *.cpp *.hpp
