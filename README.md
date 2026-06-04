# Networking-Tool
Multithreaded TCP server built in C++20 using Boost.Asio, capable of handling 300+ concurrent connections with low latency. clients can send and receive messages in real time, also has features like chat rooms and file transfers.

# Requirements
- C++20
- CMake 3.31.6
- Boost.Asio 1.90.0

# Architecture
One `Server` accepts clients; each client gets a `Session` for async I/O; all sessions share one `Room` for join/leave and broadcast.

<img width="448" height="699" alt="image" src="https://github.com/user-attachments/assets/9edfde7b-34d0-41c2-bb67-73ec65796ce7" />
