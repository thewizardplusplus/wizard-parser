cmake_minimum_required(VERSION 3.2.2)

get_filename_component(PROJECT_NAME "${CMAKE_SOURCE_DIR}" NAME)
string(MAKE_C_IDENTIFIER "${PROJECT_NAME}" PROJECT_NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(PROJECT_SOURCE_DIRECTORY "${PROJECT_SOURCE_DIR}/source")
file(GLOB_RECURSE PROJECT_SOURCE "${PROJECT_SOURCE_DIRECTORY}/*.cpp")
add_library(${PROJECT_NAME} STATIC "${PROJECT_SOURCE}")
if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(
		CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} \
			-std=c++14 \
			-Weverything \
			-Wno-c++98-compat \
			-Wno-c++98-compat-pedantic \
			-Wno-shadow \
			-Wno-global-constructors \
			-Wno-exit-time-destructors \
			-Wno-padded \
			-Wno-weak-vtables \
			-O3"
	)
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set(
		CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} -std=c++14 -Wpedantic -Wall -Wextra -O3 -flto"
	)
endif()

install(
	DIRECTORY "${PROJECT_SOURCE_DIRECTORY}/"
	DESTINATION include
	FILES_MATCHING PATTERN "*.hpp"
)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)

find_package(Doxygen)
if(DOXYGEN_FOUND)
	set(DOXYGEN_INPUT "${CMAKE_SOURCE_DIR}")
	set(DOXYGEN_OUTPUT "${CMAKE_SOURCE_DIR}")
	set(DOXYFILE_PATH "${CMAKE_SOURCE_DIR}/Doxyfile")
	configure_file("${DOXYFILE_PATH}.in" "${DOXYFILE_PATH}")
	add_custom_target(docs COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYFILE_PATH}")
else()
	message(
		WARNING
		"The Doxygen hasn't been found - the reference manual won't be created"
	)
endif()
