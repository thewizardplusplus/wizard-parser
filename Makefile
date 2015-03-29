SOURCE = source/thewizardplusplus/wizard_parser/
OBJECTS = \
	$(SOURCE)parser/exceptions/ParseException.o \
	$(SOURCE)parser/Parser.o \
	$(SOURCE)node/Node.o
BUILD = build/
BUILD_HEADERS = $(BUILD)headers/wizard_parser/
BUILD_LIBRARIES = $(BUILD)libraries/wizard_parser/
LIBRARY_NAME = $(BUILD_LIBRARIES)libWizardParser.a
DOCS = docs/
CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2

.PHONY: install docs clean

main: $(OBJECTS)
	mkdir -p $(BUILD_LIBRARIES)
	$(AR) crs $(LIBRARY_NAME) $(OBJECTS)

	$(RM) -r $(BUILD_HEADERS)
	mkdir -p $(BUILD_HEADERS)
	rsync -r --include="*/" --include="*.h" --exclude="*" $(SOURCE) $(BUILD_HEADERS)

install:
	cp -vr $(BUILD_HEADERS) /usr/include/
	cp $(LIBRARY_NAME) /usr/lib/

docs:
	$(RM) -r $(DOCS)html/
	doxygen $(DOCS)Doxyfile

clean:
	find . -name "*.o" -type f -delete
