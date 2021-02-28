.PHONY: all time correct

RELEASE_OPTIONS = -O2
WARNING_OPTIONS = -Wall -Wextra
CXX = g++ --std=c++2a
MAIN_DIR = main_vers

all: full

full:
	$(CXX) $(MAIN_DIR)/main.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o my_tree.out

time:
	$(CXX) $(MAIN_DIR)/main_time.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o tree_time.out

correct:
	$(CXX) $(MAIN_DIR)/main_correct.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o tree_correct.out