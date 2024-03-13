#include "common/args/parser.hpp"
#include "common/socket/server.hpp"

using laser::args::ArgumentParser;
using laser::com::SocketServer;

ArgumentParser make_parser() {
  auto parser = ArgumentParser();
  parser.add_arg("--port");
  return parser;
}

int main(int argc, char **argv) {
  // Argument parsing
  auto parser = make_parser();
  parser.parse_args(argc, argv);
  parser.display_args();
  auto port = parser.get<int>("--port", 5001);

  std::cout << "Initializing game server on port " << port << std::endl;
  auto com_server = SocketServer(port);

  // Wait for both player
  auto player1 = com_server.wait_for_client();
  // auto player2 = com_server.wait_for_client();

  std::cout << "Sending message" << std::endl;
  player1.send_data(";testmsg\n");

  std::cout << "Waiting for message" << std::endl;
  std::string output;
  player1.receive_data(output);
  std::cout << "Received from client msg: (" << output << ")" << std::endl;

  return 0;
}