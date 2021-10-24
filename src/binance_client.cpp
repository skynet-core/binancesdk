#include "binance_client.h"

binance::Client::Client(const string_t &api_key, const string_t &secret, const string_t &base_url)
    : m_client{std::make_shared<http_client>(base_url)}
{
}