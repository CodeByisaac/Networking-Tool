cmake_minimum_required(VERSION 3.31.6)

project(Networking-Tool)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost REQUIRED COMPONENTS filesystem)
find_package(Threads REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp src/server.cpp src/session.cpp src/room.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME}
  PRIVATE
  Boost::filesystem
  pthread
)

option(SANITIZE_THREAD "Build with ThreadSanitizer (Clang/GCC only)" OFF)

if(SANITIZE_THREAD)
  if(NOT CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    message(FATAL_ERROR "ThreadSanitizer requires Clang or GCC (use WSL: -DCMAKE_CXX_COMPILER=clang++)")
  endif()
  target_compile_options(${PROJECT_NAME} PRIVATE -fsanitize=thread -g -O1 -fno-omit-frame-pointer)
  target_link_options(${PROJECT_NAME} PRIVATE -fsanitize=thread)
endif()