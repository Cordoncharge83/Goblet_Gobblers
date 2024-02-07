cmake_minimum_required(VERSION 3.5)

project(ProjetG LANGUAGES C)

add_executable(ProjetG main.c
    board.h board.o
    piece.h piece.cpp)

include(GNUInstallDirs)
install(TARGETS ProjetG
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
