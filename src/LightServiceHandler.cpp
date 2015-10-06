#include "LightServiceHandler.h"

#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include "lightlib/CacheFactory.h"
#include "UtilServ.h"

namespace light {
namespace service {

using namespace std;
using namespace apache::thrift;

LightServiceHandler::LightServiceHandler() {}

void LightServiceHandler::ping() { cout << "ping()" << endl; }

void LightServiceHandler::add(const AddArgs &addArgs) {
  if (!checkArgs(addArgs)) {
    throwException(InvalidArgsException(), 1, "invalid argument");
  }
  auto lc = CacheFactory::getCache(light::CacheTypes::LRU_LOCAL_CACHE);
  lc->set(addArgs.key, addArgs.value, addArgs.ttl);
}

void LightServiceHandler::get(std::string &return_, const string &key) {

  auto lc = CacheFactory::getCache(light::CacheTypes::LRU_LOCAL_CACHE);
  return_ = boost::any_cast<string>(lc->get(key));
}
}
}
