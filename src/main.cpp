#include "server.hpp"
#include <boost/asio.hpp>
#include <iostream>

int main() {
  try {
    boost::asio::io_context io;
    Server server(io, 8080);
    server.start_accept();

    io.run();
    
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
    return 0;
}
