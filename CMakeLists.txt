cmake_minimum_required(VERSION 3.10)
project(cpp_command_output)

set(CMAKE_CXX_STANDARD 17)

if (STATIC_COMPILE STREQUAL "yes")
    # Fix segfault when statically compiling.
    # https://stackoverflow.com/questions/35116327/when-g-static-link-pthread-cause-segmentation-fault-why
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -lrt -pthread -Wl,--whole-archive -lpthread -Wl,--no-whole-archive")
    SET(CMAKE_EXE_LINKER_FLAGS "-static")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
    SET(BUILD_SHARED_LIBS OFF)
endif()

if (NOT ${CMAKE_GENERATOR} MATCHES "Visual Studio")
    message(STATUS "CMake generator is NOT Visual Studio. Using regular build flags")

    if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Og -U_FORTIFY_SOURCE -ggdb")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Og -Wall -U_FORTIFY_SOURCE -ggdb")
    elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 ")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O2 -DNDEBUG")
    endif()
endif()


if (${CMAKE_GENERATOR} MATCHES "Visual Studio")
    message(STATUS "CMake generator is Visual Studio. Using Windows build flags")
    add_definitions(-DNOMINMAX -D_WIN32_WINNT=0x0A00 -DLANG_CXX17 -DCOMPILER_MSVC -D__VERSION__=\"MSVC\")
    add_definitions(-DWIN32 -DOS_WIN -D_MBCS -DWIN64 -DWIN32_LEAN_AND_MEAN -DNOGDI -DPLATFORM_WINDOWS)
    add_definitions(/bigobj /nologo /EHsc /GF /FC /MP /Gm-)
    # Suppress warnings to reduce build log size.
    add_definitions(/wd4267 /wd4244 /wd4800 /wd4503 /wd4554 /wd4996 /wd4348 /wd4018)
    add_definitions(/wd4099 /wd4146 /wd4267 /wd4305 /wd4307)
    add_definitions(/wd4715 /wd4722 /wd4723 /wd4838 /wd4309 /wd4334)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

message(STATUS "C++ compiler flags  : ${CMAKE_CXX_FLAGS}")
message(STATUS "C compiler flags    : ${CMAKE_C_FLAGS}")
message(STATUS "Linker flags        : ${CMAKE_EXE_LINKER_FLAGS} ${CMAKE_SHARED_LINKER_FLAGS} ${CMAKE_STATIC_LINKER_FLAGS}")


add_executable(cpp_command_output main.cpp command.h)