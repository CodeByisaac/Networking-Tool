#include "server.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main() {
  try {
    boost::asio::io_context io;
    Server server(io, 8080);
    server.start_accept();

    //io.run();

    std::vector<std::thread> threads;
    for (int i = 0; i < std::thread::hardware_concurrency(); ++i) {
      threads.emplace_back([&io]{io.run();});
    }

    for (auto &t : threads) {
      t.join();
    }
    
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
    return 0;
}
