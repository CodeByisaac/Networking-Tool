#ifndef ROOM_MANAGER_HPP
#define ROOM_MANAGER_HPP

#include <unordered_map>
#include <string>
#include <memory>
#include <mutex>
#include "room.hpp"

class RoomManager {
    public:
        RoomManager(const RoomManager&) = delete;
        RoomManager& operator = (const RoomManager&) = delete;
        RoomManager() = default;


        std::shared_ptr<Room> get_or_create_room(const std::string& room_name){
            std::lock_guard<std::mutex> lock(mutex_);
            auto it = rooms_.find(room_name);
            
            if (it == rooms_.end()) {
                auto new_room = std::make_shared<Room>();
                rooms_[room_name] = new_room; 
                return new_room;
            }
            return it->second;
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<Room>> rooms_;
        std::mutex mutex_;
};

#endif