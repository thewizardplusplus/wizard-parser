# general settings
TARGET = wb3
CONFIG += warn_on
CONFIG += console
CONFIG -= qt

# project files
HEADERS += \
	source/parser/Node.h \
	source/parser/Result.h \
	source/parser/Parser.h
SOURCES += \
	source/parser/Node.cpp \
	source/parser/Parser.cpp \
	source/main.cpp

# compiler flags
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2
