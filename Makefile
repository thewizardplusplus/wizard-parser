SOURCE = source/thewizardplusplus/wizard_parser/
OBJECTS = \
	$(SOURCE)utilities/set_utilities.o \
	$(SOURCE)utilities/string_utilities.o \
	$(SOURCE)lexer/token_group.o \
	$(SOURCE)lexer/token.o \
	$(SOURCE)lexer/tokenizer.o \
	$(SOURCE)parser/alternation_parser.o \
	$(SOURCE)parser/assignable_parser.o \
	$(SOURCE)parser/ast_node_flag.o \
	$(SOURCE)parser/ast_node.o \
	$(SOURCE)parser/binary_parser.o \
	$(SOURCE)parser/concatenation_parser.o \
	$(SOURCE)parser/dummy_parser.o \
	$(SOURCE)parser/empty_parser.o \
	$(SOURCE)parser/eoi_parser.o \
	$(SOURCE)parser/exception_parser.o \
	$(SOURCE)parser/flag_assignable_parser.o \
	$(SOURCE)parser/hide_parser.o \
	$(SOURCE)parser/lift_parser.o \
	$(SOURCE)parser/match_parser.o \
	$(SOURCE)parser/not_sequential_parser.o \
	$(SOURCE)parser/optional_parser.o \
	$(SOURCE)parser/parse.o \
	$(SOURCE)parser/parsing_result.o \
	$(SOURCE)parser/repetition_parser.o \
	$(SOURCE)parser/rule_parser.o \
	$(SOURCE)parser/sequential_parser.o \
	$(SOURCE)parser/token_parser.o \
	$(SOURCE)parser/type_assignable_parser.o \
	$(SOURCE)parser/type_match_parser.o \
	$(SOURCE)parser/utilities.o \
	$(SOURCE)parser/value_match_parser.o \
	$(SOURCE)parser/wrapping_parser.o
BUILD = build/
BUILD_HEADERS = $(BUILD)headers/wizard_parser/
BUILD_LIBRARIES = $(BUILD)libraries/wizard_parser/
LIBRARY_NAME = $(BUILD_LIBRARIES)libWizardParser.a
DOCS = docs/
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
	-O3

.PHONY: install docs clean

main: $(OBJECTS)
	mkdir -p $(BUILD_LIBRARIES)
	$(AR) crs $(LIBRARY_NAME) $(OBJECTS)

	$(RM) -r $(BUILD_HEADERS)
	mkdir -p $(BUILD_HEADERS)
	rsync -r --include="*/" --include="*.hpp" --exclude="*" $(SOURCE) $(BUILD_HEADERS)

install:
	cp -vr $(BUILD_HEADERS) /usr/include/
	cp $(LIBRARY_NAME) /usr/lib/

docs:
	$(RM) -r $(DOCS)html/
	doxygen $(DOCS)Doxyfile

clean:
	find . -name "*.o" -type f -delete
