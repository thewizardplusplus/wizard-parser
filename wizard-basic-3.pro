# general settings
CONFIG += warn_on
CONFIG += console
CONFIG -= qt

# project files
HEADERS += \
	source/Parser.h \
	source/Result.h
SOURCES += \
	source/main.cpp \
	source/Parser.cpp \
	source/Result.cpp

# compiler flags
QMAKE_CXXFLAGS += -std=c++11 -Wpedantic -Wall -Wextra -O2
