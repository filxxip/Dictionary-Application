#pragma once

#include <exception>

class MyException : public std::exception {
public:
  enum class Types { NAME, AGE, SURNAME, EMAIL, PASSWORD, COUNTRY, SCHOOL };

private:
  Types val;

public:
  MyException(Types type);
  Types what();
};
