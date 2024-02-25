#include <iostream>
#include <exception>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in

int runClient(int domain, int type, int protocol);
void checkStatus(int status_code, const std::string& func_name);

int main()
{
    const int DOMAIN = AF_INET;
    const int SOCK_TYPE = SOCK_STREAM;
    const int DEFAULT_PROTOCOL = 0;

    runClient(DOMAIN,
              SOCK_TYPE,
              DEFAULT_PROTOCOL);

    return 0;
}


int runClient(int domain, int type, int protocol)
{
    int status_code = 0;

    // get socket file descriptor
    int client_sfd = socket(domain, type, protocol);
    checkStatus(client_sfd, "socket");

    // prepare the point of connection
    struct sockaddr_in saddr;
    saddr.sin_family = domain;
    saddr.sin_port = htons(8080); // !!!
    saddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    status_code = connect(client_sfd,
                          reinterpret_cast<struct sockaddr*>(&saddr),
                          sizeof(saddr));
    checkStatus(status_code, "connect");

    return status_code;
}

void checkStatus(int status_code, const std::string& func_name)
{
    if (status_code < 0)
    {
        std::string err_msg = func_name + "() function error: " + std::to_string(status_code);
        throw std::runtime_error(err_msg);
    }
}
