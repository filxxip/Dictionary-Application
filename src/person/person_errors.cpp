#include "person_errors.h"

MyException::MyException(Types type) : val(type) {}

MyException::Types MyException::what() { return val; }
