#include "ai/AIClient.hpp"
#include "common/args/parser.hpp"
#include "common/game/board.hpp"
#include "common/game/messages.hpp"
#include "common/math/vector.hpp"
#include "common/socket/errors.hpp"
#include "common/socket/socket.hpp"

using laser::ai::LaserChessAI;
using laser::args::ArgumentParser;
using laser::com::Messages;

ArgumentParser make_parser() {
  auto parser = ArgumentParser();
  parser.add_arg("--port");
  parser.add_arg("--ip");
  return parser;
}

void MessageParser(Messages clientMessage, std::string message);

int main(int argc, char **argv) {
  // Argument parsing
  auto parser = make_parser();
  parser.parse_args(argc, argv);
  parser.display_args();

  auto srv_ip = parser.get<std::string>("--ip", "127.0.0.1");
  auto srv_port = parser.get<int>("--port", 5001);

  LaserChessAI ai(srv_ip, srv_port);
  if (ai.connectToServer()) {
    std::cout << "Connected to server " << srv_ip << ":" << srv_port << std::endl;
    std::cout << "Waiting for level description ..." << std::endl;
    while (!ai.is_game_done()) {
      ai.loop();
    }
  } else
    std::cout << "Couldn't connect to server" << std::endl;

  return 0;
}