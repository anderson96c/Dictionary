#Makefile

#Compiler
CXX = g++

#Flags
COMPILE_FLAG = -std=c++11

#Path
SRC_PATH = ./src/driver_dal.cpp
INCLUDE_PATH = ./include/dal.h

#Executable
BIN_NAME = ./bin/dictionary

dictionary: $(SRC_PATH) $(INCLUDE_PATH)
	$(CXX) $(COMPILE_FLAG) $(SRC_PATH) -o $(BIN_NAME)