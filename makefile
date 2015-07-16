FILES :=                              \
    .travis.yml                       \
    graph-tests/elp692-TestGraph.c++ \
    graph-tests/elp692-TestGraph.out \
    Graph.h                         \
    Graph.log                       \
    html                              \
    TestGraph.c++                   \
    TestGraph.out

ifeq ($(CXX), clang++)
    COVFLAGS := --coverage
    GCOV     := gcov-4.6 -r
else
    CXX      := g++-4.8
    COVFLAGS := -fprofile-arcs -ftest-coverage
    GCOV     := gcov-4.8 -r
endif

CXXFLAGS := -pedantic -std=c++11 -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

all: TestGraph

check:
	@for i in $(FILES);                                         \
	do                                                          \
        [ -e $$i ] && echo "$$i found" || echo "$$i NOT FOUND"; \
    done

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f TestGraph
	rm -f TestGraph.out

config:
	git config -l

test: TestGraph.out

graph-tests:
	git clone https://github.com/cs378-summer-2015/graph-tests.git

html: Doxyfile Graph.h TestGraph.c++
	doxygen Doxyfile

Graph.log:
	git log > Graph.log

Doxyfile:
	doxygen -g

TestGraph: Graph.h TestGraph.c++
	$(CXX) $(COVFLAGS) $(CXXFLAGS) TestGraph.c++ -o TestGraph $(LDFLAGS)

TestGraph.out: TestGraph
	$(VALGRIND) ./TestGraph  >  TestGraph.out 2>&1
	$(GCOV) -b TestGraph.c++ >> TestGraph.out
	cat TestGraph.out