SOURCE = source/thewizardplusplus/wizard_parser/
OBJECTS = $(SOURCE)main.o $(SOURCE)Parser.o $(SOURCE)Node.o
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2

main: $(OBJECTS)
	$(CXX) $(OBJECTS) -o main
	make clean

clean:
	find . -name "*.o" -type f -delete
