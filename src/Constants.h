#pragma once
namespace light {

class Constants{
 public:
  /**
   * settings for LocalCache class
   * the check thread sleeps in milliseconds.
   */
  static int local_cache_check_sleep;

  /**
   * number of working threads for this service (global)
   */
  static int num_work_threads;
};
}
