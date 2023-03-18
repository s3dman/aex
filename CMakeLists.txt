cmake_minimum_required(VERSION 3.20)

project(glt)
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} )
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

add_executable(${PROJECT_NAME} src/main.c)
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} )

