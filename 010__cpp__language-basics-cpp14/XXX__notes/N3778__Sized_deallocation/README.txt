c++14: N3778 "Sized deallocation"

Resource
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3778.html

Compiler support
gcc 5 (GNU)
Clang 3.4


Problem

With C++11, programmers may define a static member function operator delete that takes a size parameter indicating the size of the object to be deleted. The equivalent global operator delete is not available. This omission has unfortunate performance consequences.

Modern memory allocators often allocate in size categories, and, for space efficiency reasons, do not store the size of the object near the object. Deallocation then requires searching for the size category store that contains the object. This search can be expensive, particularly as the search data structures are often not in memory caches.

Solution

Permit implementations and programmers to define sized versions of the global operator delete. The compiler shall call the sized version in preference to the unsized version when the sized version is available.

There are two potential problems with this solution.
