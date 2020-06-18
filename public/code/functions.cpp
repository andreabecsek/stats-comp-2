#include <iostream>

int sum ( int a, int b)
{
	int c = a + b;
	return c;
}

bool even ( int a)
{
	return a % 2 == 0;
}


void print_hello()
{
	std::cout << "hello" <<  std::endl;
}

int main()
{	
	int c = sum(2,4);
	std::cout << "2+4=" <<  c << std::endl;

	std::cout << "Is 4 even?" << even(4) << std::endl;

	print_hello();
	
	return 0;
}
