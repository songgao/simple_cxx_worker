#ifndef HEADER_CLIENT_HPP
#define HEADER_CLIENT_HPP

#include "include/cppzmq/zmq.hpp"
#include <string>

namespace worker {
    std::string Do(std::string addr, std::string input) {
        zmq::context_t context (1);
        zmq::socket_t client(context, ZMQ_REQ);
        client.connect(addr.c_str());
        zmq::message_t req(input.size() + 1);
        client.send(input.c_str(), input.size() + 1, 0);
        zmq::message_t reply;
        client.recv(&reply);
        return std::string((char*)reply.data());
    }
}

#endif
