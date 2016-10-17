OBJECTS = source/main.o
CXX = clang++
CXXFLAGS += \
	-std=c++14 \
	-Weverything \
	-Wno-c++98-compat \
	-Wno-c++98-compat-pedantic \
	-Wno-shadow \
	-Wno-global-constructors \
	-Wno-exit-time-destructors \
	-Wno-padded \
	-Wno-weak-vtables \
	-O3
LDFLAGS += -lWizardParser

.PHONY: clean

main: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o main $(OBJECTS) $(LDFLAGS)

clean:
	find . -name "*.o" -type f -delete
