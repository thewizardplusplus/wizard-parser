SOURCE = source/
OBJECTS = $(SOURCE)main.o $(SOURCE)Parser.o $(SOURCE)Node.o
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2

all: $(OBJECTS)
	$(CXX) $(OBJECTS) -o wb3

clean:
	$(RM) $(SOURCE)*.o
