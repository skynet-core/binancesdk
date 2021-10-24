//
// Created by skyne on 10/22/2021.
//

#ifndef BINANCE_TYPES_H
#define BINANCE_TYPES_H
#include "binance_common.h"
#include "binance_traits.h"
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/containerstream.h>
#include <cpprest/json.h>
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <unordered_map>
#include <map>
#include <vector>
#include <exception>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

using milliseconds = std::chrono::milliseconds;

template <typename T, typename U>
using u_dict = std::unordered_map<T, U>;

template <typename T, typename U>
using dict = std::map<T, U>;

using u_params_map = u_dict<string_t, string_t>;
using params_map = dict<string_t, string_t>;
using param_entry = std::pair<string_t, string_t>;
using big_float = boost::multiprecision::cpp_dec_float_50;

namespace binance
{

    template <typename T = u_params_map>
    binance_EXPORT string_t to_query_string(const T &params);
    namespace types
    {
        template <typename T>
        struct binance_EXPORT Array
        {
            static constexpr auto _has_from_json = has_from_json<T>::value;
            binance_EXPORT void from_json(json::value &val)
            {
                if (!val.is_array())
                {
                }
                auto arr = val.as_array();
                values.resize(arr.size());
                int i{0};
                for (auto &&el : arr)
                {
                    values[i].from_json(el);
                    i++;
                }
            }
            binance_EXPORT json::array to_json() const
            {
                auto arr = json::array(values.size);
                int i{0};
                for (auto &&el : values)
                {
                    arr[i] = el.to_json();
                    i++;
                }
                return arr;
            }

            std::vector<T> values;
        };
        namespace request
        {
            struct binance_EXPORT KLines
            {
                string_t symbol;
                string_t interval;
                milliseconds start_time;
                milliseconds end_time;
                int limit;

                template <typename T = u_params_map>
                binance_EXPORT T to_query_params() const
                {
                    T params{};
                    params.insert(param_entry{_SU("symbol"), symbol});
                    params.insert(param_entry{_SU("interval"), interval});
                    if (start_time.count() > 0)
                        params.insert(param_entry{_SU("startTime"),
                                                  _itoa(start_time.count())});
                    if (end_time.count() > 0)
                        params.insert(param_entry{_SU("endTime"),
                                                  _itoa(end_time.count())});
                    if (limit > 0)
                        params.insert(param_entry{_SU("limit"),
                                                  _itoa(limit)});
                    return params;
                }

                binance_EXPORT json::value to_json() const;
                binance_EXPORT void from_json(json::value &obj);
            };
        }
        namespace response
        {
            struct binance_EXPORT Error : std::exception
            {
                int64_t code;
                string_t message;

                binance_EXPORT json::value to_json() const;
                binance_EXPORT void from_json(json::value &obj);

                const char *what() const noexcept override;
            };
            struct binance_EXPORT KLine
            {
                milliseconds open_time;
                big_float open;
                big_float high;
                big_float low;
                big_float close;
                big_float volume;
                milliseconds close_time;
                big_float quote_asset_vol;
                int64_t number_of_trades;
                big_float taker_buy_base_asset_volume;
                big_float taker_buy_quote_asset_volume;
                big_float ignore;

                binance_EXPORT json::value to_json() const;
                binance_EXPORT void from_json(json::value &obj);
            };
        }
    }
}

template <typename T = u_params_map>
binance_EXPORT string_t binance::to_query_string(const T &params)
{
    ostringstream_t stream;
    string_t sym{"?"};
    for (auto &&pair : params)
    {
        stream
            << sym
            << pair.first
            << "="
            << pair.second;
        sym = "&";
    }
    sym = stream.str();
    return sym;
}

#endif // BINANCESDK_BINANCE_TYPES_H
