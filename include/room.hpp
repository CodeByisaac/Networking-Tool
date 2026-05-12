#pragma once
#include <set>
#include <memory>
#include <string>

class Session;

class Room {
public:
  void join(std::shared_ptr<Session> session);
  void leave(std::shared_ptr<Session> session);
  void broadcast(const std::string& message, std::shared_ptr<Session> sender);

private:
  std::set<std::shared_ptr<Session>> sessions_;
};
