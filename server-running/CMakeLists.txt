cmake_minimum_required(VERSION 3.5)

project(server-running LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(headers "../headers")
set(sources "../sources")

add_executable(
    ${PROJECT_NAME}
    main.cpp
    ${headers}/Listener.h
    ${sources}/Listener.cpp
    )

target_include_directories(
    ${PROJECT_NAME} PRIVATE
    ${headers}
    )
