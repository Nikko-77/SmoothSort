#include <iostream>
#include <string>
#include <omp.h>

#include "leonardo_numbers.hh"
#include "leonardo_tree_view.hh"
#include "leonardo_heap.hh"
#include "smoothsort.hh"

#include "array_random.hh"

int main(int argc, char** argv) {
	int n_threads;
	if ( argc != 2 )
		n_threads = 4;
	else {
		n_threads = std::stoi(argv[1]);
	}
	omp_set_num_threads( n_threads );
	
	using std::cout, std::endl;
	smoothsort(v);
	//for ( int n : v ) cout << n << " "; cout << endl;
}