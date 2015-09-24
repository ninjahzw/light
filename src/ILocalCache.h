#pragma once
#include <string>

namespace light {
class ILocalCache{
 public:
  virtual ~ILocalCache(){}
  /**
   * To put a key value pair to cache.
   * @param key: the key as a string
   * @param value: the value as a string
   * @param ttl: time-to-live in the memory
   * NOTE that ttl is ignored in some cache implementation like LRU cache.
   */
  virtual void set(const std::string& key,
				   const std::string& value,
				   const int64_t& ttl=30) = 0;
  /**
   * To get the value by the key.
   * @param key: the key as a string
   * @return the value as a string
   */
  virtual std::string get(const std::string& key) = 0;
};
}
