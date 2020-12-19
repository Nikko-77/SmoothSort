#ifndef CC3872EC_2426_4124_9121_4F5BAE6127E0
#define CC3872EC_2426_4124_9121_4F5BAE6127E0

#include <iterator>
#include <iostream>
#include <cmath>
#include "leonardo_numbers.hh"

// Gives a Leonardo Tree View of the desired range.
// It doesn't own the range though you can use either of its iterators to modify the range values.
template <typename RandomAccessIterator, typename T = std::iterator_traits<RandomAccessIterator>::value_type>
class LeonardoTreeView {
	public:
		LeonardoTreeView( RandomAccessIterator begin, RandomAccessIterator end ) : m_begin(begin), m_end(end) {
			level = calculate_leonardo_position( std::distance(m_begin,m_end), true );
		}
		LeonardoTreeView left() {
			return LeonardoTreeView( m_begin, m_begin+leonardo[level-1] );
		}
		LeonardoTreeView right() {
			return LeonardoTreeView( m_begin+leonardo[level-1], m_begin+leonardo[level-1]+leonardo[level-2] );
		}
		RandomAccessIterator begin() { return m_begin; }
		RandomAccessIterator end() { return m_end; }
		std::size_t size() { return std::distance(m_begin,m_end); }
		T& left_child() { return *(m_begin+leonardo[level-1]-1); }
		T& right_child() { return *(m_begin+leonardo[level-1]+leonardo[level-2]-1); }
		bool has_children() { return level > 1; }
		T& operator*() { return *(m_end-1); }
	private:
		int level;
		RandomAccessIterator m_begin;
		RandomAccessIterator m_end;
};

// Returns the children with the highest value.
template <typename RandomAccessIterator>
auto max_children(LeonardoTreeView<RandomAccessIterator>& view) {
	if ( view.left_child() >= view.right_child() ) return view.left();
	else return view.right();
}

// Doesnt completely order the entire tree, it rather just orders the root node,
// then if it swapped it orders the node it swapped recursively (should have probably gave it a better name)
template <typename RandomAccessIterator>
LeonardoTreeView<RandomAccessIterator>& order(LeonardoTreeView<RandomAccessIterator>& view) {
	if ( view.has_children() ){
		auto max = max_children(view);
		if ( *view < *max ) {
			std::swap(*view,*max);
			order(max);
		}
	}
	return view;
}

template <typename RandomAccessIterator>
std::ostream& operator<<(std::ostream& os, LeonardoTreeView<RandomAccessIterator> tree) {
	std::cout << "{ ";
	for ( auto& n : tree ) 
		std::cout << n << " "; 
	std::cout << "}";
	return os;
}

#endif /* CC3872EC_2426_4124_9121_4F5BAE6127E0 */
