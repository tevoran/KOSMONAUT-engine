cmake_minimum_required(VERSION 3.18)
project("SBC")


find_library(MATHS m)
find_library(SDL2 SDL2)
find_library(NNG nng)
find_library(PTHREAD pthread)
find_library(GLEW GLEW)
find_library(GL GL)


#kosmonaut engine include
include_directories(src/kosmonaut/)

#SBC game include
include_directories(src/game/game/)

#SET(CMAKE_C_FLAGS "-lSDL2 -lGL -lGLEW -lm -lnng -lpthread -o SBC -g -pg -fno-common")
set(CMAKE_C_FLAGS "")

#creating kosmonaut engine lib
file(GLOB_RECURSE KOSMONAUT_SRC src/kosmonaut/*.c)
add_library(KOSMONAUT STATIC ${KOSMONAUT_SRC})

#creating Star Battle Command
file(GLOB_RECURSE SBC_SRC src/game/*.c)
add_executable(SBC ${SBC_SRC})

target_link_libraries(SBC LINK_PRIVATE "${MATHS}")
target_link_libraries(SBC LINK_PRIVATE "${SDL2}")
target_link_libraries(SBC LINK_PRIVATE KOSMONAUT)
target_link_libraries(SBC LINK_PRIVATE "${NNG}")
target_link_libraries(SBC LINK_PRIVATE "${PTHREAD}")
target_link_libraries(SBC LINK_PRIVATE "${GLEW}")
target_link_libraries(SBC LINK_PRIVATE "${GL}")

file(COPY SBC DESTINATION ../)