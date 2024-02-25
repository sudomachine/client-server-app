#include "../headers/Listener.h"

#include <iostream>

#include <string>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in
#include <unistd.h> // close(socket)

namespace srv {

class RequestHandler{
public:
    RequestHandler(int socket): client_socket_(socket)
    {

    }

    int client_socket_;
};

} // srv namespace

inline void checkCode(int code, const std::string& func_name)
{
    if (code < 0)
    {
        std::string err_msg = func_name + "() function error: " + std::to_string(code);
        throw std::runtime_error(err_msg);
    }
}

srv::Listener::Listener(uint16_t port)
{
    int status_code = -1;

    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    checkCode(sfd, "Listener::socket");

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    status_code = bind(sfd,
                       reinterpret_cast<struct sockaddr*>(&addr),
                       sizeof(addr));
    checkCode(status_code, "Listener::bind");

    socket_ = sfd;
}

void
srv::Listener::listen(uint32_t queue_size)
{
    int status_code = -1;

    status_code = ::listen(socket_, queue_size);
    checkCode(status_code, "Listener::listen");
}

void
srv::Listener::stop()
{
    int status_code = -1;
    status_code = close(socket_);
    checkCode(status_code, "Listener::close");
}

std::shared_ptr<srv::RequestHandler>
srv::Listener::accept()
{
    sockaddr_in addr;
    socklen_t addr_len;
    int client_socket = ::accept(socket_,
                                 0, 0);
//                                 reinterpret_cast<struct sockaddr*>(&addr),
//                                 &addr_len);
    checkCode(client_socket, "Listener::accept");

    std::cout << "accepted client socket: " << std::to_string(client_socket) << std::endl;
//    std::cout << "server socket: " << std::to_string(socket_) << std::endl;

    return std::make_shared<srv::RequestHandler>(client_socket);
}
