# general settings
TARGET = wb3
CONFIG += warn_on
CONFIG += console
CONFIG -= qt

# project files
HEADERS += \
	source/Parser.h \
	source/Result.h \
	source/Node.h
SOURCES += \
	source/main.cpp \
	source/Parser.cpp \
	source/Result.cpp \
	source/Node.cpp

# compiler flags
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2
