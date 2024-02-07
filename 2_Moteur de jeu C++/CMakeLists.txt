cmake_minimum_required(VERSION 3.5)

project(PROJ1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(PROJ1 main.cpp
    board.cpp board.h)

include(GNUInstallDirs)
install(TARGETS PROJ1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
