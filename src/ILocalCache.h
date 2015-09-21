#pragma once
#include <string>

namespace light {
class ILocalCache{
 public:
  virtual ~ILocalCache(){}

  virtual void set(const std::string& key,
				   const std::string& value,
				   const int64_t& ttl) = 0;

  virtual std::string get(const std::string& key) = 0;
};
}
