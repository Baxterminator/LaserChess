#include "common/args/parser.hpp"

#include <string>

namespace laser::args {

bool ArgumentParser::has_value_for(const std::string &key) const {
  // If key not in map
  if (auto it = args.find(key); it == args.end()) return false;

  // If value has not been parsed and is ""
  if (args.at(key).length() == 0) return false;

  return true;
}

template <>
double ArgumentParser::get(const std::string &key, double default_value) const {
  if (has_value_for(key)) return std::stod(args.at(key));
  return default_value;
}

template <>
float ArgumentParser::get(const std::string &key, float default_value) const {
  if (has_value_for(key)) return std::stof(args.at(key));
  return default_value;
}

template <>
int ArgumentParser::get(const std::string &key, int default_value) const {
  if (has_value_for(key)) return std::stoi(args.at(key));
  return default_value;
}

template <>
long ArgumentParser::get(const std::string &key, long default_value) const {
  if (has_value_for(key)) return std::stol(args.at(key));
  return default_value;
}

template <>
std::string ArgumentParser::get(const std::string &key, std::string default_value) const {
  if (has_value_for(key)) return std::string(args.at(key));
  return default_value;
}

}  // namespace laser::args