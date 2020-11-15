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

#creating cross compiled Winodws binary
#set(CMAKE_SYSTEM_NAME Windows)
#set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)

#link_directories(BEFORE windows/lib/)
#file(GLOB_RECURSE SBC_CROSS_WIN_LIBS_FILES windows/lib/*.a)
#set(SBC_CROSS_WIN_LIBS 	${SBC_CROSS_WIN_LIBS_FILES})
#set(CMAKE_C_FLAGS "-mwindows -I../src/kosmonaut/ -I../src/game/game/ -I../windows/include/  -L../windows/lib/ ../windows/nng.dll -lglew32 -lglew32mx -lSDL2 -lSDL2main -lopengl32 -lmingw32 -lm")
#include_directories(windows/include/)

#find_library(SBC_CROSS_WIN_SDL2 libSDL2.a NO_SYSTEM_ENVIRONMENT_PATH)
#find_library(SBC_CROSS_WIN_SDL2_MAIN libSDL2main.a NO_SYSTEM_ENVIRONMENT_PATH)
#find_library(SBC_CROSS_WIN_GLEW32 libglew32.a NO_SYSTEM_ENVIRONMENT_PATH)
#find_library(SBC_CROSS_WIN_NNG nng.dll NO_SYSTEM_ENVIRONMENT_PATH)


#add_executable(SBC_CROSS_WIN ${SBC_SRC} ${KOSMONAUT_SRC})
#target_link_libraries(SBC_CROSS_WIN ${SBC_CROSS_WIN_LIBS})
#target_link_libraries(SBC_CROSS_WIN ${SBC_CROSS_WIN_SDL2})
#target_link_libraries(SBC_CROSS_WIN ${SBC_CROSS_WIN_SDL2_MAIN})
#target_link_libraries(SBC_CROSS_WIN ${SBC_CROSS_WIN_GLEW32})
#target_link_libraries(SBC_CROSS_WIN ${SBC_CROSS_WIN_NNG})