cmake_minimum_required(VERSION 2.8.8)
project(qcx-trx)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${PROJECT_SOURCE_DIR}/cmake)

INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})

# firmware sources
add_subdirectory(firmware)

