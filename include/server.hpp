#pragma once
#include <boost/asio.hpp>

class Server {
public:
  Server(boost::asio::io_context& io, short port);
  void start_accept();

private:
  using tcp = boost::asio::ip::tcp;
  tcp::acceptor acceptor_;
  void handle_client(tcp::socket socket);
};
