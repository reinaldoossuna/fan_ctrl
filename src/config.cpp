#include "../include/config.h"
#include <vector>

namespace fan {

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

  levels_.emplace_back(std::move(level));
  return true;
}

std::vector<std::unique_ptr<Level>>* Config::levels() {
  return &levels_;
}
}  // namespace fan
