#include <iostream>
#include <memory>
#include <thread>
#include <unordered_map>
#include <boost/any.hpp>

namespace light {

class LocalCache {
 public:
  /**
   * Get the LocalCache instance
   * @return the LocalCache singleton instance
   */
  static std::shared_ptr<LocalCache> getInstance();

  void set(const std::string& key,
		   const std::string& value,
		   const int64_t& ttl = 30);

  std::string get(const std::string& key);

  void invalidate();

 private:
  /**
   * constructor
   */
  LocalCache();

  static std::shared_ptr<LocalCache> localcache_obj_;

  /**
   * the object that stors local cache data
   */
  std::unordered_map<std::string, std::string> local_cache_;

  std::unordered_map<std::string, int64_t> local_cache_timer_;

  /**
   * The thread for cache invalidation.
   */
  std::thread cache_check_thread_;

  bool invalidation_check_;
}; 
}
