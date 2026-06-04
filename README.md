# Networking-Tool
Multithreaded TCP server built in C++20 using Boost.Asio, capable of handling 300+ concurrent connections with low latency. clients can send and receive messages in real time, also has features like chat rooms and file transfers.

# Requirements
- C++20
- CMake 3.31.6
- Boost.Asio 1.90.0

# Architecture
One `Server` accepts clients; each client gets a `Session` for async I/O; all sessions share one `Room` for join/leave and broadcast.

<img width="456" height="690" alt="image" src="https://github.com/user-attachments/assets/8fed56b4-5b9d-4f2b-af33-b276c9186c27" />
