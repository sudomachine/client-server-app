#include <iostream>
#include <exception>
#include <string>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> // sockaddr_in

int runServer(int domain, int type, int protocol, int port);
void checkStatus(int status_code, const std::string& func_name);

int main()
{
    const int DOMAIN = AF_INET;
    const int SOCK_TYPE = SOCK_STREAM;
    const int DEFAULT_PROTOCOL = 0;
    const int PORT = 8080;

    runServer(DOMAIN,
              SOCK_TYPE,
              DEFAULT_PROTOCOL,
              PORT);

    return 0;
}


int runServer(int domain, int type, int protocol, int port)
{
    int status_code = 0;

    // get socket file descriptor
    int server_sfd = socket(domain, type, protocol);
    checkStatus(server_sfd, "socket");

    // prepare the point of connection
    struct sockaddr_in saddr;
    saddr.sin_family = domain;
    saddr.sin_port = htons(port);
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // bind address
    status_code = bind(server_sfd,
                       reinterpret_cast<struct sockaddr *>(&saddr),
                       sizeof(saddr));
    checkStatus(status_code, "bind");

    // listen port
    status_code = listen(server_sfd, 10);
    checkStatus(status_code, "listen");

    // get response from clients
    int client_sfd = 0;
    sockaddr_in client_addr;
    socklen_t client_addr_len;
    while (true)
    {
        client_sfd = accept(server_sfd,
                            reinterpret_cast<struct sockaddr*>(&client_addr),
                            &client_addr_len);

        std::cout << "client is connected" << std::endl;

    }

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
