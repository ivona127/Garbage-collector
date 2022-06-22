#include <string>

using namespace std;

class invalidInput : public exception{
    private:
        string message;
    public:
        invalidInput(){
            this->message = "Invalid input!";
        }
        const char* what(){
            return this->message.c_str();
        }
};
