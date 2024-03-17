#ifndef LASER_ARGS_PARSER
#define LASER_ARGS_PARSER

#include <iostream>
#include <string>
#include <unordered_map>

namespace laser::args {

class ArgumentParser {
  // ===========================================================================
  // Constructors
  // ===========================================================================
 public:
  ArgumentParser() {}

 public:
  // ===========================================================================
  // Methods
  // ===========================================================================
 public:
  void add_arg(const std::string& name) { args.insert_or_assign(name, ""); }

  void parse_args(int argc, char** argv) {
    char* key;
    for (int i = 1; i < argc; i++) {
      if (i % 2 == 1)
        key = argv[i];
      else
        args.insert_or_assign(std::string(key), argv[i]);
    }
  }

  template <typename T>
  T get(const std::string& key, T default_value) const;

  void display_args() const {
    auto it = args.begin();
    while (it != args.end()) {
      std::cout << "Arg " << it->first << " -> " << it->second << std::endl;
      it++;
    }
  }

 private:
  bool has_value_for(const std::string& key) const;

  // ===========================================================================
  // Members
  // ===========================================================================
 private:
  std::unordered_map<std::string, std::string> args;
};

}  // namespace laser::args

#endif