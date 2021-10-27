#ifndef BINANCE_TRAITS
#define BINANCE_TRAITS
#include <type_traits>

namespace binance
{
    template <typename T>
    struct has_from_json
    {
        static constexpr auto value =
            std::is_member_function_pointer<decltype(&T::from_json)>::value;
    };
}
#endif