#include <vector>
#include "Block.h"
#define MAX_SIZE 1024

using namespace std;

class Page{
    public:
        char data[MAX_SIZE];
        vector <Block> blocks;
};