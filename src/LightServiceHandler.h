#pragma once

#include "../gen-cpp/LightService.h"

namespace light {

class LightServiceHandler : public LightServiceIf {
 public:
  LightServiceHandler();

  void ping() override;

  /**
   * Add a key value pair
   * @param addArgs: AddArgs object, key, value are required
   * ttl is optimal, default value is defined in thrift file.
   */
  void add (const AddArgs& addArgs) override;

  /**
   * Get a value by key
   * @param the key
   * @return the value corresponding to the key.
   */
  void get(std::string& return_, const std::string& key) override;
};
}
