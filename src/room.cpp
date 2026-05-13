#include "room.hpp"
#include "session.hpp"
#include <string>

void Room::join(std::shared_ptr<Session> session) {
   sessions_.insert(session);
}

void Room::leave(std::shared_ptr<Session> session) {
  sessions_.erase(session);
}

void Room::broadcast(const std::string& message, std::shared_ptr<Session> sender) {
  const std::string out =
      "Client " + std::to_string(sender->id()) + ": " + message;
  for (auto & s : sessions_) {
    if (s != sender) s->deliver(out);
  }
}
  
