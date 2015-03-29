OBJECTS = main.o
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2
LDFLAGS += -lWizardParser

.PHONY: clean

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(LDFLAGS)

clean:
	find . -name "*.o" -type f -delete
