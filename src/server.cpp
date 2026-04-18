#include <iostream>
#include <utility>
#include "server.hpp"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
Server::Server(boost::asio::io_context& io, short port) : acceptor_(io, tcp::endpoint(tcp::v4(), port)) {}

void Server::start_accept() {
  acceptor_.async_accept([this](std::error_code er, tcp::socket socket) {
    if (!er) handle_client(std::move(socket));
    start_accept();
  });
}

void Server::handle_client(tcp::socket socket){
  std::cout << "Client Connected" << std::endl;
}
