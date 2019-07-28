c++14: N3664 "Clarifying memory allocation"

Resource
http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3664.html

Compiler support
gcc N/A
Clang 3.4

Problem

As strict reading of the current C and C++ standards may lead one to conclude that the allocation strategy shall not consider any information not derivable from the sequence of new and delete expressions. In essence, the standards may exclude macro-optimization of allocation.

  On the other hand, a strict reading of the standards may lead one to conclude that the implementation must make an allocation function call for each and every new expression. This reading may exclude micro-optimization of allocation.

Solution

  We propose to replace existing mechanistic wording with wording more precisely focused on essential requirements. The intent is to enable behavior that some existing compilers and memory allocators already have. For example, see TCMalloc [TCM].


This paper aims at rephrasing the Memory Allocation part in the C++ Standard to a more detailed version. It proposes to replace existing mechanistic wording with wording more precisely focused on essential requirements.
