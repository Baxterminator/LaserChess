#ifndef LASER_SOCKET_ERRORS
#define LASER_SOCKET_ERRORS

namespace laser::com {

enum class SocketErrors {
  NO_ERROR = 0,
  DATA_EXCEEDING_BUFFER_LENGTH,
  SOCKET_ERROR,
};

}

#endif