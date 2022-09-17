#include "current_date.h"

Date get_current_date() {
  auto t = std::time(0);
  auto now = std::localtime(&t);
  Date date_now(now->tm_sec, now->tm_min, now->tm_hour, now->tm_mday,
                now->tm_mon + 1, now->tm_year + 1900);
  return date_now;
}
