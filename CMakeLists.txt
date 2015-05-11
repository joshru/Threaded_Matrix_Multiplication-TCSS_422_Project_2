cmake_minimum_required(VERSION 3.2)
project(Threaded_Matrix_Multiplication___TCSS_422_Project_2)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wall")

set(SOURCE_FILES main.c)
add_executable(dbsg ${SOURCE_FILES})

