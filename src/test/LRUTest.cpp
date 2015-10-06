#include <glog/logging.h>
#include <gtest/gtest.h>
#include "../lightlib/CacheFactory.h"
#include "../lightlib/Util.h"

using namespace std;
using namespace light;

class LRUTest: public ::testing::Test{
 protected:
  LRUTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(LRUTest, set_get) {
  auto cache = CacheFactory::getCache(CacheTypes::LRU_LOCAL_CACHE);
  string key{"1"};
  string value{"1"};
  cache -> set(key, value);
  EXPECT_EQ(boost::any_cast<string>(cache -> get("1")), "1");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
