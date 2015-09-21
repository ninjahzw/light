#pragma once
#include "Util.h"
#include "ILocalCache.h"

#include <exception>

namespace light {

class CacheTypeNodeFoundException: public std::exception {
  virtual const char* what() const throw() {
	return "Cache type not found!";	
  }
};

class CacheFactory {
 public:
  /**
   * Get a cash singleton instance.
   * @param types: a enum of cache types defined at Util.h.
   * @return a shared_ptr of the cash instance determined by {types} 
   */
  static std::shared_ptr<ILocalCache> getCache(CacheTypes types);

 private:
  static std::shared_ptr<ILocalCache> brutal_cache_;
  static std::shared_ptr<ILocalCache> lru_cache_;
};
}

