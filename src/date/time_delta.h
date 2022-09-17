#pragma once

#include "date_config.h"

#include <QString>

/** The TimeDelta struct which specified difference beetween two dates*/
struct TimeDelta {
  DateConfig::Sign sign; ///< sign which specified if the given dates are in
                         ///< progressive direction or not
  int seconds;           ///< number of seconds
  int minutes;           ///< number of minutes
  int hours;             ///< number of hours
  int days;              ///< number of days
  int years;             ///< number of years
  /**
   * @brief TimeDelta constructor
   * @param sign_ sign which specified if the given dates are in progressive
   * direction or not
   * @param seconds_ number of seconds
   * @param minutes_ number of minutes
   * @param hours_ number of hours
   * @param days_ number of days
   * @param years_ number of years
   */
  TimeDelta(DateConfig::Sign sign_, int seconds_, int minutes_, int hours_,
            int days_, int years_);

  /**
   * @brief get_friend_format method which convert TimeDelta instance to
   * friendly QString format
   * @return string format of Dates diffrence
   */
  QString get_friend_format();
};
