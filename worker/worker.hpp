#ifndef HEADER_WORKER_HPP
#define HEADER_WORKER_HPP

#include "include/cppzmq/zmq.hpp"
#include <string>
#include <functional>
#include <thread>
#include <iostream>

namespace worker {

    class worker {
        public:
            typedef std::function<std::string(std::string)> THE_WORKER_TYPE;
            inline worker(std::string addr, THE_WORKER_TYPE the_worker) {
                this->addr = addr;
                this->the_worker = the_worker;

                this->context = new zmq::context_t(1);
            }
            inline void start() {
                zmq::socket_t socket(*this->context, ZMQ_REP);
                socket.bind(this->addr.c_str());
                while(true) {
                    zmq::message_t input;
                    socket.recv(&input);
                    std::string out_str = the_worker(std::string((char*)input.data()));
                    zmq::message_t output(out_str.size() + 1);
                    std::memcpy((void *)output.data(), out_str.c_str(), out_str.size() + 1);
                    socket.send(output);
                }
            }
        private:
            std::string addr;
            THE_WORKER_TYPE the_worker;

            zmq::context_t * context;
    };

}
#endif
