cmake_minimum_required(VERSION 3.28)
project(ShareIt_project)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ShareIt_project
        classes.h
        general.cpp
        item_listing_classes.cpp
        notification.cpp
        user.cpp
        main.cpp
        manager.cpp)
