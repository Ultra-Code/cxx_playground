#include <cstddef>
#include <cstdlib>
#include <boost/asio.hpp>
#include <iostream>
#include <string_view>
// import<iostream>;
// import<string_view>;

using address  = boost::asio::ip::address;
using tcp      = boost::asio::ip::tcp;
using error    = boost::system::error_code;
using resolver = boost::asio::ip::tcp::resolver;
namespace ip   = boost::asio::ip;
namespace asio = boost::asio;

auto client_endpoints() -> int;
auto dns_resolver() -> int;
auto passive_socket() -> int;
auto active_socket() -> int;
auto server_endpoints() -> int;

auto
server_endpoints() -> int {

  const uint16_t port_number{2020};
  address ip_address{ip::address_v6::any()};
  tcp::endpoint endpoint{ip_address, port_number};
  return EXIT_SUCCESS;
}

auto
client_endpoints() -> int {
  std::string ip_address{"127.0.0.1"};
  const uint16_t port_number{2020};
  error error_codes{};
  address safe_ip_address{address::from_string(ip_address, error_codes)};
  if (error_codes.value() != 0) {
    std::cout << "Failed to Parse The IP Address. Error Code = "
              << error_codes.value() << " . Message : " << error_codes.message()
              << std::endl;
    return error_codes.value();
  }
  tcp::endpoint endpoint{safe_ip_address, port_number};
  return EXIT_SUCCESS;
}

auto
active_socket() -> int {
  asio::io_context io_service{};
  tcp protocal{tcp::v4()};
  tcp::socket socket{io_service}; // a passive socket uses the accecptor object
  error error_codes{};
  socket.open(protocal, error_codes);
  if (error_codes.value() != 0) {
    std::cout << "Failed to open the Socket! Error Code = "
              << error_codes.value() << ". Message : " << error_codes.message();
    return error_codes.value();
  }
  return EXIT_SUCCESS;
}

auto
passive_socket() -> int {
  asio::io_context os_network_io{};
  const tcp::endpoint endpoint{tcp::v4(), 2030};
  tcp::acceptor acceptor{os_network_io};
  error error_codes{};
  acceptor.open(endpoint.protocol(), error_codes);
  acceptor.bind(endpoint);
  return EXIT_SUCCESS;
}

auto
dns_resolver() -> int {
  asio::io_context os_network_io{};
  tcp protocal{tcp::v4()};
  std::string hostname{"www.google.com"};
  std::string port_number{"2020"};
  resolver::query dns_query{protocal, hostname, port_number,
                            resolver::query::numeric_service};
  resolver resolver{os_network_io};
  error error_codes{};
  resolver::iterator iterators{resolver.resolve(dns_query, error_codes)};
  // Handling errors if any.
  if (error_codes.value() != 0) {
    // Failed to resolve the DNS name. Breaking execution.
    std::cout << "Failed to resolve a DNS name."
              << "Error code = " << error_codes.value()
              << ". Message = " << error_codes.message();
    return error_codes.value();
  }
  for (resolver::iterator end_iterator{}; iterators != end_iterator;
       ++iterators) {
    tcp::endpoint endpoints{iterators->endpoint()};
    endpoints.size();
  }
  return EXIT_SUCCESS;
}
