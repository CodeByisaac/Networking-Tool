#pragma once
#include <boost/asio.hpp>
#include <cstdint>
#include <atomic>
#include "room_manager.hpp"

class Server {
public:
  Server(boost::asio::io_context& io, short port);
  void start_accept();

private:
  using tcp = boost::asio::ip::tcp;
  tcp::acceptor acceptor_;
  
  RoomManager room_manager_;
  std::atomic<std::uint64_t> next_client_id_{1};
};
