#ifndef BINANCE_HTTP_
#define BINANCE_HTTP_

#include "binance_traits.h"
#include "binance_common.h"
#include <istream>
#include <iostream>
#include <exception>

namespace binance
{
    class HTTPProvider
    {
    public:
        HTTPProvider(std::string base_url,
                     std::string api_key = "",
                     std::string api_secret = "")
            : m_uri{base_url},
              m_api_key{api_key},
              m_api_secret{api_secret}
        {
        }

        template <typename T>
        typename std::enable_if_t<has_from_json<T>::value, T>
        post(const std::string &path, json_value &req)
        {
            return T{};
        }

        template <typename T, typename U = u_params_map>
        typename std::enable_if_t<has_from_json<T>::value, T>
        get(const std::string &path, const U &query_params = {})
        {
            return T{};
        }

    private:
        std::string m_uri;
        std::string m_api_key;
        std::string m_api_secret;
    };

} // namespace binance

#endif