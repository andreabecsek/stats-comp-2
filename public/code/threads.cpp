#include <iostream>

#ifdef _OPENMP
    #include <omp.h>
#else
    #define omp_get_num_threads() 0
    #define omp_get_thread_num() 0
#endif

int main(){
	std::cout << "This is the main thread.\n";

	#pragma omp parallel
	{
		int n_threads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();

		std::cout << "This is thread " << thread_id << " out of " << n_threads << "\n";
	}

	std::cout << "This is the main thread again.\n";

	return 0;
}

