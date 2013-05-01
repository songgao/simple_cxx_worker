#include "../worker/worker.hpp"
#include <string>
#include <iostream>

#include <unistd.h>

std::string the_worker(std::string str) {
    return "Hello, " + str;
}

int main() {
    worker::worker w("tcp://*:55555", the_worker);
    auto pid = fork();
    if(-1 == pid)
        std::cout<<"Failure in fork()"<<std::endl;
    else if(0 == pid)
        w.start();
    else {
        std::cout<<"Forked. new PID: "<<pid<<std::endl;
        std::cout<<"use: `kill "<<pid<<"` to stop."<<std::endl;
    }
}
