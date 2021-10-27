//
// Created by skyne on 10/22/2021.
//

#ifndef BINANCE_TYPES_H
#define BINANCE_TYPES_H
#include "binance_common.h"
#include "binance_traits.h"
#include <exception>
#include <sstream>

namespace binance
{
    namespace types
    {
        template <typename T>
        struct binance_EXPORT Array
        {
            static constexpr auto _has_from_json = has_from_json<T>::value;
            void from_json(json_value &val)
            {
                // if (!val.is_array())
                // {
                // }
                // auto arr = val.as_array();
                // values.resize(arr.size());
                // int i{0};
                // for (auto &&el : arr)
                // {
                //     values[i].from_json(el);
                //     i++;
                // }
            }
            json_value to_json() const
            {
                // auto arr = json_value::array();
                // int i{0};
                // for (auto &&el : values)
                // {
                //     arr[i] = el.to_json();
                //     i++;
                // }
                return {};
            }

            std::vector<T> values;
        };
        namespace request
        {
            struct binance_EXPORT KLines
            {
                std::string symbol;
                std::string interval;
                milliseconds start_time;
                milliseconds end_time;
                int limit;

                template <typename T = u_params_map>
                T to_query_params() const
                {
                    T params{};
                    // params.insert(param_entry{_SU("symbol"), symbol});
                    // params.insert(param_entry{_SU("interval"), interval});
                    // if (start_time.count() > 0)
                    //     params.insert(param_entry{_SU("startTime"),
                    //                               _itoa(start_time.count())});
                    // if (end_time.count() > 0)
                    //     params.insert(param_entry{_SU("endTime"),
                    //                               _itoa(end_time.count())});
                    // if (limit > 0)
                    //     params.insert(param_entry{_SU("limit"),
                    //                               _itoa(limit)});
                    return params;
                }

                json_value to_json() const;
                void from_json(json_value &obj);
            };
        }
        namespace response
        {
            struct binance_EXPORT Error : std::exception
            {
                int64_t code;
                std::string message;

                json_value to_json() const;
                void from_json(json_value &obj);

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

                json_value to_json() const;
                void from_json(json_value &obj);
            };
        }
    }

    template <typename T = u_params_map>
    binance_EXPORT std::string to_query_string(const T &params)
    {
        std::ostringstream stream;
        std::string sym{"?"};
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
}

#endif // BINANCESDK_BINANCE_TYPES_H
