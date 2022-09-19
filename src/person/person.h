#pragma once

#include <QString>

/** Person class which implements the owner of dictionary*/
class Person {
  QString name;     ///< name of this person
  QString surname;  ///< surname of this person
  int age;          ///< age of this person
  QString school;   ///< school for which this person attends
  QString country;  ///< country where this person lives
  QString email;    ///< email of person
  QString password; ///< password of person

public:
  enum class Data {
    NAME,
    SURNAME,
    AGE,
    COUNTRY,
    SCHOOL,
    EMAIL,
    PASSWORD,
  }; ///< Enumerate class which specifies data of person
  /**
   * @brief Person default constructor
   */
  Person();

  /**
   * @brief Person constructor
   * @param name_ name of person
   * @param surname_ surname of person
   * @param age_ age of person
   * @param school_ school where this person studies
   * @param country_ country where this person lives
   * @param email_ email of person used to log into account
   * @param password_ password of person used to log into account
   */
  Person(QString name_, QString surname_, int age_, QString school_,
         QString country_, QString email_, QString password_);

  /**
   * @brief get_data method which provides data of person
   * @param data_name enum sign of needed data
   * @return reference to QString instance
   */
  const QString get_data(Data data_name) const;

  /**
   * @brief set_data method which sets new data of person
   * @param data new data of given atrribute
   * @param data_name sign of attribute which should be changed
   */
  void set_data(const QString &data, Data data_name);

  /**
   * @brief get_password method which provides the password of person
   * @return password of person
   */
  const QString &get_password() const;

  /**
   * @brief get_email method which provides the email of person
   * @return email of person
   */
  const QString &get_email() const;

  /**
   * @brief get_name method which provides the name of person
   * @return name of person
   */
  const QString &get_name() const;

  /**
   * @brief get_name method which provides the surname of person
   * @return surname of person
   */
  const QString &get_surname() const;

  /**
   * @brief get_name method which provides the fullname of person
   * @return fullname of person
   */
  QString get_fullname() const;

  /**
   * @brief get_name method which provides the school of person
   * @return school of this person
   */
  const QString &get_school() const;

  /**
   * @brief get_name method which provides the country of person
   * @return country where this person lives
   */
  const QString &get_country() const;

  /**
   * @brief get_age method which provides the age of person
   * @return the age of this person
   */
  int get_age() const;

  /**
   * @brief set_name set new name of person
   * @param new_name new name of person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_name(const QString &new_name);

  /**
   * @brief set_surname set new surname of person
   * @param new_surname new surname of person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_surname(const QString &new_surname);

  /**
   * @brief set_age set new age of person
   * @param new_age new age of person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_age(const int new_age);
  /**
   * @brief set_age set new age of person
   * @param new_age new age of person in qstring format
   * @return true if setting new value is successful, otherwise false
   */
  bool set_age(const QString &new_age);

  /**
   * @brief set_school set new school
   * @param new_school new school of this person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_school(const QString &new_school);

  /**
   * @brief set_country set new country
   * @param new_country new country of this person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_country(const QString &new_country);

  /**
   * @brief set_email set new email
   * @param new_email new email of this person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_email(const QString &new_email);

  /**
   * @brief set_password set new password
   * @param new_password new password of this person
   * @return true if setting new value is successful, otherwise false
   */
  bool set_password(const QString &new_password);

  /**
   * @brief operator == method which determines if two person are the same
   * instance
   * @param person person instance to compare
   * @return true if person are the same instances (deducing by emails),
   * otherwise false
   */
  bool operator==(const Person &person);

  /**
   * @brief is_valid_data method which checks if some data is correct
   * @param data new data of given atrribute
   * @param data_name sign of attribute which should be changed
   * @return true if data is valid, otherwise false
   */
  bool is_valid_data(const QString &data, Person::Data data_name) const;
};
