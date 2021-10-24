#ifndef BINANCE_COMMON_H
#define BINANCE_COMMON_H
#include <string>
#define _TURN_OFF_PLATFORM_STRING 1
#include <cpprest/details/basic_types.h>
using namespace utility; // Common utilities like string conversions

#ifdef WIN32
#define binance_EXPORT __declspec(dllexport)
#else
#define binance_EXPORT
#endif

#ifdef WIN32
template <typename T>
constexpr string_t _itoa(T v)
{
    return std::to_wstring(v);
}
#else
template <typename T>
constexpr string_t _itoa(T v)
{
    return std::to_string(v);
}
#endif
#define _SU(x) _XPLATSTR(x)

#endif