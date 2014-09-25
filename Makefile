SOURCE = source/thewizardplusplus/wizard_parser/
OBJECTS = $(SOURCE)main.o $(SOURCE)parser/Parser.o $(SOURCE)node/Node.o
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2

main: $(OBJECTS)
	$(CXX) $(OBJECTS) -o main

clean:
	find . -name "*.o" -type f -delete
