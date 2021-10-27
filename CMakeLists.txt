cmake_minimum_required(VERSION 3.15)
project(binancesdk CXX)
set(CMAKE_CXX_STANDARD 17)
# include(${CMAKE_BINARY_DIR}/conan_paths.cmake) find_package(Boost REQUIRED
# COMPONENTS nowide system regex date_time json)
find_package(Boost 1.77.0 REQUIRED)
# find_package(date REQUIRED)

# include(${CMAKE_CURRENT_SOURCE_DIR}/build/conanbuildinfo.cmake)
# conan_basic_setup()
add_library(binancesdk "src/binance_types.cpp" "src/binance_client.cpp")
set_target_properties(binancesdk PROPERTIES PUBLIC_HEADER
                                            "src/binance_client.h")

if(BOOST_FOUND)
  message(STATUS "${Boost_INCLUDE_DIRS}")
  include_directories(${Boost_INCLUDE_DIRS})
  target_link_libraries(binancesdk Boost::headers ${Boost_LIBRARIES})
  # target_link_libraries (binancesdk Boost::system Boost::regex Boost::json
  # Boost::headers Boost::nowide Boost::date_time)
endif()

# if(DATE_FOUND) include_directories(${date_INCLUDE_DIRS}) target_link_libraries
# (binancesdk ${date_LIBRARIES}) endif() add_subdirectory(test_package)

install(
  TARGETS binancesdk
  DESTINATION "."
  PUBLIC_HEADER DESTINATION include
  RUNTIME DESTINATION bin
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
