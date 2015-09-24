#include <glog/logging.h>
#include <gtest/gtest.h>
#include "../CacheFactory.h"
#include "../Util.h"

using namespace std;
using namespace light;

class BrutalTest: public ::testing::Test{
 protected:
  BrutalTest() {}

  virtual void SetUp() {}

  virtual void TearDown() {}
};

TEST_F(BrutalTest, set_get) {
  auto cache = CacheFactory::getCache(CacheTypes::BRUTAL_LOCAL_CACHE);
  cache -> set("1", "1");
  EXPECT_EQ(cache -> get("1"), "1");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
