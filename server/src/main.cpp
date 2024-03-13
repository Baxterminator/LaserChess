#include "common/socket/server.hpp"

using laser::com::SocketServer;

int main(int argc, char **argv) {
  std::cout << "Initializing game server" << std::endl;
  auto com_server = SocketServer(5001);

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