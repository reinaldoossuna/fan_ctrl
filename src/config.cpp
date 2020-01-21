#include <vector>
#include <iostream>
#include <string>

#include "../include/config.h"
#include "yaml-cpp/yaml.h"

namespace fan {

Config* Config::read_config(const std::string& filename) {
  Config* c = nullptr;
  YAML::Node file = YAML::LoadFile(filename);

  try {
    auto sensors = file["sensors"];
    c->add_sensor(sensors.as<std::string>());
    auto fan = file["fan-pin"];
    c->add_fan(fan.as<int>());
    /*
    const YAML::Node& levels = file["levels"];
    for (YAML::const_iterator it = levels.begin();
        it != levels.end();
        ++it) {
      const auto level = *it;
      auto level_vector = level.as<std::vector<int>>();
      std::unique_ptr<SimpleLevel> l(new SimpleLevel(level_vector[0], level_vector[1], level_vector[2]));
      c->add_level(std::move(l));
    }
      */
  } catch (YAML::BadConversion &e){
    std::cout << "Bad Config file" << std::endl;
  }

  /*
  const YAML::Node& levels = config["levels"];

    auto v = level.as<std::vector<int>>();
  */
  return c;
}

bool Config::add_fan(int pin) {
  // TODO
  std::cout << pin << std::endl;
  return true;
}

bool Config::add_sensor(const std::string& p) {
  // TODO
  std::cout << p << std::endl;
  return true;
}

Level::Level(int level, int lower_limit, int upper_limit)
    : Level(level,
            std::vector<int>(1, lower_limit),
            std::vector<int>(1, upper_limit))
{}

Level::Level(int level, const std::vector<int>& lower_limit, const std::vector<int>& upper_limit)
    : level_(level),
        lower_limit_(lower_limit),
        upper_limit_(upper_limit)
{}

std::vector<int> Level::upper_limit() const {
    return upper_limit_;
}
std::vector<int> Level::lower_limit() const {
    return lower_limit_;
}

SimpleLevel::SimpleLevel(int level, int lower_limit, int upper_limit)
    : Level(level, lower_limit, upper_limit)
{}

bool SimpleLevel::up() const {
  // TODO(reinaldo):
  // 40 it's place holder
  // You need to read the atual temp
    return 40 >= upper_limit().front();
}

bool SimpleLevel::down() const {
    return 40 < lower_limit().front();
}

Config::Config(): num_temps_(0) {}

const Config* read_config(const std::string& filename) {
  // TODO(reinaldo)

  const Config *rv =  nullptr;
  return rv;
}

Config::~Config() {
  levels_.clear();
}

bool Config::add_level(std::unique_ptr<Level>&& level) {
  if (!level)
    return false;

  levels_.push_back(level.release());
  return true;
}

std::vector<Level *>* Config::levels() {
  return &levels_;
}

}  // namespace fan
