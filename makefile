ROOT_DIR = .
SRC_DIR = $(ROOT_DIR)/src
INC_DIR = $(ROOT_DIR)/include
TEST_DIR = $(ROOT_DIR)/test
LIB_DIR = $(ROOT_DIR)/lib
SAMPLE_DIR = $(ROOT_DIR)/sample
CPP_FLAG = -std=c++11 -I$(ROOT_DIR) -I$(INC_DIR) -g -Wall
TEST_FLAG = -pthread 

CC_FILE = $(SRC_DIR)/jsonArray.cc  $(SRC_DIR)/jsonString.cc  \
	$(SRC_DIR)/jsonValue.cc  $(SRC_DIR)/jsonObject.cc  \
	$(SRC_DIR)/jsonBoolean.cc

HEAD_FILE = $(INC_DIR)/jsonValue.h  $(INC_DIR)/jsonObject.h  \
	$(INC_DIR)/jsonNumber.h  $(INC_DIR)/jsonString.h  \
	$(INC_DIR)/jsonArray.h  $(INC_DIR)/jsonBoolean.h  \
	$(INC_DIR)/jsonJson.h

OBJ_FILE = jsonJson.o  jsonArray.o  jsonString.o  \
	jsonValue.o  jsonObject.o  jsonBoolean.o

EXEC_FILE = jsonat

TEST_HEAD_FILE = $(INC_DIR)/gtest/gtest.h
TEST_LIB_FILE = $(LIB_DIR)/libgtest.a



# =======================================================
# Execute file

$(EXEC_FILE) : main.o  $(LIB_DIR)/libjsonat.a
	g++ $(CPP_FLAG) main.o  $(LIB_DIR)/libjsonat.a -o $(EXEC_FILE)


main.o : $(SRC_DIR)/main.cpp  $(INC_DIR)/Json.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/main.cpp

$(INC_DIR)/Json.h : $(HEAD_FILE)
	touch $(INC_DIR)/Json.h

$(LIB_DIR)/libjsonat.a : $(OBJ_FILE)
	ar -rv $(LIB_DIR)/libjsonat.a  $(OBJ_FILE) 

jsonJson.o : $(SRC_DIR)/jsonJson.cc  $(HEAD_FILE)
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonJson.cc

jsonArray.o : $(SRC_DIR)/jsonArray.cc  $(INC_DIR)/jsonArray.h  \
	$(INC_DIR)/jsonValue.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonArray.cc

jsonObject.o : $(SRC_DIR)/jsonObject.cc  $(INC_DIR)/jsonObject.h  \
	$(INC_DIR)/jsonValue.h  $(INC_DIR)/jsonString.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonObject.cc

jsonString.o : $(SRC_DIR)/jsonString.cc  $(INC_DIR)/jsonString.h  \
	$(INC_DIR)/jsonValue.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonString.cc

jsonValue.o : $(SRC_DIR)/jsonValue.cc  $(INC_DIR)/jsonValue.h  \
	$(INC_DIR)/jsonObject.h  $(INC_DIR)/jsonBoolean.h  \
	$(INC_DIR)/jsonNumber.h  $(INC_DIR)/jsonString.h  \
	$(INC_DIR)/jsonArray.h  
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonValue.cc

jsonBoolean.o : $(SRC_DIR)/jsonBoolean.cc  $(INC_DIR)/jsonBoolean.h
	g++ $(CPP_FLAG) -c $(SRC_DIR)/jsonBoolean.cc



# ============================================================
# Test file
	
test : test_main.o  test_Boolean.o  jsonBoolean.o  $(TEST_LIB_FILE)
	g++ $(CPP_FLAG) $(TEST_FLAG)  test_main.o  test_Boolean.o  \
		jsonBoolean.o  $(TEST_LIB_FILE)  -o  test-all

test_main.o : $(TEST_DIR)/test_main.cpp  $(TEST_HEAD_FILE)
	g++ $(CPP_FLAG) -c  $(TEST_DIR)/test_main.cpp

test_Boolean.o : $(TEST_DIR)/test_Boolean.cpp  $(INC_DIR)/jsonBoolean.h  \
	$(TEST_HEAD_FILE)
	g++ $(CPP_FLAG) -c $(TEST_DIR)/test_Boolean.cpp
	

# =============================================================
# Sample file

sample :  sample3.o  $(LIB_DIR)/libjsonat.a  
	g++ $(CPP_FLAG)  sample3.o  $(LIB_DIR)/libjsonat.a  -o  sample3

sample1.o : $(SAMPLE_DIR)/sample1.cpp  $(INC_DIR)/Json.h
	g++ $(CPP_FLAG) -c  $(SAMPLE_DIR)/sample1.cpp

sample2.o : $(SAMPLE_DIR)/sample2.cpp  $(INC_DIR)/Json.h
	g++ $(CPP_FLAG) -c -O0  $(SAMPLE_DIR)/sample2.cpp
	
sample3.o : $(SAMPLE_DIR)/sample3.cpp  $(INC_DIR)/Json.h
	g++ $(CPP_FLAG) -c -O0  $(SAMPLE_DIR)/sample3.cpp

# =============================================================
# clean

clean : 
	rm  -f  $(OBJ_FILE)  main.o  $(EXEC_FILE)  $(EXEC_FILE).exe

clean-test : 
	rm  -f  test_main.o  test_Boolean.o  jsonBoolean.o  test-all  test-all.exe

clean-sample :
	rm -f  sample1.o  sample1  sample1.exe


clean-all :
	rm  -f  *.o  *.exe