#pragma once

#include <QString>

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
bool is_age_valid(const QString &age);
bool is_name_valid(const QString &name);
bool is_surname_valid(const QString &surname);
bool is_country_valid(const QString &country);
bool is_school_valid(const QString &name);
