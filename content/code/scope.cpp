#include <iostream>

// declare global variable
int i;

int main()
{
  //declare local variable
  int i = 10;
  
	for (int i=5; i>0; i--)
	{
		std::cout << i << std::endl;
	}

	std::cout << "Run!" << std::endl;

	std::cout << "The current value of i is: " << i << std::endl;
	return 0;
}
