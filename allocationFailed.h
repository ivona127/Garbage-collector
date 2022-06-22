#include <string>

using namespace std;

class allocationFailed : public exception{
    private:
        string message;
    public:
        allocationFailed(){
            this->message = "Allocation failed";
        }
        const char* what(){
            return this->message.c_str();
        }
};