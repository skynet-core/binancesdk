cmake_minimum_required(VERSION 3.15)
project(binancesdk CXX)

add_library(binancesdk "src/binance_types.cpp" "src/binance_client.cpp")
set_target_properties(binancesdk PROPERTIES PUBLIC_HEADER "src/binance_client.h")

install(TARGETS binancesdk DESTINATION "."
        PUBLIC_HEADER DESTINATION include
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        )
