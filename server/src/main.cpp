#include <memory>

#include "common/args/parser.hpp"
#include "common/game/pieces/constants.hpp"
#include "common/socket/server.hpp"
#include "server/player.hpp"
#include "server/server.hpp"

using laser::args::ArgumentParser;

ArgumentParser make_parser() {
  auto parser = ArgumentParser();
  parser.add_arg("--port");
  parser.add_arg("--level");
  return parser;
}

int main(int argc, char **argv) {
  // Argument parsing
  auto parser = make_parser();
  parser.parse_args(argc, argv);
  parser.display_args();
  auto port = parser.get<int>("--port", 5001);
  auto lvl = parser.get<std::string>("--level", "level1");

  std::cout << "Initializing game server on port " << port << std::endl;
  auto server = laser::server::GameServer(port);
  server.loadLevel(lvl.c_str());
  server.waitForPlayers();
  while (!server.isGameDone()) server.loop();

  return 0;
}