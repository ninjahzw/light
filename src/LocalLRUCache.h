#pragma once
#include <string>
#include <list>
#include <memory>
#include <thread>
#include <unordered_map>
#include <boost/any.hpp>
#include "ILocalCache.h"

namespace light {

class CacheEntry {
 public:
  std::string key;
  std::string value;
  CacheEntry* prev;
  CacheEntry* next;
  CacheEntry(std::string key, std::string value): key(key),
												  value(value),
												  prev(nullptr),
												  next(nullptr){}
};

class LocalLRUCache: public ILocalCache {
 public:
  LocalLRUCache(int capacity); 
  /**
   * ttl is ignored here.	
   */
  void set(const std::string& key,
		   const std::string& value,
		   const int64_t& ttl) override;

  std::string get(const std::string& key) override;

 private:
  void removeEntry(CacheEntry* entry);
  void setHead(CacheEntry* entry);
  /**
   * the object that stors local cache data
   */
  std::unordered_map<std::string, CacheEntry> local_cache_{};
  /**
   * capacity of the lru cache.
   */
  int capacity_;
  /**
   * current size.
   */
  int size_;
  /**
   * the head node 
   */
  CacheEntry* head_;
  /**
   * the tail node 
   */
  CacheEntry* tail_;
}; 
}
