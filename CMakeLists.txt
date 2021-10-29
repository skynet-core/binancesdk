cmake_minimum_required(VERSION 3.15)

project(binancesdk CXX)

set(CMAKE_CXX_STANDARD 17)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

find_package(Boost REQUIRED)

find_package(uriparser CONFIG REQUIRED)

find_package(date REQUIRED)

# find_package(Catch2 CONFIG REQUIRED)
#     target_link_libraries(main PRIVATE Catch2::Catch2)

add_library(binancesdk "src/binance_types.cpp" "src/binance_client.cpp")

set_target_properties(binancesdk PROPERTIES PUBLIC_HEADER
                                            "src/binance_client.h")

target_link_libraries(binancesdk PRIVATE Boost::boost)
# target_link_libraries (binancesdk Boost::system Boost::regex Boost::json
  # Boost::headers Boost::nowide Boost::date_time)
target_link_libraries(binancesdk PRIVATE uriparser::uriparser)
target_link_libraries(binancesdk PRIVATE date::date date::date-tz)

install(
  TARGETS binancesdk
  DESTINATION "."
  PUBLIC_HEADER DESTINATION include
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
