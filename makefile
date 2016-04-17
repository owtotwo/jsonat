ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include

CPP_FLAG = -std=c++11 -I$(INC_DIR) -g -Wall

CC_FILE = $(SRC_DIR)/jsonArray.cc  $(SRC_DIR)/jsonString.cc  \
	$(SRC_DIR)/jsonValue.cc  $(SRC_DIR)/jsonObject.cc

OBJ_FILE = parser.o  jsonArray.o  jsonString.o  \
	jsonValue.o  jsonObject.o

jsonat.exe : $(OBJ_FILE)
	g++ $(CPP_FLAG) $(OBJ_FILE) -o jsonat.exe


parser.o : $(SRC_DIR)/parser.cpp  $(INC_DIR)/Json.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/parser.cpp

$(INC_DIR)/Json.h : $(INC_DIR)/jsonValue.h  $(INC_DIR)/jsonObject.h  \
	$(INC_DIR)/jsonNumber.h  $(INC_DIR)/jsonString.h  \
	$(INC_DIR)/jsonArray.h
	touch $(INC_DIR)/Json.h

jsonArray.o : $(SRC_DIR)/jsonArray.cc  $(INC_DIR)/jsonArray.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonArray.cc

jsonObject.o : $(SRC_DIR)/jsonObject.cc  $(INC_DIR)/jsonObject.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonObject.cc

jsonString.o : $(SRC_DIR)/jsonString.cc  $(INC_DIR)/jsonString.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonString.cc

jsonValue.o : $(SRC_DIR)/jsonValue.cc  $(INC_DIR)/jsonValue.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonValue.cc



clean : 
	rm  $(OBJ_FILE) jsonat.exe