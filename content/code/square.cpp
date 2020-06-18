#include "square.h"
#include <iostream>

// define constructor
Square::Square(double side_length)
{
  this->_side_length = side_length;
}

// define method
double Square::area()
{
  return this->_side_length * this->_side_length;
}
