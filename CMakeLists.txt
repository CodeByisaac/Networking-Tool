cmake_minimum_required(VERSION 3.31.6)

project(Networking-Tool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/server.cpp src/session.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Boost::filesystem
  pthread
)
