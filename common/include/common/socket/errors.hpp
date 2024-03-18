#ifndef LASER_SOCKET_ERRORS
#define LASER_SOCKET_ERRORS

namespace laser::com {

enum class SocketErrors {
  NO_ERROR = 0,
  DATA_EXCEEDING_BUFFER_LENGTH,
  SOCKET_ERROR,
  NO_INIT,
};

inline const char* error2String(SocketErrors error) {
  switch (error) {
    case SocketErrors::NO_ERROR:
      return "NO_ERROR";
    case SocketErrors::DATA_EXCEEDING_BUFFER_LENGTH:
      return "DATA_EXCEEDING_BUFFER_LENGTH";
    case SocketErrors::SOCKET_ERROR:
      return "SOCKET_ERROR";
    case SocketErrors::NO_INIT:
      return "NO_INIT";
    default:
      return "UNKNOWN";
  }
}

}  // namespace laser::com

#endif