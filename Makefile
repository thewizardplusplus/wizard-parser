SOURCE = source/
OBJECTS = $(SOURCE)main.o $(SOURCE)parser/Parser.o $(SOURCE)parser/Node.o
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2

all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o wb3

clean:
	find . -name "*.o" -type f -delete
