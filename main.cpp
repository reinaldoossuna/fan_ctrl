#include <iostream>
#include <string>
#include <vector>
#include "yaml-cpp/yaml.h"

int main() {
  YAML::Node config = YAML::LoadFile("../example/fan.yaml");
  
  std::cout << config["sensors"].as<std::string>() << std::endl;
  std::cout << config["fan-pin"].as<int>() << std::endl;

  return 0;
}
