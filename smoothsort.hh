#ifndef FF57C637_1D1C_4435_91D1_BD4B694DBC3C
#define FF57C637_1D1C_4435_91D1_BD4B694DBC3C

#include <ranges>
#include "leonardo_heap.hh"

auto smoothsort(std::ranges::random_access_range auto& range) {
	auto heap = heapify(range);
	unheapify(heap);
	return range;
}

#endif /* FF57C637_1D1C_4435_91D1_BD4B694DBC3C */
