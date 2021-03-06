cmake_minimum_required(VERSION 3.10.2)

get_filename_component(PROJECT_NAME "${CMAKE_SOURCE_DIR}" NAME)
string(MAKE_C_IDENTIFIER "${PROJECT_NAME}" PROJECT_NAME)
project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(PROJECT_SOURCE_DIRECTORY "${PROJECT_SOURCE_DIR}/source")
file(GLOB_RECURSE PROJECT_SOURCE "${PROJECT_SOURCE_DIRECTORY}/*.cpp")
add_library(${PROJECT_NAME} STATIC "${PROJECT_SOURCE}")

set(TEST_PROJECT_NAME "${PROJECT_NAME}_test")
file(GLOB_RECURSE TEST_PROJECT_SOURCE "${PROJECT_SOURCE_DIR}/tests/*.cpp")
add_executable(${TEST_PROJECT_NAME} "${TEST_PROJECT_SOURCE}")
target_link_libraries(${TEST_PROJECT_NAME} ${PROJECT_NAME})

install(
	DIRECTORY "${PROJECT_SOURCE_DIRECTORY}/"
	DESTINATION include
	FILES_MATCHING PATTERN "*.hpp"
)
install(TARGETS ${PROJECT_NAME} ARCHIVE DESTINATION lib)

enable_testing()
add_test(NAME ${TEST_PROJECT_NAME} COMMAND ${TEST_PROJECT_NAME})
add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)
add_dependencies(check ${TEST_PROJECT_NAME})

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
		"Doxygen tool not found; therefore, the reference manual won't be generated."
	)
endif()
