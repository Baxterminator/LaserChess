#include "common/socket/server.hpp"

using laser::com::SocketServer;

int main(int argc, char **argv) {
  auto com_server = SocketServer(5000);

  // Wait for both player
  auto player1 = com_server.wait_for_client();
  auto player2 = com_server.wait_for_client();

  return 0;
}