#ifndef _SQUARE_H
#define _SQUARE_H

// Class to computer area of a square
class Square 
{
  public:
  //declare constructor
  Square(double side_length);
  
  //declare method
  double area();

  private:
  double _side_length;
};

#endif
