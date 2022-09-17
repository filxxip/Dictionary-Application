#include "time_delta.h"

TimeDelta::TimeDelta(DateConfig::Sign sign_, int seconds_, int minutes_,
                     int hours_, int days_, int years_)
    : sign(sign_), seconds(seconds_), minutes(minutes_), hours(hours_),
      days(days_), years(years_) {}

QString TimeDelta::get_friend_format() {
  QString str = QString::number(years) + " years, " + QString::number(days) +
                " days, " + QString::number(hours) + " hours, " +
                QString::number(minutes) + " minutes, " +
                QString::number(seconds) + " seconds, ";
  return str;
}
