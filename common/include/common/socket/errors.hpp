#ifndef LASER_SOCKET_ERRORS
#define LASER_SOCKET_ERRORS

namespace laser::com {

enum class SocketErrors {
  NO_ERROR1 = 0,
  DATA_EXCEEDING_BUFFER_LENGTH,
  SOCKET_ERROR1,
};

}

#endif