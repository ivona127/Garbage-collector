#include <iostream>
#include <string>
#include <vector>
#include "Test.h"

using namespace std;

int main () {
    GC::init();
    try{
        int* test1 = (int*)GC::allocate(sizeof(int));
        *test1 = 5;
        cout << test1 << " " << *test1 << endl;

        int* test2 = (int*)GC::allocate(sizeof(int));
        *test2 = 7;
        cout << test2 << " " << *test2 << endl;

        int* test3 = (int*)GC::allocate(sizeof(int)*2);
        cout << test3 << endl;

        GC::free(test2);
        GC::grow(test1, sizeof(int));
        GC::shrink(test3, sizeof(int));
        
        Test *test = new Test();
        delete test;

        Test* test4 = new Test[5];
        GC::dump("GC.txt");

    } catch(allocationFailed& ex) {
        cout << "Exception caught: " << ex.what() << endl;
    } catch(invalidAdress& ex) {
       cout << "Exception caught: " << ex.what() << endl;
    } catch(invalidInput& ex) {
        cout << "Exception caught: " << ex.what() << endl;
    } catch(ProblemWithFile& ex) {
        cout << "Exception caught: " << ex.what() << endl;
    }

    //GC::clean();

    return 0;
}
