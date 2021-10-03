# The following lines of boilerplate have to be in your project's CMakeLists
# in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE HEADER_FILES src/*.h)

if (NOT DEFINED COMPONENT_DIR)

    #When used as a standalone app
    project (sh1107)
    file(GLOB_RECURSE SOURCE_FILES main/*.c)
    add_library(sh1107 STATIC ${HEADER_FILES} ${SOURCE_FILES})

else()

    #When used as a component
    file(GLOB_RECURSE SOURCE_FILES main/sh1107*.c)
    
    idf_component_register(SRCS ${SOURCE_FILES}
                           INCLUDE_DIRS "main")

endif()
