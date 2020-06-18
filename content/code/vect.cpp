#include <iostream>
#include <vector>

int main()
{
  //declare vector to hold integers and initialize with some values
  std::vector<int> vect = {5, 4, 3, 2};
  
  //append values to the end of the vector
  vect.push_back( 1 );
  
  //print vector values using loop
  std::cout << "vect{ ";
  
  int i = 0;
  while (i!=5) {

    //print ith element of the vector
    std::cout << vect[i] << " ";
    i++;
  }
  
  std::cout << "}" << std::endl;
  
  return 0;
}
