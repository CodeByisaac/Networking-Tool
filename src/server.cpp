#include <iostream>
#include <utility>
#include "server.hpp"
#include "session.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
Server::Server(boost::asio::io_context& io, short port) : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {}

void Server::start_accept() {
  acceptor_.async_accept([this](std::error_code er, tcp::socket socket) {
    if (!er) {
      std::make_shared<Session>(std::move(socket))->start(); 
    }
    start_accept();
  });
}
