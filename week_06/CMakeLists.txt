cmake_minimum_required(VERSION 3.16)

SET( CMAKE_BUILD_TYPE Release)
set (CMAKE_CXX_STANDARD 17)
add_compile_options(-Werror)

project(assembler)

set(SRCS
        assembler.cpp
        instruction.cpp
        libft.cpp
        machine_language.cpp
        parsing.cpp
        truth_tables.cpp
)

add_executable(${PROJECT_NAME} ${SRCS})
