#include "../worker/client.hpp"
#include <string>
#include <iostream>

int main() {
    std::cout<<worker::Do("tcp://127.0.0.1:55555", "world")<<std::endl;
}
