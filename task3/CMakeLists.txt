cmake_minimum_required(VERSION 3.0)

add_library(rational STATIC rational.cpp)
install (TARGETS rational DESTINATION ${CMAKE_INSTALL_PREFIX}/lib)
install (FILES rational.h DESTINATION ${CMAKE_INSTALL_PREFIX}/include)
install (FILES rational.cpp DESTINATION ${CMAKE_INSTALL_PREFIX}/include)