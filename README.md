# Networking-Tool
Multithreaded TCP server built in C++20 using Boost.Asio, capable of handling 300+ concurrent connections with low latency. clients can send and receive messages in real time, also has features like chat rooms and file transfers.

# Requirements
- C++20
- CMake 3.31.6
- Boost.Asio 1.90.0

# Architecture
One `Server` accepts clients; each client gets a `Session` for async I/O; all sessions share one `Room` for join/leave and broadcast.

<img width="564" height="704" alt="image" src="https://github.com/user-attachments/assets/1499f2d8-a7e4-42c4-bc90-9db7039ca3a6" />

