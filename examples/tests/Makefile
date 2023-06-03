CXX=clang++
INC=../test_execution/include
LIB=../build/test_execution
CXXFLAGS=--std=c++20 -I $(INC) -L $(LIB) -l cppbdd
EXAMPLES=linked_list_test all_failed_test

.PHONY: all clean

all: $(EXAMPLES)

%: %.cpp
	$(CXX) -o $@ $(CXXFLAGS) $<

clean:
	-rm $(EXAMPLES)
