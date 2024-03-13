#include "common/socket/socket.hpp"

using laser::com::Socket;

int main(int argc, char **charv) {
  std::cout << "Initializing AI client" << std::endl;
  auto sock = Socket("127.0.0.1", 5001);
  if (sock.connectToServer()) {
    std::cout << "Waiting for message" << std::endl;
    std::string output;
    sock.receive_data(output);
    std::cout << "Received from server msg: (" << output << ")" << std::endl;

    std::cout << "Sending message" << std::endl;
    sock.send_data(";clientmsg\n");
  } else {
    std::cout << "Couldn't connect to server" << std::endl;
  }

  return 0;
}