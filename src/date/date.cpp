#include "date.h"
#include "../data/config_file.h"
#include "time_delta.h"

#include <algorithm>
#include <iostream>
#include <numeric>

// namespace

Date::Date(int second_, int minute_, int hour_, int day_, int month_, int year_)
    : second(second_), minute(minute_), hour(hour_), day(day_),
      month(static_cast<DateConfig::Months>(month_)), year(year_) {}

TimeDelta Date::get_difference(const Date &date2) const {
  using namespace Date_Values;
  int years_result = 0;
  int days_result = 0;
  int hours_result = 0;
  int minutes_result = 0;
  int seconds_result = 0;
  DateConfig::Sign sign;
  int sum_of_days =
      std::accumulate(
          DateConfig::MonthDays.begin(), DateConfig::MonthDays.find(month), day,
          [](auto &value1, auto &value2) { return value1 + value2.second; }) -
      std::accumulate(
          DateConfig::MonthDays.begin(),
          DateConfig::MonthDays.find(date2.month), day,
          [](auto &value1, auto &value2) { return value1 + value2.second; });
  int hours_help = year * DAY_YEAR * DAY_HOURS + day * DAY_HOURS + hour -
                   date2.year * DAY_YEAR * DAY_HOURS - date2.day * DAY_HOURS -
                   date2.hour + sum_of_days * DAY_HOURS;
  int seconds_help =
      second + minute * MINUTE_HOUR - date2.second - date2.minute * MINUTE_HOUR;
  int result = hours_help * MINUTE_HOUR * SECOND_MINUTE + seconds_help;
  if (result < 0) {
    sign = DateConfig::Sign::MINUS;
  } else if (result == 0) {
    sign = DateConfig::Sign::NONE;
  } else {
    sign = DateConfig::Sign::PLUS;
  }
  if (result / (MINUTE_HOUR * SECOND_MINUTE * DAY_HOURS * DAY_YEAR) != 0) {
    years_result =
        result / (MINUTE_HOUR * SECOND_MINUTE * DAY_HOURS * DAY_YEAR);
    result = result % (MINUTE_HOUR * SECOND_MINUTE * DAY_HOURS * DAY_YEAR);
  }
  if (result / (MINUTE_HOUR * SECOND_MINUTE * DAY_HOURS) != 0) {
    days_result = result / (MINUTE_HOUR * SECOND_MINUTE * DAY_HOURS);
    result = result % (MINUTE_HOUR * SECOND_MINUTE * DAY_HOURS);
  }
  if (result / MINUTE_HOUR * SECOND_MINUTE != 0) {
    hours_result = result / MINUTE_HOUR * SECOND_MINUTE;
    result = result % MINUTE_HOUR * SECOND_MINUTE;
  }
  if (result / SECOND_MINUTE != 0) {
    minutes_result = result / SECOND_MINUTE;
    result = result % SECOND_MINUTE;
  }
  seconds_result = result;
  return TimeDelta(sign, std::abs(seconds_result), std::abs(minutes_result),
                   std::abs(hours_result), std::abs(days_result),
                   std::abs(years_result));
}

bool Date::operator<(const Date &date) {
  return get_difference(date).sign == DateConfig::Sign::MINUS;
}

bool Date::operator==(const Date &date) {
  return get_difference(date).sign == DateConfig::Sign::NONE;
}

bool Date::operator>(const Date &date) {
  return get_difference(date).sign == DateConfig::Sign::PLUS;
}

QString Date::to_string() const {
  QString result = QString::number(year) + ">" +
                   QString::number(static_cast<int>(month)) + ">" +
                   QString::number(day) + ">" + QString::number(hour) + ">" +
                   QString::number(minute) + ">" + QString::number(second);
  return result;
}

Date to_date(const QString &date) {
  std::vector<QString> date_elements;
  auto date_helper = date.toStdString();
  auto begin = date_helper.begin();
  auto end = date_helper.end();
  while (true) {

    auto new_end = std::find(begin, end, '>');
    auto element_helper = std::string(begin, new_end);
    auto element = QString::fromStdString(element_helper);
    date_elements.push_back(element);
    begin = new_end;
    if (begin == end) {
      break;
    }
    begin = std::next(begin);
  }
  int year = date_elements.at(0).toInt();
  int month = date_elements.at(1).toInt();
  int day = date_elements.at(2).toInt();
  int hour = date_elements.at(3).toInt();
  int minute = date_elements.at(4).toInt();
  int second = date_elements.at(5).toInt();
  return Date(second, minute, hour, day, month, year);
}
