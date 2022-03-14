cmake_minimum_required(VERSION 3.5)

project(st7789 LANGUAGES C)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCES)

add_library(st7789_lib 
    STATIC 
        ${SOURCES}
)

target_include_directories( st7789_lib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}
    examples/single_device_test.c
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        st7789_lib
        gpiod
)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")

SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")
