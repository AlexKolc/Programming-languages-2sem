cmake_minimum_required(VERSION 3.4)

set(HEADERS rational.h)
set(SOURCES rational.cpp)
add_library(rational ${SOURCES} ${HEADERS})
install (TARGETS rational DESTINATION lib)
install (FILES rational.h DESTINATION include)
install (FILES rational.cpp DESTINATION include)
