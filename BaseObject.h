#include "GC.h"

using namespace std;

class BaseObject{
    public:
        void* operator new(size_t size){
            return GC::allocate(size);
        }

        void operator delete(void* region){
            GC::free(region);
        }

        void* operator new[](size_t size){
            return GC::allocate(size);
        }

        void operator delete[](void* region){
            GC::free(region);
        }
};
