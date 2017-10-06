all: hw2

hw2: mainTerm.o variable.o
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o variable.o -lgtest
else
	g++ -o hw2 mainTerm.o variable.o -lgtest -lpthread
endif

mainTerm.o: mainTerm.cpp utTerm.h
	g++ --std=gnu++11 -c mainTerm.cpp
variable.o: variable.cpp variable.h
	g++ --std=gnu++11 -c variable.cpp

clean:
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
