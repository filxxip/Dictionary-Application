#pragma once

#include "../data/config_file.h"
#include "../person/person.h"
#include "regex_check.h"

#include <QString>

#include <functional>
#include <map>

/**
 * @brief check_email method which checks if email is in suitable format
 * @param email email to check
 * @return true if email is right, otherwise false
 */
bool is_email_valid(const QString &email);

/**
 * @brief check_password method which checks if password is in suitable format
 * @param email password to check
 * @return true if password is right, otherwise false
 */
bool is_password_valid(const QString &password);

/**
 * @brief is_age_valid method which checks if age is suitable
 * @param value value of age
 * @return true if age is not a negative number, otherwise false
 */
bool is_age_valid(const int value);

/**
 * @brief is_age_valid method which checks if age is suitable
 * @param age value of age
 * @return true if age can be chaged not to a negative number, otherwise false
 */
bool is_age_valid(const QString &age);

/**
 * @brief is_name_valid method which checks if name is suitable
 * @param name value of name
 * @return true if name isnt empty, otherwise false
 */
bool is_name_valid(const QString &name);

/**
 * @brief is_surname_valid method which checks if name is suitable
 * @param surname value of surname
 * @return true if surname is not empty, otherwise false
 */
bool is_surname_valid(const QString &surname);

/**
 * @brief is_country_valid method which checks if country is suitable
 * @param country value of country
 * @return true if country is not empty, otherwise false
 */
bool is_country_valid(const QString &country);

/**
 * @brief is_school_valid method which checks if school is suitable
 * @param name value of name
 * @return true if school is not empty, otherwise false
 */
bool is_school_valid(const QString &name);

namespace FunctionCheck {

using func = std::function<bool(const QString &)>;

const std::map<Person::Data, func> items{
    {Person::Data::NAME, is_name_valid},
    {Person::Data::SURNAME, is_surname_valid},
    {Person::Data::COUNTRY, is_country_valid},
    {Person::Data::PASSWORD, is_password_valid},
    {Person::Data::SCHOOL, is_school_valid},
    {Person::Data::EMAIL, is_email_valid},
    {Person::Data::AGE, static_cast<bool (*)(const QString &)>(is_age_valid)}};
} // namespace FunctionCheck
