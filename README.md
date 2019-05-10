# AVLIndex
A simple C++ Template Class for quick in memory storage index. The index is implemented as an AVL Tree. 

## Usage
Just copy the AVLIndex.h to your source directory. Include the template class like so:

#include "AVLIndex.h"

Here is an example usage:

AVLIndex<int, std::string> index;

index.add(1, "one");

std::string value;
index.get(1, &value);

index.remove(1);


## Checking it out
You can compile the test code in test.cpp using :
c++ -g test.cpp
### Running it
./a.out


