#include <glog/logging.h>
#include <gtest/gtest.h>
#include <unistd.h>
#include <boost/any.hpp>
#include "../lightlib/CacheFactory.h"
#include "../lightlib/ILocalCache.h"
#include "../lightlib/Util.h"

using namespace std;
using namespace light;

class BrutalTest: public ::testing::Test{
 protected:
  BrutalTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(BrutalTest, set_get) {
  auto cache_ = CacheFactory::getCache(CacheTypes::BRUTAL_LOCAL_CACHE);
  string key{"1"};
  string value{"1"};
  cache_ -> set(key, value);
  EXPECT_EQ(boost::any_cast<string>(cache_ -> get("1")), "1");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
