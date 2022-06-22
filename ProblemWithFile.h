#include <string>

using namespace std;

class ProblemWithFile : public exception{
    private:
        string message;
    public:
        ProblemWithFile(){
            this->message = "There is a problem with the file.";
        }
        const char* what(){
            return this->message.c_str();
        }
};