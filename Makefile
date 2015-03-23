WARNINGS = -Wall -Werror
W_NO = -Wno-c++98-compat -Wno-padded -Wno-unknown-pragmas -Wno-c++98-compat-pedantic -Wno-old-style-cast -Wno-missing-variable-declarations -Wno-missing-prototypes
CXX = g++
CXXFLAGS = --std=c++11 $(WARNINGS) $(W_NO)

ifneq ($(shell uname), Linux)
CXX = clang++
W = -Weverything
endif

CXXFLAGS = --std=c++11 $(WARNINGS) $(W_NO) $(FLAGS) $(W)


bfs.out: bfs.cpp breadth-first-search.h common.h ostream.h utilities.h
	$(CXX) $(CXXFLAGS) -o $@ $<

bfs: bfs.out
	./$<


clean:
	$(RM) *.out *.o

.PHONY: clean bfs
