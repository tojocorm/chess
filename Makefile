CC=g++ -g -Wall -std=c++17

# List of source files
CHESS_SOURCES=globals.cpp gui.cpp main.cpp

# Generate the names of the file server's object files
CHESS_OBJS=${CHESS_SOURCES:.cpp=.o}

TEST_SOURCES = $(wildcard test*.cpp)
TESTS = $(TEST_SOURCES:%.cpp=%)

.PHONT: all clean tests

all: chess $(TESTS)

tests: $(TESTS)

# Compile the file server and tag this compilation
chess: ${CHESS_OBJS} libfs_server.o
	${CC} -o $@ $^ -pthread -ldl

# Compile a client program
test%: test%.cpp libfs_client.o
	${CC} -o $@ $^

# Generic rules for compiling a source file to an object file
%.o: %.cpp
	${CC} -c $<
%.o: %.cc
	${CC} -c $<

clean:
	rm -f ${CHESS_OBJS} fs ${TESTS} special_test