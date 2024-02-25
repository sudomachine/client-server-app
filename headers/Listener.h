#ifndef LISTENER_H
#define LISTENER_H

#include <cstdint>
#include <memory>

namespace srv {

class RequestHandler;

class Listener {

public:
    Listener(uint16_t port);

    void
    listen(uint32_t queue_size);

    void stop();

    std::shared_ptr<RequestHandler>
    accept();

private:
    int socket_;
};

} // srv namespace

#endif // LISTENER_H
