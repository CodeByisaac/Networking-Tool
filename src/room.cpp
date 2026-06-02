#include "room.hpp"
#include "session.hpp"
#include <string>

void Room::join(std::shared_ptr<Session> session) {
  const std::lock_guard<std::mutex> lock(sessions_mutex);
  sessions_.insert(session);
}

void Room::leave(std::shared_ptr<Session> session) {
  const std::lock_guard<std::mutex> lock(sessions_mutex);
  sessions_.erase(session);
}

void Room::broadcast(const std::string& message, std::shared_ptr<Session> sender) {
  std::unique_lock<std::mutex> lock(sessions_mutex);
  auto snapshot = sessions_;
  lock.unlock();
  const std::string out = "Client " + std::to_string(sender->id()) + ": " + message;
  for (auto & s : snapshot) {
    if (s != sender) {
      s->deliver(out);
    }
  }
}
  
