cmake_minimum_required(VERSION 3.26)
project(ap_final_project_main)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ap_final_project_main
        api.cpp
        api.h
        ctgs.h
        difficulty.cpp
        difficulty.h
        CustomPage.cpp
        CustomPage.h
        main.cpp
        mainwindow.cpp
        mainwindow.h
        names.cpp
        names.h
        pvp_mode.cpp
        pvp_mode.h
        qst.h
        quiz.cpp
        quiz.h
        quiz2.h
        randstr.h
        starting.cpp
        starting.h
        survival_mode.cpp
        survival_mode.h)
