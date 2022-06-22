#include <fstream>
#include <string>
#include <vector>
#include "Page.h"
#include "allocationFailed.h"
#include "invalidAdress.h"
#include "invalidInput.h"
#include "ProblemWithFile.h"

#define PAGES 5

using namespace std;

class GC{
    private:
        static vector <Page> pages; 
        
        GC(){}

    public:
        static void init();
        static void* allocate(size_t size);
        static void free(void *region);
        static void grow(void *region, size_t size);
        static void shrink(void *region, size_t size);
        static void dump(string filepath);
        //static void clean();
};
