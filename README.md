# light
<p>
A C++ local memory lib and (thrift) service.
Currently implemented "Brutal cache" and LRU cache
Here "Brutal cache" means don't care about the memory occupation, only remove cache that reached ttl which is set up by user.
</p>
<p>
Usage:
To use and a lib:
</p>
```
auto cache_ = CacheFactory::getCache(CacheTypes::BRUTAL_LOCAL_CACHE);
```
To use as a service:
```
Check the client/CppClient.cpp for usecase.
```
