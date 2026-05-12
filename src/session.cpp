#include "session.hpp"
#include "room.hpp"
#include <iostream>

Session::Session(tcp::socket socket, Room& room): socket_(std::move(socket)), room_(room){
}

void Session::start(){
  std::cout << "Client Connected" << std::endl;
  room_.join(shared_from_this());
  do_read();
}

void Session::do_read(){
  auto self = shared_from_this(); //keeps session alive while async operations are running.
  
  socket_.async_read_some(boost::asio::buffer(buffer_), [this, self](std::error_code er , std::size_t length){
    if (!er) {
      //std::cout << "Recieved: " << std::string(buffer_.data(), length) << std::endl;
      std::string msg(buffer_.data(), length);
      room_.broadcast(msg,self);
      do_read();
    } else {
      room_.leave(self);
      std::cout << "Client Disconnected" << std::endl;
    }});
  }

void Session::deliver(const std::string& message){
  do_write(message);
}

void Session::do_write(const std::string& message) {
  auto self = shared_from_this();
  boost::asio::async_write(socket_, boost::asio::buffer(message), [this, self](std::error_code er, std::size_t){
  });
}
