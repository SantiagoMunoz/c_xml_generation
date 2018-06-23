CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12)

project("c xml codegen sample project")

find_package(PkgConfig)
pkg_check_modules (LIBXML2 libxml-2.0)

file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/generated/xml_dynamic.h ${CMAKE_CURRENT_BINARY_DIR}/generated/xml_dynamic.c
    COMMAND python ${CMAKE_CURRENT_SOURCE_DIR}/build.py ${CMAKE_CURRENT_SOURCE_DIR}/examples/example_xml_struct.xml ${CMAKE_CURRENT_BINARY_DIR}/generated/xml_dynamic
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating xml management and serialization code"
    )

include_directories(${CMAKE_CURRENT_BINARY_DIR}/generated)
list(APPEND xml_sources ${CMAKE_CURRENT_BINARY_DIR}/generated/xml_dynamic.h)
list(APPEND xml_sources ${CMAKE_CURRENT_BINARY_DIR}/generated/xml_dynamic.c)
set(example_sources examples/example.c)

add_executable(self_test ${xml_sources} ${example_sources})
target_include_directories(self_test PRIVATE ${LIBXML2_INCLUDE_DIRS})
target_link_libraries(self_test ${LIBXML2_LIBRARIES})
