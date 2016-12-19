FLAGS:=-Wall -pedantic -std=c++11
CC:=g++

EXE=LinkedList

.cpp.o:
	${CC} ${FLAGS} -c $@ $<

${EXE}: main.cpp
	${CC} ${FLAGS} -o $@ $<
