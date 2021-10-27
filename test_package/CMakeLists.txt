cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(binancesdk CONFIG REQUIRED)

add_executable(client_test src/http.cpp)
target_link_libraries(client_test binancesdk::binancesdk)
