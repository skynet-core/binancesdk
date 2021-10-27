#ifndef BINANCE_COMMON_H
#define BINANCE_COMMON_H

#include <string>
#include <chrono>
#include <unordered_map>
#include <map>
#include <boost/multiprecision/cpp_dec_float.hpp>
#include <boost/json.hpp>

#ifdef WIN32
#define binance_EXPORT __declspec(dllexport)
#define ucout boost::nowide::cout
#define ucerr boost::nowide::cerr
#define ucin boost::nowide::cin
#else
#define ucout std::cout
#define ucerr std::cerr
#define ucin std::cin
#define binance_EXPORT
#endif

using milliseconds = std::chrono::milliseconds;
typedef const char *c_string;
template <typename T, typename U>
using u_dict = std::unordered_map<T, U>;

template <typename T, typename U>
using dict = std::map<T, U>;

using u_params_map = u_dict<std::string, std::string>;
using params_map = dict<std::string, std::string>;
using param_entry = std::pair<std::string, std::string>;
using big_float = boost::multiprecision::cpp_dec_float_50;
using json_value = boost::json::value;

#endif