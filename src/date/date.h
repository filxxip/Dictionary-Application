#pragma once

#include "date_config.h"
#include "time_delta.h"

#include <QDebug>

#include <map>

/** The Date class which represents specific date in past.*/
class Date {
private:
  int second;               ///< date number of seconds
  int minute;               ///< date number of minute
  int hour;                 ///< date number of hour
  int day;                  ///< date number of day
  DateConfig::Months month; ///< enum type of month
  int year;                 ///< date number of year

public:
  /**
   * @brief Date constructor method
   * @param second_ number of second
   * @param minute_ number of minute
   * @param hour_ number of hour
   * @param day_ numbr of day
   * @param month_ number of month
   * @param year_ number of year
   */
  Date(int second_, int minute_, int hour_, int day_, int month_, int year_);

  /**
   * @brief get_difference method which count difference beetween two dates
   * @param date2 second date to compare
   * @return TimeDelta class instance which specified the diffrence
   */
  TimeDelta get_difference(const Date &date2) const;

  /**
   * @brief operator < which compare two dates
   * @param date date needed to compare
   * @return true if first date is earlier, otherwise false
   */
  bool operator<(const Date &date);

  /**
   * @brief operator == which compare two dates
   * @param date date needed to compare
   * @return true if dates are equal, otherwise false
   */
  bool operator==(const Date &date);

  /**
   * @brief operator > which compare two dates
   * @param date date needed to compare
   * @return true if first date is newer, otherwise false
   */
  bool operator>(const Date &date);

  /**
   * @brief to_string method which convert Date to string format type
   * "year>month>day>hour>minute>second"
   * @return the string version of date
   */
  QString to_string() const;
};

/**
 * @brief to_date method which convert string format date to Date class instance
 * @param date string in format "year>month>day>hour>minute>second"
 * @return Date class instance
 */
Date to_date(const QString &date);
