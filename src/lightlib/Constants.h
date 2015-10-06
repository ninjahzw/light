#pragma once
namespace light {

class Constants{
 public:
  /**
   * settings for LocalCache class
   * the check thread sleeps in milliseconds.
   */
  static int LOCAL_CACHE_CHECK_SLEEP;

  /**
   * number of working threads for this service (global)
   */
  static int NUM_WORK_THREADS;

  /**
   * LRU cache capacity
   */
  static int LRU_CAPACITY;
};
}
