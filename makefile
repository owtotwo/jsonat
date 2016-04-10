ROOT_DIR = .
INCLUDE_DIR = $(ROOT_DIR)/include

CPP_FLAG = -std=c++11 -I$(INCLUDE_DIR)

test.exe : test.o  Value.o
	g++ $(CPP_FLAG) test.o Value.o -o test.exe

test.o : test.cpp  $(INCLUDE_DIR)/Json.h
	g++ -c $(CPP_FLAG) test.cpp

Value.o : Value.cpp  $(INCLUDE_DIR)/String.h  $(INCLUDE_DIR)/Array.h  \
			$(INCLUDE_DIR)/Object.h  $(INCLUDE_DIR)/Number.h 
	g++ -c $(CPP_FLAG) Value.cpp

clean : 
	rm test.exe test.o Value.o