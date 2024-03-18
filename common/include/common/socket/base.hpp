#ifndef BAXTERMINATOR_SOCKET_BASE
#define BAXTERMINATOR_SOCKET_BASE

// Windows specific
#ifdef _WIN32
#include <Ws2tcpip.h>
#include <winsock2.h>

// UNIX specific
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>

typedef int SOCKET;
const int INVALID_SOCKET = 0;
const int SOCKET_ERROR = -1;
#endif

// Common dependencies
#include <atomic>
#include <cstring>
#include <functional>
#include <iostream>
#include <string>

#include "common/socket/errors.hpp"

namespace laser::com {

const int BUFF_SIZE = 4096;

/**
 * @brief This interface provide a OS agnostic way of manipulating sockets in a simple way.
 */
struct SocketBase {
  /**
   * @brief Empty constructor to make a socket client from an already existing socket.
   */
  SocketBase();

  /**
   * @brief Initialize a new server socket with the given port.
   * @param port the port to open the server on
   */
  SocketBase(unsigned int port);

  /**
   * @brief Initialize a new client socket with the given couple (ip, port)
   * @param ip the ip of the server
   * @param port the port of the server
   */
  SocketBase(const std::string &ip, int port);

  /**
   * @brief Destroy the socket object by closing it and cleaning up after.
   */
  ~SocketBase();

  // ===========================================================================
  // Utils
  // ===========================================================================
  inline bool is_init() const { return (sock != INVALID_SOCKET && sock != SOCKET_ERROR); }

  // ===========================================================================
  // Windows specific socket implementations
  // ===========================================================================
 private:
  /**
   * @brief Initialize a socket.
   * @return 0 on success
   */
  int init_socket();

 protected:
  /**
   * @brief Quit a socket connection
   * @return 0 on success
   */
  int quit_socket();

  /**
   * @brief Close a socket connection
   * @return 0 on success, else the status for the closing action
   */
  int close_socket();

  // ===========================================================================
  // Wrappers
  // ===========================================================================
 private:
  /**
   * @brief Wrapper for creating a socket
   */
  void making_socket(unsigned int port);

  // ===========================================================================
  // Socket members
  // ===========================================================================
 protected:
  SOCKET sock = INVALID_SOCKET;  //< Socket handler
  sockaddr_in hint;              //< Socket informations
};

}  // namespace laser::com

#endif
