#include <string>

using namespace std;

class invalidAdress : public exception{
    private:
        string message;
    public:
        invalidAdress(){
            this->message = "Invalid block beginning adress!";
        }
        const char* what(){
            return this->message.c_str();
        }
};