#include <iostream>
using namespace std;

class PageTable{

public:

	PageTable() : frameIndex(0) {}

private:

	size_t frameIndex;
};