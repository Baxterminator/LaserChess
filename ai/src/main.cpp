#include "common/args/parser.hpp"
#include "common/socket/socket.hpp"

using laser::args::ArgumentParser;
using laser::com::Socket;

ArgumentParser make_parser() {
  auto parser = ArgumentParser();
  parser.add_arg("--port");
  parser.add_arg("--ip");
  return parser;
}

int main(int argc, char **argv) {
  // Argument parsing
  auto parser = make_parser();
  parser.parse_args(argc, argv);
  parser.display_args();

  auto ip = parser.get<std::string>("--ip", "127.0.0.1");
  auto port = parser.get<int>("--port", 5001);

  std::cout << "Initializing AI client with server (" << ip << ":" << port << ")" << std::endl;
  auto sock = Socket(ip, port);
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