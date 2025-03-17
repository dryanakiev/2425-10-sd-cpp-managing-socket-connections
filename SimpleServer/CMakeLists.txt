cmake_minimum_required(VERSION 3.10)

project(HttpServer)

set(CMAKE_CXX_STANDARD 11)

add_executable(HttpServer main.cpp HttpServer.cpp)

# Link the necessary Winsock library
target_link_libraries(HttpServer ws2_32)