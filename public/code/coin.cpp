#include <iostream>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_thread_num() 0
#endif

int flip_coin(){
	int n = rand() % 2;
	return n;
}

int main(){
	int count = 0;
	#pragma omp parallel reduction( + : count )
	{
		int private_count = 0;

		#pragma omp for
		for (int i=0; i<100; i++)
		{
			int flip = flip_coin();
			
			if (flip == 1)
			{
				++private_count;
			}	
		}
		count += private_count;
	}
		std::cout << "Estimated mean of 100 coin flips is: " << count/double(100) <<"\n";
	return 0;
}
