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
  std::vector<std::shared_ptr<Session>> snapshot;
  {
    std::lock_guard<std::mutex> lock(sessions_mutex);
    snapshot.reserve(sessions_.size());
    for (const auto& s : sessions_){
      if (s!=sender) snapshot.push_back(s);
    }
  }

  const std::string out = "Client " + std::to_string(sender->id()) + ": " + message;
  for (auto & s : snapshot) {
      s->deliver(out);
  }
}
  
