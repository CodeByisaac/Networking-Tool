#include "session.hpp"
#include "room.hpp"
#include <iostream>

Session::Session(tcp::socket socket, Room& room, std::uint64_t client_id)
    : socket_(std::move(socket)),
      strand_(boost::asio::make_strand(socket_.get_executor())),
      room_(room),
      client_id_(client_id) {}

void Session::start(){
  std::cout << "Client " << client_id_ << " connected" << std::endl;
  auto self = shared_from_this();
  boost::asio::post(strand_, [this, self]() {
    room_.join(self);
    do_read();
  });
}

void Session::do_read(){
  auto self = shared_from_this(); //keeps session alive while async operations are running.
  
  socket_.async_read_some(boost::asio::buffer(buffer_), 
  boost::asio::bind_executor(strand_, [this, self](boost::system::error_code er , std::size_t length){
      if (!er) {
        //std::cout << "Recieved: " << std::string(buffer_.data(), length) << std::endl;
        std::string msg(buffer_.data(), length);
        room_.broadcast(msg,self);
        do_read();
      } else {
        room_.leave(self);
        std::cout << "Client " << client_id_ << " disconnected" << std::endl;
      }
    }));
  }

void Session::deliver(const std::string& message){
  auto self = shared_from_this();
  boost::asio::post(strand_, [this, self, message]() {
    bool was_idle = writeq.empty();
    writeq.push_back(message);
    if (was_idle) {
      do_write();
    }
  });
}

void Session::do_write() {
  auto self = shared_from_this();
  boost::asio::async_write(socket_,
    boost::asio::buffer(writeq.front()), 
    boost::asio::bind_executor(strand_, [this, self] (boost::system::error_code er, std::size_t){
    if (!er) {
      writeq.pop_front();
      if (!writeq.empty()) do_write();
    } else {
        room_.leave(self);
        std::cout << "Client" << client_id_ << "disconnected" << std::endl;
      }
  }));
}
