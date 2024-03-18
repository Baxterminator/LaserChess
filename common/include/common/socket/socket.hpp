#ifndef BAXTERMINATOR_SOCKET_CLIENT
#define BAXTERMINATOR_SOCKET_CLIENT

#include "common/socket/base.hpp"
#include "common/socket/errors.hpp"

namespace laser::com {

/**
 * @brief Socket client for communication with others.
 */
class Socket : public SocketBase {
  // ===========================================================================
  // Constructors
  // ===========================================================================
 public:
  /**
   * @brief Initialize a client socket and connect to it
   *
   * @param ip the IP to the socket server
   * @param port the port of the socket server
   */
  Socket(const std::string &ip, int port);

  /**
   * @brief Create a new socket client based on an already existing socket
   *
   * @param sock the handle to the existing socket
   */
  Socket(SOCKET sock);

  Socket() {}

  // ===========================================================================
  // Methods
  // ===========================================================================
 public:
  /**
   * @brief Connect to the server.
   * @return true if successfull, false else
   */
  bool connectToServer();

  /**
   * @brief Send data through this socket
   *
   * @param data the message to send
   */
  SocketErrors send_data(const std::string &data) const;

  /**
   * @brief Receive message from the socket and push it in the output parameter.
   *
   * @param output where to fill in the received message
   */
  SocketErrors receive_data(std::string &output) const;

  // ===========================================================================
  // Members
  // ===========================================================================
 private:
  bool connected = false;  //< whether the socket is connected
  char SOM = ';';          //< Start of messages (for receiving)
  char EOM = '\n';         //< End of message (for receiving)
};

}  // namespace laser::com

#endif