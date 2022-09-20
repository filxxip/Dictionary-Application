#include "person.h"
#include "../regex_check/regex_check.h"

#include <QDebug>

#include <stdexcept>

Person::Person() {}

Person::Person(QString name_, QString surname_, int age_, QString school_,
               QString country_, QString email_, QString password_) {
  set_name(name_);
  set_surname(surname_);
  set_age(age_);
  set_school(school_);
  set_country(country_);
  set_email(email_);
  set_password(password_);
}

const QString &Person::get_name() const { return name; }

const QString &Person::get_surname() const { return surname; }

QString Person::get_fullname() const { return name + " " + surname; }

const QString &Person::get_school() const { return school; }

const QString &Person::get_country() const { return country; }

const QString &Person::get_email() const { return email; }

const QString &Person::get_password() const { return password; }

int Person::get_age() const { return age; }

bool Person::set_name(const QString &new_name) {
  if (is_name_valid(new_name)) {
    name = new_name;
    name[0] = name[0].toUpper();
    return true;
  }
  return false;
}

bool Person::set_surname(const QString &new_surname) {
  if (is_surname_valid(new_surname)) {
    surname = new_surname;
    surname[0] = surname[0].toUpper();
    return true;
  }
  return false;
}

bool Person::set_age(const int new_age) {
  if (is_age_valid(new_age)) {
    age = new_age;
    return true;
  }
  return false;
}
bool Person::set_age(const QString &new_age) {
  if (is_age_valid(new_age)) {
    age = new_age.toInt();
    return true;
  }
  return false;
}

bool Person::set_school(const QString &new_school) {
  if (is_school_valid(new_school)) {
    school = new_school;
    return true;
  }
  return false;
}

bool Person::set_country(const QString &new_country) {
  if (is_country_valid(new_country)) {
    country = new_country;
    country[0] = country[0].toUpper();
    return true;
  }
  return false;
}

bool Person::set_email(const QString &new_email) {
  if (is_email_valid(new_email)) {
    email = new_email;
    return true;
  }
  return false;
}

bool Person::set_password(const QString &new_password) {
  if (is_password_valid(new_password)) {
    password = new_password;
    return true;
  }
  return false;
}

bool Person::operator==(const Person &person) { return email == person.email; }

const QString Person::get_data(Person::Data data_name) const {
  switch (data_name) {
  case Person::Data::NAME: {
    return get_name();
  }
  case Person::Data::SURNAME: {
    return get_surname();
  }
  case Person::Data::AGE: {
    return QString::number(get_age());
  }
  case Person::Data::EMAIL: {
    return get_email();
  }
  case Person::Data::PASSWORD: {
    return get_password();
  }
  case Person::Data::COUNTRY: {
    return get_country();
  }
  case Person::Data::SCHOOL: {
    return get_school();
  }
  default:
    return "";
  }
}

void Person::set_data(const QString &data, Person::Data data_name) {
  switch (data_name) {
  case Person::Data::NAME: {
    set_name(data);
    break;
  }
  case Person::Data::SURNAME: {
    set_surname(data);
    break;
  }
  case Person::Data::AGE: {
    set_age(data);
    break;
  }
  case Person::Data::EMAIL: {
    set_email(data);
    break;
  }
  case Person::Data::PASSWORD: {
    set_password(data);
    break;
  }
  case Person::Data::COUNTRY: {
    set_country(data);
    break;
  }
  case Person::Data::SCHOOL: {
    set_school(data);
    break;
  }
  }
}

bool Person::is_valid_data(const QString &data, Person::Data data_name) const {
  return FunctionCheck::items.at(data_name)(data);
}
