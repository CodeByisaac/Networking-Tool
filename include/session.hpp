#pragma once
#include <boost/asio.hpp>
#include <cstdint>
#include <memory>
#include <string>
#include <array>

class Room;

class Session : public std::enable_shared_from_this<Session> {
public:
  using tcp = boost::asio::ip::tcp;
  Session(tcp::socket socket, Room &room, std::uint64_t client_id);
  void start();
  void deliver(const std::string& message);
  std::uint64_t id() const { return client_id_; }

private:
  tcp::socket socket_;
  Room& room_;
  std::uint64_t client_id_;
  std::array<char, 1024> buffer_;
  
  void do_read();
  void do_write(const std::string& message);
};
