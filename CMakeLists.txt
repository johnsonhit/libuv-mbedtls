cmake_minimum_required(VERSION 2.6)
project(libuv_mbedtls C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(libuv)
add_subdirectory(mbedtls)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/libuv/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/mbedtls/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(libuv_mbedtls
        include/bio.h
        include/tls_engine.h
        include/uv_tls.h
        src/bio.c
        src/tls_engine.c
        src/uv_tls.c)

target_link_libraries(libuv_mbedtls uv_a mbedtls)
