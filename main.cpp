#include <iostream>
#include "../include/config.h"

using namespace fan;

int main() {
    auto c = Config::read_config("../example/fan.yaml");
    auto *l = c->levels();
    std::cout << l->size() << std::endl;
}
