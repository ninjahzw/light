#include <glog/logging.h>
#include <gtest/gtest.h>
#include "../CacheFactory.h"
#include "../Util.h"

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
  cache -> set("1", "1");
  EXPECT_EQ(cache -> get("1"), "1");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
