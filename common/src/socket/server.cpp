#include "common/socket/server.hpp"

#include "common/socket/base.hpp"

namespace laser::com {

SocketServer::SocketServer(int port) : SocketBase(port) { (void)bind(sock, (sockaddr *)&hint, sizeof(hint)); }

Socket SocketServer::wait_for_client() { return Socket(wait_for_client_raw()); }

SOCKET SocketServer::wait_for_client_raw() {
  // Wait for a client
  if (listen(sock, SOMAXCONN) == -1) {
    std::cout << "Too many sockets :/" << std::endl;
    return INVALID_SOCKET;
  }

  // Get client
  sockaddr_in client;
#ifdef _WIN32
  int clientSize = sizeof(client);
#else
  unsigned int clientSize = sizeof(client);
#endif
  SOCKET clientSocket = accept(sock, (sockaddr *)&client, &clientSize);

  // Get client data
  char host[NI_MAXHOST];
  char service[NI_MAXSERV];
  memset(host, 0, NI_MAXHOST);
  memset(service, 0, NI_MAXSERV);
  if (getnameinfo((sockaddr *)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
    std::cout << host << " connected on port " << service << std::endl;
  } else {
    inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
    std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
  }
  return clientSocket;
}

}  // namespace laser::com