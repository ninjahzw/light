#include "LocalLRUCache.h"
#include "Util.h"
#include "Constants.h"
#include <chrono>
#include <glog/logging.h>

namespace light{

using namespace std;

void LocalLRUCache::set(const string& key,
					    const string& value,
						const int64_t& ttl){
  auto value_it = local_cache_.find(key);
  // if key already exists
  // then insert nothing in map but set it to head of the list
  if (value_it != local_cache_.end()){
	auto& entry = value_it->second;
	removeEntry(&entry);
	setHead(&entry);
	return;
  }

  CacheEntry entry {key, value};
  // if the cache is full
  if (size_ >= capacity_){
	if (nullptr != tail_){
	  LOG(INFO) << tail_->key << " will be removed.";
	  // NOTE, the following line will give seg fault in 
	  // this posision, still do not know why
	  // -- local_cache_.erase(key_remove);
	  // alternative way:
	  auto& key_remove = tail_->key;
	  removeEntry(tail_); 
	  local_cache_.erase(key_remove);
	  setHead(&entry);
  	  // set value to cahce
  	  local_cache_.insert(pair<string, CacheEntry>(key, entry));
	  return;
	}
  }

  setHead(&entry);
  // set value to cahce
  local_cache_.insert(pair<string, CacheEntry>(key, entry));
  size_ ++;
}

string LocalLRUCache::get(const string& key) {
  auto&& kv = local_cache_.find(key);
  if (kv != local_cache_.end()) {
	auto& entry = kv->second;
	removeEntry(&entry);
	setHead(&entry);
    return entry.value;
  }
  // TODO throw exception
  return "";
}

/**
 * NOTE elegant way to remove a node, consider head and tail.
 */
void LocalLRUCache::removeEntry(CacheEntry* entry){
  if (nullptr != entry->prev) {
	entry->prev->next = entry->next;
  } else {
	head_ = entry->next;
  }
  if (nullptr != entry-> next) {
	entry->next->prev = entry->prev;	
  } else {
	tail_ = entry->prev;
  }
}

void LocalLRUCache::setHead(CacheEntry* entry){
  entry->next = head_;
  entry->prev = nullptr;
  if (nullptr != head_){
	head_->prev = entry;
  }
  head_ = entry;
  // initialize tail. NOTE, important!
  if (nullptr == tail_) {
	tail_ = head_;
  }
}

LocalLRUCache::LocalLRUCache(int capacity): capacity_(capacity),
											size_(0),
											head_(nullptr),
											tail_(nullptr){
}
}
