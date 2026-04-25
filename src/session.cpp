#include "session.hpp"
#include <iostream>

Session::Session(tcp::socket socket): socket_(std::move(socket)){
}

void Session::start(){
  std::cout << "Client Connected" << std::endl;
  do_read();
}

void Session::do_read(){
  auto self = shared_from_this(); //keeps session alive while async operations are running.
  
  socket_.async_read_some(boost::asio::buffer(buffer_), [this, self](std::error_code er , std::size_t length){
    if (!er) {
      std::cout << "Recieved: " << std::string(buffer_.data(), length) << std::endl;
      do_write(length);
    } else {
      std::cout << "Client Disconnected" << std::endl;
    }});
  }

void Session::do_write(std::size_t length) {
  auto self = shared_from_this();
  boost::asio::async_write(socket_, boost::asio::buffer(buffer_, length), [this, self](std::error_code er, std::size_t){
    if (!er) do_read(); //continue reading 
  });
}
