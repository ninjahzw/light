#include "LocalCache.h"
#include "Util.h"
#include "Constants.h"
#include <chrono>
#include <glog/logging.h>

namespace light{

using namespace std;

std::shared_ptr<LocalCache> LocalCache::localcache_obj_ = NULL;

void LocalCache::set(const string& key,
					 const string& value,
					 const int64_t& ttl){
  // set value to cahce
  local_cache_.insert(pair<string, string>(key, value));
  
  // set timmer
  auto&& expire = getNowSeconds() + ttl;
  local_cache_timer_.insert(pair<string, int64_t>(key, expire));
}

string LocalCache::get(const string& key) {
  auto&& kv = local_cache_.find(key);
  if (kv != local_cache_.end()) {
    return kv->second;
  }
  // TODO throw exception
  return "";
}

std::shared_ptr<LocalCache> LocalCache::getInstance(){
  if (localcache_obj_ == NULL){
	// If use make_shared, have to make the constructor public.
	localcache_obj_ = std::shared_ptr<LocalCache>(new LocalCache());
  }
  return localcache_obj_;
}

void LocalCache::invalidate() {
  while (invalidation_check_) {
	// If needed to delete items while iterating
	// can not use (auto& kv : map)
	// because the iterator pointer need to be operated.
	auto itr = local_cache_timer_.begin();
	while (itr != local_cache_timer_.end()) {
	  auto cache_key = itr -> first;
	  auto timeout = itr -> second;
	  // remove timeout data from cache.
	  if (timeout <= getNowSeconds()) {
		if (local_cache_.erase(cache_key) >= 1) {
		  // increment pointer before delete.
		  itr ++;
		  local_cache_timer_.erase(cache_key);	
		  LOG(INFO) << "cache key " << cache_key << " removed";
		}
	  } else {
		itr ++;
	  }
	} 
	// sleep for a while
	std::this_thread::sleep_for(
		std::chrono::milliseconds(Constants::local_cache_check_sleep));
  }
}

LocalCache::LocalCache(): invalidation_check_(true){
  cache_check_thread_ = std::thread([this] {
    LOG(INFO) << "Start local cache invalidation thread";
    invalidate();
    LOG(INFO) << "Local cache invalidation thread stopped!";
  });
}
}