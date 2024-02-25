cmake_minimum_required(VERSION 3.5)

project(client-running LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(headers "../headers")
set(sources "../sources")

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${headers}/Client.h
    ${sources}/Client.cpp
    )

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${headers}
    )
