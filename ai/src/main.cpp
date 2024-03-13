#include "common/socket/socket.hpp"

using laser::com::Socket;

int main(int argc, char **charv) {
  auto sock = Socket("127.0.0.1", 5000);

  return 0;
}