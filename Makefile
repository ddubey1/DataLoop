CONSERVATIVE_FLAGS = -std=c++11 -pedantic -Wall -Wextra
DEBUGGING_FLAGS = -g
CFLAGS = $(CONSERVATIVE_FLAGS) $(DEBUGGING_FLAGS)

# Creates executable for running and testing.
DataLoopTest: DataLoop.o DataLoopTest.o
	g++ -o DataLoopTest DataLoop.o DataLoopTest.o

TDataLoopTest: TDataLoopTest.o
	g++ -o TDataLoopTest TDataLoopTest.o

# Creates object files from .cpp files.
DataLoop.o: DataLoop.cpp  DataLoop.h
	g++ -c DataLoop.cpp $(CFLAGS)

DataLoopTest.o: DataLoopTest.cpp DataLoop.h
	g++ -c DataLoopTest.cpp $(CFLAGS)

TDataLoopTest.o: TDataLoopTest.cpp TDataLoop.h
	g++ -c TDataLoopTest.cpp $(CFLAGS)

# Gets rid of object files and executables.
clean:
	rm -f *.o main