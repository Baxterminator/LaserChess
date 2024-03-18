#ifdef _WIN32
#pragma comment(lib, "wsock32.lib")
#pragma comment(lib, "Ws2_32.lib")
#endif
#include "common/socket/base.hpp"

namespace laser::com {

SocketBase::SocketBase() {}

// Server socket init
SocketBase::SocketBase(unsigned int port) {
  making_socket(port);
#ifdef _WIN32
  hint.sin_addr.S_un.S_addr = INADDR_ANY;
#else
  hint.sin_addr.s_addr = INADDR_ANY;
#endif
}

SocketBase::SocketBase(const std::string &ip, int port) {
  making_socket(port);
  inet_pton(AF_INET, ip.c_str(), &hint.sin_addr);
}

SocketBase::~SocketBase() {
  quit_socket();
  close_socket();
}

///////////////////////////////////////////////////////////////////////////////

void SocketBase::making_socket(unsigned int port) {
  init_socket();
  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (!is_init()) {
    quit_socket();
    return;
  }

  // Configuring socket
  hint.sin_family = AF_INET;
  hint.sin_port = htons(port);
}

///////////////////////////////////////////////////////////////////////////////

int SocketBase::init_socket() {
#ifdef _WIN32
  WSADATA wsa_data;
  return WSAStartup(MAKEWORD(2, 0), &wsa_data);
#else
  return 0;
#endif
}

int SocketBase::quit_socket() {
#ifdef _WIN32
  return WSACleanup();
#else
  return 0;
#endif
}

int SocketBase::close_socket() {
  int status = 0;
#ifdef _WIN32
  status = shutdown(sock, SD_BOTH);
  if (status == 0) {
    status = closesocket(sock);
  }
#else
  status = shutdown(sock, SHUT_RDWR);
  if (status == 0) {
    status = close(sock);
  }
#endif

  sock = INVALID_SOCKET;
  return status;
}

}  // namespace laser::com