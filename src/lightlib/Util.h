#pragma once
namespace light{

enum CacheTypes{
  BRUTAL_LOCAL_CACHE,
  LRU_LOCAL_CACHE,
};

long getNowSeconds();
}
