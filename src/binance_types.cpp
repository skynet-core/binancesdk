#include "binance_types.h"

json_value binance::types::request::KLines::to_json() const
{
    // json_value obj;
    // obj[_SU("symbol")] = json::value::string(symbol);
    // obj[_SU("interval")] = json::value::string(interval);
    // if (start_time.count() > 0)
    //     obj[_SU("startTime")] = json::value::number(start_time.count());
    // if (end_time.count() > 0)
    //     obj[_SU("endTime")] = json::value::number(end_time.count());
    // if (limit > 0)
    //     obj[_SU("limit")] = json::value::number(limit);

    return {};
}
void binance::types::request::KLines::from_json(json_value &obj)
{
    // symbol = std::move(obj[_SU("symbol")].as_string());
    // interval = std::move(obj[_SU("interval")].as_string());
    // start_time = milliseconds(obj[_SU("startTime")].as_number().to_int64());
    // end_time = milliseconds(obj[_SU("endTime")].as_number().to_int64());
    // limit = obj[_SU("limit")].as_integer();
}

void binance::types::response::Error::from_json(json_value &val)
{
    // code = val[_SU("code")].as_integer();
    // message = val[_SU("msg")].as_string();
}

json_value binance::types::response::Error::to_json() const
{
    json_value obj;
    // obj[_SU("msg")] = json::value::string(message);
    // obj[_SU("code")] = json::value::number(code);
    return {};
}

const char *binance::types::response::Error::what() const noexcept
{
    return nullptr;
    // return message.data();
}

void binance::types::response::KLine::from_json(json_value &val)
{
    // if (!val.is_array())
    // {
    //     // TODO: format error ...
    //     throw;
    // }
    // auto arr = val.as_array();
    // if (arr.size() < 12)
    // {
    //     // TODO: format error ...
    //     throw;
    // }
    // open_time = milliseconds{arr[0].as_number().to_int64()};
    // open = big_float{arr[1].as_string()};
    // high = big_float{arr[2].as_string()};
    // low = big_float{arr[3].as_string()};
    // close = big_float{arr[4].as_string()};
    // volume = big_float{arr[5].as_string()};
    // close_time = milliseconds{arr[6].as_number().to_int64()};
    // quote_asset_vol = big_float{arr[7].as_string()};
    // number_of_trades = arr[8].as_number().to_int64();
    // taker_buy_base_asset_volume = big_float{arr[9].as_string()};
    // taker_buy_quote_asset_volume = big_float{arr[10].as_string()};
    // ignore = big_float{arr[11].as_string()};
}

json_value binance::types::response::KLine::to_json() const
{
    return {};
}