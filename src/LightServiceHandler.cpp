#include "LightServiceHandler.h"

#include <thrift/server/TThreadedServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TTransportUtils.h>
#include <thrift/TToString.h>

#include "LocalCache.h"
#include "Util.h"

namespace light {

using namespace std;
using namespace apache::thrift;

LightServiceHandler::LightServiceHandler() {}

void LightServiceHandler::ping() { cout << "ping()" << endl; }

void LightServiceHandler::add(const AddArgs& addArgs) {
  if (!checkArgs(addArgs)){
	throwException(InvalidArgsException(), 1,
		"invalid argument");
  }
  auto lc = LocalCache::getInstance(); 
  lc-> set(addArgs.key, addArgs.value, addArgs.ttl);
}

void LightServiceHandler::get(std::string& return_,
							  const string& key){

  auto lc = LocalCache::getInstance(); 
  return_ = lc-> get(key);
}
}
