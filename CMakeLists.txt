cmake_minimum_required(VERSION 3.5)
project(ncursespp)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(LIB_NAME ${PROJECT_NAME})

# Build ncurses
include(ExternalProject)
set(NCURSES_INSTALL_DIR ${CMAKE_CURRENT_BINARY_DIR}/ncurses)
ExternalProject_Add(ncurses
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ncurses/
        CONFIGURE_COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/third_party/ncurses/configure --prefix=${NCURSES_INSTALL_DIR}
        BUILD_COMMAND make
        INSTALL_COMMAND make install
)
include_directories(${NCURSES_INSTALL_DIR}/include)

function(import_ncurses name)
    add_library(${name} STATIC IMPORTED)
    set_property(TARGET ${name} PROPERTY IMPORTED_LOCATION "${NCURSES_INSTALL_DIR}/lib/lib${name}.a")
endfunction()

import_ncurses(form)
import_ncurses(menu)
import_ncurses(panel)

file(GLOB_RECURSE PROJECT_SOURCE_FILES src/*.cc)
add_executable(${LIB_NAME} ${PROJECT_SOURCE_FILES})
target_link_libraries(${LIB_NAME} form menu panel)

