CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2 -I../build/headers/
LDFLAGS += -L../build/libraries/wizard_parser/ -lWizardParser

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LDFLAGS)

clean:
	find . -name "*.o" -type f -delete
