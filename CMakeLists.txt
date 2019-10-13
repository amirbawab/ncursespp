cmake_minimum_required(VERSION 3.5)
project(ncursespp)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(LIB_NAME ${PROJECT_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_compile_options(-std=c++11)
add_definitions(-DNPP_DEBUG)

# Build ncurses
include(ExternalProject)
set(NCURSES_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/ncurses)
ExternalProject_Add(ncurses_lib
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ncurses/
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ncurses/configure --prefix=${NCURSES_INSTALL_DIR}
        BUILD_COMMAND make
        INSTALL_COMMAND make install
)
include_directories(${NCURSES_INSTALL_DIR}/include)
include_directories(src/)

function(import_ncurses name)
    add_library(${name} STATIC IMPORTED)
    set_property(TARGET ${name} PROPERTY IMPORTED_LOCATION "${NCURSES_INSTALL_DIR}/lib/lib${name}.a")
    add_dependencies(${name} ncurses_lib)
endfunction()

import_ncurses(ncurses)
import_ncurses(form)
import_ncurses(menu)
import_ncurses(panel)

file(GLOB_RECURSE PROJECT_SOURCE_FILES src/*.cc)
add_executable(${LIB_NAME} ${PROJECT_SOURCE_FILES})
target_link_libraries(${LIB_NAME} ncursesw form menu panel)

