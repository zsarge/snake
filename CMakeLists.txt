cmake_minimum_required(VERSION 3.16)

project(serpent-game)

file(GLOB SOURCES "src/*.cpp")

add_executable(snake.out ${SOURCES})

