#pragma once
#include <string>
#include <memory>
#include <thread>
#include <unordered_map>
#include <boost/any.hpp>
#include "ILocalCache.h"

namespace light {

class LocalBrutalCache: public ILocalCache {
 public:
  /**
   * Constructor
   * NOTE: have to explicitely write this default constructor
   * out because (in cpp file) will use this to initialize 
   * some variables.
   */
  LocalBrutalCache();
  /**
   * Get the LocalBrutalCache instance
   * @return the LocalBrutalCache singleton instance
   */
  static std::shared_ptr<LocalBrutalCache> getInstance();

  void set(const std::string& key,
		   const std::string& value,
		   const int64_t& ttl = 30) override;

  std::string get(const std::string& key) override;

  void invalidate();

 private:
  /**
   * the object that stors local cache data
   */
  std::unordered_map<std::string, std::string> local_cache_{};

  std::unordered_map<std::string, int64_t> local_cache_timer_{};

  /**
   * The thread for cache invalidation.
   */
  std::thread cache_check_thread_;

  bool invalidation_check_;
}; 
}
