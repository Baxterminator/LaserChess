#include "common/socket/socket.hpp"

#include "common/socket/base.hpp"
#include "common/socket/errors.hpp"

namespace laser::com {

Socket::Socket(const std::string &ip, int port) : SocketBase(ip, port) {}

Socket::Socket(SOCKET _sock) : SocketBase(), connected(true) { sock = _sock; }

bool Socket::connectToServer() {
  // If already connected, then we are connected
  if (connected) return connected;

  // Else connected to server
  connected = connect(sock, (sockaddr *)&hint, sizeof(hint)) != SOCKET_ERROR;
  if (!connected) {
    quit_socket();
    close_socket();
  }
  return connected;
}

///////////////////////////////////////////////////////////////////////////////

SocketErrors Socket::send_data(const std::string &data) const {
  if (!is_init()) return SocketErrors::NO_INIT;

  if (data.size() > BUFF_SIZE) return SocketErrors::DATA_EXCEEDING_BUFFER_LENGTH;

  if (send(sock, data.c_str(), data.size() + 1, 0) == SOCKET_ERROR) {
    return SocketErrors::SOCKET_ERROR;
  }

  return SocketErrors::NO_ERROR;
}

SocketErrors Socket::receive_data(std::string &output) const {
  if (!is_init()) return SocketErrors::NO_INIT;

  char buff[BUFF_SIZE];
  memset(buff, '\0', BUFF_SIZE);
  int buff_idx = 0;

  // Read one byte at the time
  while (true) {
    int bytesReceived = recv(sock, &buff[buff_idx], 1, 0);

    // If socket error, returns
    if (bytesReceived == SOCKET_ERROR) {
      output = "";
      return SocketErrors::SOCKET_ERROR;
    }

    // If nothing happened, re run
    if (bytesReceived != 1) continue;

    // Incrementing position in buffer
    if (buff_idx == 0 && buff[0] == SOM)
      buff_idx = 1;
    else
      buff_idx++;

    // Check for message ending
    if (buff_idx >= BUFF_SIZE - 1) {
      buff[BUFF_SIZE - 1] = '\0';
      output = std::string(buff, 0, BUFF_SIZE);
      return SocketErrors::DATA_EXCEEDING_BUFFER_LENGTH;
    } else if (buff[buff_idx - 1] == EOM) {
      buff[++buff_idx] = '\0';
      output = std::string(buff, 0, BUFF_SIZE);
      return SocketErrors::NO_ERROR;
    }
    // TODO: Add timeout
  }
}

}  // namespace laser::com