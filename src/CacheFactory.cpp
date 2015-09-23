#include "CacheFactory.h"
#include "LocalBrutalCache.h"
#include "LocalLRUCache.h"
#include "Constants.h"

namespace light {

std::shared_ptr<ILocalCache> CacheFactory::brutal_cache_ = NULL;

std::shared_ptr<ILocalCache> CacheFactory::lru_cache_ = NULL;

std::shared_ptr<ILocalCache> CacheFactory::getCache(CacheTypes types){
  switch (types){
    case CacheTypes::BRUTAL_LOCAL_CACHE:
	  if (CacheFactory::brutal_cache_ == NULL){
		CacheFactory::brutal_cache_ = std::shared_ptr<LocalBrutalCache>(
			new LocalBrutalCache());
	  }
	  return CacheFactory::brutal_cache_;
	case CacheTypes::LRU_LOCAL_CACHE:
	  if (CacheFactory::lru_cache_ == NULL){
		CacheFactory::lru_cache_ = std::shared_ptr<LocalLRUCache>(
			new LocalLRUCache(Constants::LRU_CAPACITY));
	  }
	  return CacheFactory::lru_cache_;
  } 
  // the types has to be in enum.
  throw CacheTypeNodeFoundException();
}
}

