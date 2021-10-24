#ifndef BINANCE_CLIENT_H
#define BINANCE_CLIENT_H
#include "binance_common.h"
#include "binance_traits.h"
#include "binance_types.h"
#include <cpprest/http_client.h>
#include <cpprest/http_msg.h>
#include <cpprest/filestream.h>
#include <cpprest/containerstream.h>
#include <memory>
#include <iostream>

using namespace web;                  // Common features like URIs.
using namespace web::http;            // Common HTTP functionality
using namespace web::http::client;    // HTTP client features
using namespace concurrency::streams; // Asynchronous streams

namespace binance
{
    static const string_t ApiBaseUrl{_SU("https://api.binance.com")};

    class binance_EXPORT Client
    {
    public:
        Client(const string_t &api_key, const string_t &secret,
               const string_t &base_url = ApiBaseUrl);

        template <typename T>
        typename std::enable_if_t<has_from_json<T>::value, T>
        post(const string_t &path, json::value &req)
        {
            return m_client->request(_SU("POST"), path)
                .then([=](http_response response)
                      { return response.extract_json(); })
                .then([=](json::value val)
                      {
#ifdef DUMP_RES
                          utility::stringstream_t stream;
                          result.second.serialize(stream);
                          ucout << stream.str() << std::endl;
#endif
                          T result{};
                          result.from_json(val);
                          return result;
                      })
                .get();
        }

        template <typename T, typename U = u_params_map>
        typename std::enable_if_t<has_from_json<T>::value, T>
        get(const string_t &path, const U &req)
        {
            return m_client->request(_SU("GET"), path + to_query_string(req))
                .then([=](http_response response)
                      {
                          auto p = std::make_pair(
                              response.status_code(),
                              response.extract_json().get());
                          return p;
                      })
                .then([=](std::pair<status_code, json::value> result)
                      {
                          auto code = result.first;
                          if (code == status_codes::OK)
                          {
#ifdef DUMP_RES
                              utility::stringstream_t stream;
                              result.second.serialize(stream);
                              ucout << stream.str() << std::endl;
#endif
                              T res{};
                              res.from_json(result.second);
                              return res;
                          }
                          types::response::Error err{};
                          err.from_json(result.second);
                          throw err;
                      })
                .get();
        }

    private:
        std::shared_ptr<http_client> m_client;
        string_t m_base_url;
        string_t m_api_key;
        string_t m_api_secret;
    };
}

#endif