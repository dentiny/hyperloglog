// Implementation for hyperloglog for cadinatility estimation.
//
// `HyperLogLog` is a templated class to support different types of keys.
// It's not thread-safe, so should be wrapped with mutex at concurrent usage.

#pragma once

#include <bitset>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <vector>

namespace ghost {

template <typename T>
class HyperLogLog {
 public:
  explicit HyperLogLog(uint16_t n_bits)
    : num_of_bits_(n_bits),
      constant_(GetConstant(n_bits)) {
    buckets_ = std::vector<uint8_t>(1 << num_of_bits_, 0);
  }

  void AddElem(const T& val) {
    const uint64_t hash_val = hasher_(val);
    const auto bset = std::bitset<64>(hash_val);
    const size_t bkt_idx = GetIndexOfBucket(bset);
    const uint8_t zero_count = PositionOfLeftmostOne(bset);
    buckets_[bkt_idx] = std::max(buckets_[bkt_idx], zero_count);
  }

  size_t ComputeCardinality() const {
    double sum = 0;
    for (size_t bkt_val : buckets_) {
      sum += 1.0 / (1ULL << bkt_val);
    }
    size_t cardinality = constant_ * buckets_.size() * buckets_.size() / sum;
    return cardinality;
  }

 private:
  // Get constant value for cardinality estimation.
  double GetConstant(uint16_t num_of_bits) const {
    return 0.7213 / (1 + 1.079 / num_of_bits);
  }

  uint64_t PositionOfLeftmostOne(const std::bitset<64> &bset) const {
    for (size_t idx = num_of_bits_; idx < 64; ++idx) {
      if (bset[64 - 1 - idx]) {
        return idx + 1 - num_of_bits_;
      }
    }
    return 64 - num_of_bits_;
  }

  size_t GetIndexOfBucket(const std::bitset<64>& bset) const {
    // Read first [num_of_bits_] bits to decide index.
    size_t bucket_index = 0;
    for (int64_t idx = 0; idx < num_of_bits_; ++idx) {
      bucket_index = bucket_index * 2 + static_cast<size_t>(bset[63 - idx]);
    }
    return bucket_index;
  }

  // Hasher to get hash value.
  std::hash<T> hasher_{};
  // Number of bits, used to decide bucket count and bucket index.
  uint16_t num_of_bits_;
  // Used to estimate cardinality.
  double constant_;
  // Buckets for counters.
  std::vector<uint8_t> buckets_;
};

}  // namespace ghost
