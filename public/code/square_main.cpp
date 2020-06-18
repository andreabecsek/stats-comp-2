#include "square.h"
#include <iostream>

int main(){
  //create squares with side lengths 3 and 4.5
  Square square_obj_1(3);
  Square square_obj_2(4.5);
  
  //print square side length
  std::cout << "Square 1 has area " << square_obj_1.area() << std::endl;
  std::cout << "Square 2 has area " << square_obj_2.area() << std::endl;
  return(0);
}
