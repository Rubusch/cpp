// tricks in Cpp


// output of vector contents
#include <iterator>
copy(vec.begin(), vec.end(), ostream_iterator< int >(cout, " "));
// or array contents
copy(arr, arr + 10, ostream_iterator< int >(cout, " "));


// unique for std::vectors
#include <algorithm>
#include <vector>
vector< char > vec;
// push_back() some elems...
sort(vec.begin(), vec.end());
vec.erase(unique(vec.begin(), vec.end()), vec.end());
