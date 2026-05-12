#include "room.hpp"
#include "session.hpp"

void Room::join(std::shared_ptr<Session> session) {
   sessions_.insert(session);
}

void Room::leave(std::shared_ptr<Session> session) {
  sessions_.erase(session);
}

void Room::broadcast(const std::string& message, std::shared_ptr<Session> sender) {
  for (auto & s : sessions_) {
    if (s != sender) s->deliver(message);
  }
}
  
