cmake_minimum_required(VERSION 3.15)
project(task4 C)

set(CMAKE_C_STANDARD 11)

add_executable(main.c Objective.c Language.c Functional.c Container.c Procedure.c)