cmake_minimum_required(VERSION 2.8)
project (cidr_range)

include_directories(include)

add_subdirectory(src)
add_subdirectory(test)

find_package(Doxygen)
if(DOXYGEN_FOUND)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
add_custom_target(doc
${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
COMMENT "Generating API documentation with Doxygen" VERBATIM
)
else(DOXYGEN_FOUND)
message([WARNING] "Doxygen was not found, doc can't be generated." ...)
endif(DOXYGEN_FOUND)