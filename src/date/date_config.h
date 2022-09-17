#pragma once

#include <unordered_map>

namespace DateConfig {
enum class Months {
  JANUARY = 1,
  FEBRUARY = 2,
  MARCH = 3,
  APRIL = 4,
  MAY = 5,
  JUNE = 6,
  JULY = 7,
  AUGUST = 8,
  SEPTEMBER = 9,
  OCTOBER = 10,
  NOVEMBER = 11,
  DECEMBER = 12
};

enum class Sign { PLUS, MINUS, NONE };

const std::unordered_map<Months, int> MonthDays{
    {Months::JANUARY, 31}, {Months::FEBRUARY, 28}, {Months::MARCH, 31},
    {Months::APRIL, 30},   {Months::MAY, 31},      {Months::JUNE, 30},
    {Months::JULY, 31},    {Months::AUGUST, 31},   {Months::SEPTEMBER, 30},
    {Months::OCTOBER, 31}, {Months::NOVEMBER, 30}, {Months::DECEMBER, 31}};

} // namespace DateConfig
