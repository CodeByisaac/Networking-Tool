#pragma once
#include <boost/asio.hpp>
#include <memory>
#include <string>
#include <array>

class Room;

class Session : public std::enable_shared_from_this<Session> {
public:
  using tcp = boost::asio::ip::tcp;
  Session(tcp::socket socket, Room &room);
  void start();
  void deliver(const std::string& message);

private:
  tcp::socket socket_;
  Room& room_;
  std::array<char, 1024> buffer_;
  
  void do_read();
  void do_write(const std::string& message);
};
