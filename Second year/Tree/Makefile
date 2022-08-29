.PHONY: all time correct

RELEASE_OPTIONS = -O2
WARNING_OPTIONS = -Wall -Wextra
CXX = g++ --std=c++2a
MAIN_DIR = main_vers

all: time

time:
	$(CXX) $(MAIN_DIR)/main_time.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o tree_time.out

correct:
	$(CXX) $(MAIN_DIR)/main_correct.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o tree_correct.out

double_free:
	$(CXX) $(MAIN_DIR)/double_free_test.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o dble_free.out

asgn_test:
	$(CXX) $(MAIN_DIR)/asgn_test.cpp $(WARNING_OPTIONS) $(RELEASE_OPTIONS) -o asgn_test.out
