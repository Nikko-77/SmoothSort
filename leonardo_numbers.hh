#ifndef A2A56F51_2ABD_4596_8B71_0C086D789142
#define A2A56F51_2ABD_4596_8B71_0C086D789142

#include <array>
#include <stdexcept>
#include <cmath>

constinit auto leonardo = []() {
	std::array<std::size_t, 44> arr;
	arr[0] = arr[1] = 1;
	for ( int i = 2; i < arr.size(); i++ )
		arr[i] = arr[i-1] + arr[i-2] + 1;
	return arr;
}();

// Calculates the leonardo index on the "leonardo" array for the given number
// If the number its not a leonardo number, it interpolates between the leonardo numbers it is between
// and gives a decimal index (which can be truncated to obtain the index of the highest leonardo number that is less than the given number)
float calculate_leonardo_position(std::size_t n, bool strict = false) {
	for ( std::size_t i = 1; i < leonardo.size(); i++ ) {
		if ( strict ) {
			if ( n == leonardo[i] ) return i;
			else if ( n < leonardo[i] ) throw std::runtime_error("Number is not a leonardo number.");
		} else if ( n <= leonardo[i] ) {
			if ( i == 1 ) return leonardo[i];
			else return std::lerp((float)i-1, (float)i, ( ((float)n-leonardo[i-1])/(float)(leonardo[i] - leonardo[i-1]) ));
		}
	}
	throw std::runtime_error("calculate_leonardo_position(): Number out of bounds.");
}

#endif /* A2A56F51_2ABD_4596_8B71_0C086D789142 */
