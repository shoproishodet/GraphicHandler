cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME "RayTracer")

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

set(INCLUDES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Include)


add_subdirectory(Source)
