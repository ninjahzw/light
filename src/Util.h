#pragma once
#include "../gen-cpp/LightService.h"
namespace light{

enum CacheTypes{
  BRUTAL_LOCAL_CACHE,
  LRU_LOCAL_CACHE,
};

long getNowSeconds();

bool checkArgs(const AddArgs& addArgs);

template<typename T>
void throwException(T&& e,
					const int64_t& errorCode,
					const std::string& message){

  e.errorCode = errorCode;
  e.message = message;
  throw e;
}
}
