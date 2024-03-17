#ifndef BAXTERMINATOR_SOCKET_SERVER
#define BAXTERMINATOR_SOCKET_SERVER

#include "common/socket/socket.hpp"

namespace laser::com {

/**
 * @brief This class provide servers for accepting external client sockets.
 * It will return a Socket object for sending to and receiving from the distant client.
 */
class SocketServer : public SocketBase {
  // ===========================================================================
  // Constructors
  // ===========================================================================
 public:
  /**
   * @brief Initialize a socket server on the given port.
   *
   * @param port the port of the socket server
   */
  SocketServer(int port);

  // ===========================================================================
  // Methods
  // ===========================================================================
 public:
  /**
   * @brief Wait for a new client to connect and return a Socket handle to send and
   * receive data.
   *
   * @return SocketClient
   */
  Socket wait_for_client();
};

}  // namespace laser::com

#endif