#include <string>
#include "common/socket/socket.hpp"

class CommunicationClient {
    std::string IpAddress;
    int Port;
    laser::com:Socket Socket;

public:
    CommunicationClient(int port, std::string ipAddress) {
        Port = port;
        IpAddress = ipAddress;
        Socket = laser::com::Socket(IpAddress, Port); 
    }

    

};