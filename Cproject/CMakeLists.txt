cmake_minimum_required(VERSION 3.20)
project(Cproject C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Cproject
        app.c
        app.h
        card.c
        card.h
        macros.h
        main.c
        server.c
        server.h
        terminal.c
        terminal.h)
