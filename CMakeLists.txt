cmake_minimum_required(VERSION 3.0)
project(fir_filter)

list(APPEND CMAKE_MODULE_PATH cmake)

include(FindPortaudio)

set(FIR_FILTER_SOURCES src/main.c src/fir.c src/taps.c)

add_executable(fir_filter ${FIR_FILTER_SOURCES})
target_include_directories(fir_filter PUBLIC ${PORTAUDIO_INCLUDE_DIRS})
target_link_libraries(fir_filter ${PORTAUDIO_LIBRARIES})