cmake_minimum_required(VERSION 3.6)
project(common)

set(CMAKE_CXX_STANDARD 11)
set(src_path, ${CMAKE_SOURCE_DIR}/)
include_directories(${src_path})

message(STATUS "this is src path "${src_path})
message(STATUS "this is binary dir " ${PROJECT_BINARY_DIR})
message(STATUS "this is SOURCE dir " ${PROJECT_SOURCE_DIR})

set(SOURCE_FILES
        ${src_path}sort.h
        ${src_path}dcl_list.h
        ${src_path}dcl_list.cc
        ${src_path}functions.h
        ${src_path}iterator.h
        ${src_path}lru_cache.h
        ${src_path}one_object.h
        ${src_path}pool_memory.h
        ${src_path}pool_memory.cc
        ${src_path}utility.h
        ${src_path}utility.cc
        ${src_path}unit_test.h
        ${src_path}common.cc
        ${src_path}list_op.h)
add_definitions("-ggdb -fPIC -ffunction-sections -O0 -std=c++11")
add_executable(common ${SOURCE_FILES})
target_link_libraries(common  "pthread" )

