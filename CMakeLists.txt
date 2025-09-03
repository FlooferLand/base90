cmake_minimum_required(VERSION 4.0)
project(base90 C)

set(CMAKE_C_STANDARD 23)

add_executable(base90
        src/main.c
        src/str.h
        src/str.c
        src/cli.c
        src/cli.h
        src/base90.c
        src/base90.h
        src/chararr.h
        src/chararr.c)
