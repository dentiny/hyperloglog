#include "hyperloglog.h"

#include <cassert>
#include <iostream>
#include <string>

namespace ghost {

void BasicTest() {
  constexpr uint16_t kHllBitNum = 3;
  HyperLogLog<std::string> hyper_log_log{kHllBitNum};
  hyper_log_log.AddElem("hello");
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;

  hyper_log_log.AddElem("world");
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;

  hyper_log_log.AddElem("dentiny");
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;

  hyper_log_log.AddElem("database");
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;

  hyper_log_log.AddElem("hyperloglog");
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;

  for (char c = 'a'; c <= 'z'; ++c) {
    std::string s;
    s += c;
    hyper_log_log.AddElem(s);
  }
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;

  for (char c = 'A'; c <= 'Z'; ++c) {
    std::string s;
    s += c;
    hyper_log_log.AddElem(s);
  }
  std::clog << "Estimated cardinality is " << hyper_log_log.ComputeCardinality() << std::endl;
} 

}  // namespace ghost

int main() {
  ghost::BasicTest();
  return 0;
}
