cmake_minimum_required(VERSION 3.15)
project(binancesdk CXX)

include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
conan_basic_setup()

add_library(binancesdk "src/binance_types.cpp" "src/binance_client.cpp")
set_target_properties(binancesdk PROPERTIES PUBLIC_HEADER "src/binance_client.h")

install(TARGETS binancesdk DESTINATION "."
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
