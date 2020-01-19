#pragma once

#include <vector>
#include <memory>
#include <string>

namespace fan {

class Level {
 protected:
  int level_;
  std::vector<int> lower_limit_;
  std::vector<int> upper_limit_;

 public:
  Level(int level, const std::vector<int>& lower_limit, const std::vector<int>& upper_limit);
  Level(int level, int lower_limit, int upper_limit);
  virtual bool up() const = 0;
  virtual bool down() const = 0;

  std::vector<int> upper_limit() const;
  std::vector<int> lower_limit() const;
};

class SimpleLevel : public Level {
 public:
  SimpleLevel(int level, int lower_limit, int upper_limit);

  bool up() const override;
  bool down() const override;
};

class Config {
 public:
  Config();
  // Not trivially copyable
  Config(const Config& ) = delete;
  ~Config();
  static const Config* read_config(const std::string& filename);


  bool add_level(std::unique_ptr<Level>&& level);
  std::vector<std::unique_ptr<Level>>* levels() ;


 private:
  std::vector<std::unique_ptr<Level>> levels_;
  unsigned int num_temps_;
};


}
