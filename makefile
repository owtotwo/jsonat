ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include

CPP_FLAG = -std=c++11 -I$(INC_DIR) -g -Wall

CC_FILE = $(SRC_DIR)/jsonArray.cc  $(SRC_DIR)/jsonString.cc  \
	$(SRC_DIR)/jsonValue.cc  $(SRC_DIR)/jsonObject.cc

HEAD_FILE = $(INC_DIR)/jsonValue.h  $(INC_DIR)/jsonObject.h  \
	$(INC_DIR)/jsonNumber.h  $(INC_DIR)/jsonString.h  \
	$(INC_DIR)/jsonArray.h  $(INC_DIR)/jsonJson.h

OBJ_FILE = main.o  jsonJson.o  jsonArray.o  jsonString.o  \
	jsonValue.o  jsonObject.o

EXEC_FILE = jsonat

$(EXEC_FILE) : $(OBJ_FILE)
	g++ $(CPP_FLAG) $(OBJ_FILE) -o $(EXEC_FILE)





main.o : $(SRC_DIR)/main.cpp  $(INC_DIR)/Json.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/main.cpp


$(INC_DIR)/Json.h : $(HEAD_FILE)
	touch $(INC_DIR)/Json.h

jsonJson.o : $(SRC_DIR)/jsonJson.cc  $(HEAD_FILE)
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonJson.cc

jsonArray.o : $(SRC_DIR)/jsonArray.cc  $(INC_DIR)/jsonArray.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonArray.cc

jsonObject.o : $(SRC_DIR)/jsonObject.cc  $(INC_DIR)/jsonObject.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonObject.cc

jsonString.o : $(SRC_DIR)/jsonString.cc  $(INC_DIR)/jsonString.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonString.cc

jsonValue.o : $(SRC_DIR)/jsonValue.cc  $(INC_DIR)/jsonValue.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonValue.cc



clean : 
	rm  -f $(OBJ_FILE) $(EXEC_FILE) $(EXEC_FILE).exe