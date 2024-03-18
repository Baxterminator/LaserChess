#include "common/args/parser.hpp"
#include "common/socket/server.hpp"
#include "server/server.hpp"

using laser::args::ArgumentParser;

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
  laser::server::GameServer server(port);
  server.wait_for_players();

  while (!server.is_game_done()) server.loop();

  return 0;
}