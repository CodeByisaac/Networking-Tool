#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <array>

class Session : public std::enable_shared_from_this<Session> {
public:
  using tcp = boost::asio::ip::tcp;
  Session(tcp::socket socket);
  void start();

private:
  tcp::socket socket_;
  std::array<char, 1024> buffer_;
  
  void do_read();
  void do_write(std::size_t length);
};
