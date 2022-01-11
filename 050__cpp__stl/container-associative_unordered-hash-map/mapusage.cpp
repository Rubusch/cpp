// mapusage.cpp
/*
  demonstrates an unordered hash map

  -> elements access in O(1)

  alternatively, use an ordered map which typically builds on
  red-black-trees (element access in O(ln) )
//*/

#include <iostream>
#include <unordered_map>


class Hashtable
{
  std::unordered_map<const void *, const void *> umap;

public:
  void put(const void *key, const void *value)
  {
    umap[key] = value;
  }

  const void *get(const void *key)
  {
    return umap[key];
  }

  void display()
  {
//*
  // will need casting
    for (auto const& it : umap)
      {
        std::cout << (char*) it.first
                  << ':'
                  << (char*) it.second
                  << std::endl;
      }
/*/
    for (auto it = umap.begin(); it != umap.end(); ++it) {
      std::cout << it->first << "\t" << it->second << std::endl;
    }
// */
  }
};

int main()
{
  Hashtable ht;

  ht.put("Bob", "Alice");

  int some_value = 123;
  ht.put("some", &some_value);

  std::cout << "key: 'Bob' -> " << (char*) ht.get("Bob") << ";" << std::endl;
  std::cout << "key: 'some' -> " << *(int*) ht.get("some") << ";" << std::endl;

  ht.display();

  exit(EXIT_SUCCESS);
}
