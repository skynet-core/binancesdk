#ifndef BINANCE_CLIENT_H
#define BINANCE_CLIENT_H
#include "binance_common.h"
#include "binance_traits.h"
#include "binance_types.h"
#include "binance_http.h"
#include <memory>
#include <iostream>

namespace binance
{
    static const std::string ApiBaseUrl{"https://api.binance.com"};

    class binance_EXPORT Client
    {
    public:
        Client(const std::string &api_key = "", const std::string &secret = "",
               const std::string &base_url = ApiBaseUrl)
               : m_http_provider{base_url, api_key,secret} {}

    private:
        HTTPProvider m_http_provider;
    };
}

#endif