#pragma once
#include <boost/asio.hpp>
#include <cstdint>
#include "room.hpp"

class Server {
public:
  Server(boost::asio::io_context& io, short port);
  void start_accept();

private:
  using tcp = boost::asio::ip::tcp;
  tcp::acceptor acceptor_;
  Room room_;
  std::uint64_t next_client_id_{1};
};
