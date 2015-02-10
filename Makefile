SOURCE = source/thewizardplusplus/wizard_parser/
OBJECTS = \
	$(SOURCE)parser/exceptions/ParseException.o \
	$(SOURCE)parser/Parser.o \
	$(SOURCE)node/Node.o
BUILD = build/
BUILD_HEADERS = $(BUILD)headers/wizard_parser/
BUILD_LIBRARIES = $(BUILD)libraries/wizard_parser/
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2

main: $(OBJECTS)
	mkdir -p $(BUILD_LIBRARIES)
	$(AR) crs $(BUILD_LIBRARIES)libWizardParser.a $(OBJECTS)

	$(RM) -r $(BUILD_HEADERS)
	mkdir -p $(BUILD_HEADERS)
	rsync -r --include="*/" --include="*.h" --exclude="*" $(SOURCE) $(BUILD_HEADERS)

clean:
	find . -name "*.o" -type f -delete
