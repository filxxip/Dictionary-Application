#include "regex_check.h"
#include "../data/config_file.h"

#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include <algorithm>
#include <regex>

bool is_email_valid(const QString &email) {
  QRegularExpression exp(Regex::EMAIL_CHECK);
  QRegularExpressionMatch match = exp.match(email);
  return match.hasMatch();
}

bool is_password_valid(const QString &password) {
  auto result =
      std::find_if(password.begin(), password.end(),
                   [](const auto &letter) { return letter.isUpper(); });
  return (result != password.end());
}

bool is_age_valid(const int value) { return value >= 0; }
bool is_age_valid(const QString &age) {
  if (age.toInt() == 0 and age != "0") {
    return false;
  }
  if (age.toInt() < 0) {
    return false;
  }
  return true;
}
bool is_name_valid(const QString &name) { return !name.isEmpty(); }
bool is_surname_valid(const QString &surname) { return !surname.isEmpty(); }
bool is_country_valid(const QString &country) { return !country.isEmpty(); }
bool is_school_valid(const QString &school) { return !school.isEmpty(); }
