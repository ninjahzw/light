#include <iostream>

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/LightService.h"

using namespace std;
using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

int main(int argc, char *argv[]) {

  if (argc < 2){
	cout << "Please provide key" << endl;
	return 0;
  }

  boost::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
  boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
  boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
  LightServiceClient client (protocol);

  auto& key = argv[1];

  try {
    transport->open();
	AddArgs addArgs;
	addArgs.key = key;
	addArgs.value = "2";

    client.add(addArgs);

	string value;
	client.get(value, key);
	cout << "added value is : " << value << endl;

    transport->close();
  } catch (TException& tx) {
    cout << "ERROR: " << tx.what() << endl;
  }
}
