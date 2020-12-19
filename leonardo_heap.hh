#ifndef B5B46051_1F4E_4782_96AE_2B941DAC1A9A
#define B5B46051_1F4E_4782_96AE_2B941DAC1A9A

#include "leonardo_tree_view.hh"
#include <omp.h>

#include <vector>
#include <span>
#include <ranges>
#include <iostream>

template <typename RAI, typename T = std::iterator_traits<RAI>::value_type >
using LeonardoHeap = std::vector< LeonardoTreeView<RAI,T> >;

// Returns a heap view of the given range.
// The first tree has the size of the highest leonardo number that is less or equal than the size of the range,
// and the subsequent trees are the highest leonardo number that is less or equal than the size of what is left of the given range. 
template <std::ranges::random_access_range RAR, typename RAI = std::ranges::iterator_t<RAR>>
LeonardoHeap<RAI> heap_view(RAR& range) {
	LeonardoHeap<RAI> heap;
	int leonardo_pos = 0;
	for ( int i = 0; i < std::size(range); i+=leonardo_pos ) {
		// Truncates the leonardo position so it returns the largest number that its not higher than the size of the range.
		leonardo_pos = leonardo[ (int)calculate_leonardo_position( std::size(range)-i )];
		heap.emplace_back( std::ranges::begin(range) + i, std::ranges::begin(range) + i + leonardo_pos );
	}
	return heap;
}

// Pushes all the elements from one to one and creates a Heap View from them on every iteration,
// It also orders them as they enter.
template <std::ranges::random_access_range RAR, typename RAI = std::ranges::iterator_t<RAR>, typename T = std::iterator_traits<RAI>::value_type>
LeonardoHeap<RAI,T> heapify(RAR& range) {
	RAI l_begin = std::begin(range);
	for ( int i = 1; i <= std::size(range); i++ ) {
		RAI l_end = std::begin(range)+i;
		std::span<T> subrange{l_begin, l_end};
		auto trees = heap_view(subrange);
		order( (trees.back()) );
		insertion_sort(trees);
	}
	return heap_view(range);
}

// Pops all the elements from the heap and orders them if necessary.
template <typename RAI, typename T = std::iterator_traits<RAI>::value_type>
void unheapify(LeonardoHeap<RAI,T>& heap) {
	while ( heap.size() > 0 ) {
		if ( heap.back().has_children() ) {
			auto left_node = heap.back().left();
			auto right_node = heap.back().right();
			heap.pop_back();
			heap.push_back( left_node );
			heap.push_back( right_node );
			insertion_sort(heap);
		} else {
			//insertion_sort(heap); // I don't know if this is needed, I'm pretty sure its not but I believe not having it caused some problems before
			heap.pop_back();
		}
	}
}

// I dont know if this is the way of doing the insertion sort on the leonardo heap,
// I have the understanding that you also have to check something with the stepchilds of the tree roots to be able to swap them,
// However, when I thought of it it really seemed like an unnecessary check so I throw it out,
// but I'd like to know if this was a wrong decision and how it would affect the result.
template <typename RAI, typename T = std::iterator_traits<RAI>::value_type>
LeonardoHeap<RAI,T>& insertion_sort(LeonardoHeap<RAI,T>& heap) {
	for ( int i = 1; i < heap.size(); i++ ) {
		int actual_index = i;
		while ( *(heap[actual_index]) < *(heap[actual_index-1]) ) {
			std::swap( *(heap[actual_index]), *(heap[actual_index-1]) );
			if ( --actual_index == 0 ) break;
		}
		//#pragma omp parallel for // Causes False Sharing for some reason, even though all trees are separated from each other.
		for ( int j = actual_index; j < i; j++ ) {
			order(heap[j]);
		}
	}
	return heap;
}

#endif /* B5B46051_1F4E_4782_96AE_2B941DAC1A9A */
