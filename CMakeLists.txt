cmake_minimum_required(VERSION 3.5)

project(face LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib 4.2.0 REQUIRED)

add_executable(face main.cpp)

target_link_libraries(${PROJECT_NAME} raylib)

install(TARGETS face
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
