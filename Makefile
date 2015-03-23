WARNINGS = -Wall -Werror
W_NO = -Wno-padded -Wno-unknown-pragmas -Wno-old-style-cast -Wno-missing-variable-declarations
CXX = g++
CXXFLAGS = --std=c++11 $(WARNINGS) $(W_NO)

ifneq ($(shell uname), Linux)
CXX = clang++
W = -Weverything
W_MORE_NO = -Wno-c++98-compat -Wno-c++98-compat-pedantic -Wno-missing-prototypes
endif

CXXFLAGS = --std=c++11 $(WARNINGS) $(W_NO) $(FLAGS) $(W) $(W_MORE_NO)


bfs.out: bfs.cpp breadth-first-search.h common.h ostream.h utilities.h
	$(CXX) $(CXXFLAGS) -o $@ $<

bfs: bfs.out
	./$< bfs-test.txt


clean:
	$(RM) *.out *.o

.PHONY: clean bfs
