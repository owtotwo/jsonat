ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INCLUDE_DIR = $(ROOT_DIR)/include

CPP_FLAG = -std=c++11 -I$(INCLUDE_DIR)

test.exe : test.o  Value.o
	g++ $(CPP_FLAG) test.o Value.o -o test.exe

test.o : $(SRC_DIR)/test.cpp  $(INCLUDE_DIR)/Json.h
	g++ -c $(CPP_FLAG) $(SRC_DIR)/test.cpp

Value.o : Value.cpp  $(INCLUDE_DIR)/String.h  $(INCLUDE_DIR)/Array.h  \
			$(INCLUDE_DIR)/Object.h  $(INCLUDE_DIR)/Number.h 
	g++ -c $(CPP_FLAG) $(SRC_DIR)/Value.cpp

clean : 
	rm test.exe test.o Value.o