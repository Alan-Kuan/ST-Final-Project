CXX=clang++
SRC=linked_list_test.cpp
INC=../test_execution/include/
LIB=../build/test_execution/
CXXFLAGS=--std=c++20 -I $(INC) -L $(LIB) -l cppbdd
EXE=linked_list_test

.PHONY: all run clean

all: $(EXE)

$(EXE): $(SRC)
	$(CXX) -o $@ $(CXXFLAGS) $<

run: $(EXE)
	LD_LIBRARY_PATH=$(LIB) ./$(EXE)

clean:
	-rm $(EXE)
