#ifndef BOOST_SESSION
#define BOOST_SESSION

#include "root_certificates.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/system_executor.hpp>
#include <uriparser/Uri.h>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace network = boost::network;
namespace beast = boost::beast;   // from <boost/beast.hpp>
namespace http = beast::http;     // from <boost/beast/http.hpp>
namespace net = boost::asio;      // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp; // from <boost/asio/ip/tcp.hpp>
namespace binance
{

    // Report a failure
    void fail(beast::error_code ec, char const *what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    class Session : public std::enable_shared_from_this<Session>
    {
        tcp::resolver resolver_;
        beast::ssl_stream<beast::tcp_stream> stream_;
        beast::flat_buffer buffer_; // (Must persist between reads)
        http::request<http::empty_body> req_;
        http::response<http::string_body> res_;
        std::string host_;
        std::string port_;
        int version_;

        // Objects are constructed with a strand to
        // ensure that handlers do not execute concurrently.
        session(net::strand<net::system_executor> strand,
                ssl::context &ctx,
                const std::string &uri,
                int version)
            : resolver_(strand), stream_(strand, ctx), version_(version)
        {
            // network::uri::uri instance("http://cpp-netlib.github.com/");
            // std::cout << instance.host << std::endl;
        }

    public:
        // Delegate construction to a private constructor to be able to use
        // the same strand for both I/O object.
        explicit session(ssl::context &ctx)
            : session(net::make_strand(net::system_executor()), ctx)
        {
        }

        // Start the asynchronous operation
        void
        run(
            const std::string &target,
            int version)
        {
            // Set SNI Hostname (many hosts need this to handshake successfully)
            if (!SSL_set_tlsext_host_name(stream_.native_handle(), host_))
            {
                beast::error_code ec{static_cast<int>(::ERR_get_error()),
                                     net::error::get_ssl_category()};

                throw ec; // TODO: custom exception
            }

            // Set up an HTTP GET request message
            req_.version(version_);
            req_.method(http::verb::get);
            req_.target(target);
            req_.set(http::field::host, host_);
            req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

            // Look up the domain name
            resolver_.async_resolve(
                host,
                port,
                beast::bind_front_handler(
                    &session::on_resolve,
                    shared_from_this()));
        }

        void
        on_resolve(
            beast::error_code ec,
            tcp::resolver::results_type results)
        {
            if (ec)
                return fail(ec, "resolve");

            // Set a timeout on the operation
            beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

            // Make the connection on the IP address we get from a lookup
            beast::get_lowest_layer(stream_).async_connect(
                results,
                beast::bind_front_handler(
                    &session::on_connect,
                    shared_from_this()));
        }

        void
        on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
        {
            if (ec)
                return fail(ec, "connect");

            // Perform the SSL handshake
            stream_.async_handshake(
                ssl::stream_base::client,
                beast::bind_front_handler(
                    &session::on_handshake,
                    shared_from_this()));
        }

        void
        on_handshake(beast::error_code ec)
        {
            if (ec)
                return fail(ec, "handshake");

            // Set a timeout on the operation
            beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

            // Send the HTTP request to the remote host
            http::async_write(stream_, req_,
                              beast::bind_front_handler(
                                  &session::on_write,
                                  shared_from_this()));
        }

        void
        on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);

            if (ec)
                return fail(ec, "write");

            // Receive the HTTP response
            http::async_read(stream_, buffer_, res_,
                             beast::bind_front_handler(
                                 &session::on_read,
                                 shared_from_this()));
        }

        void
        on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
        {
            boost::ignore_unused(bytes_transferred);

            if (ec)
                return fail(ec, "read");

            // Write the message to standard out
            std::cout << res_ << std::endl;

            // Set a timeout on the operation
            beast::get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

            // Gracefully close the stream
            stream_.async_shutdown(
                beast::bind_front_handler(
                    &session::on_shutdown,
                    shared_from_this()));
        }

        void
        on_shutdown(beast::error_code ec)
        {
            if (ec == net::error::eof)
            {
                // Rationale:
                // http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
                ec = {};
            }
            if (ec)
                return fail(ec, "shutdown");

            // If we get here then the connection is closed gracefully
        }
    };
}

#endif