CXX = g++
FLAGS = -W -Wall -Wextra -Wpedantic -Werror -std=c++11

.PHONY: default run main.o maps.o populations.o

default: run

main.o:
	${CXX} ${FLAGS} -c main.cpp

maps.o:
	${CXX} ${FLAGS} -c Maps/*.cpp

populations.o:
	${CXX} ${FLAGS} -c Populations/*.cpp

run: main.o maps.o populations.o
	${CXX} ${FLAGS} *.o -o program

debug:
	${CXX} ${FLAGS} -g Populations/*.cpp Maps/*.cpp main.cpp -o debug

clean:
	-@rm -rf *.o program debug