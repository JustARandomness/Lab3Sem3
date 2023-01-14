#include <iostream>
#include <cstring>

int NoError = 0;
int NoListCreatedCode = 1;
int NoArrayCreatedCode = 2;
int IndexOutOfRangeCode = 3;
int DifferentSizedMatricesCode = 4;
int NotSquareMatrixCode = 5;
int ChangingTriangleMatrixCode = 6;
int NoSuchOptionFoundCode = 7;
int NoErrYetCode = 8;
int WrongNumTypeCode = 9;

const char* NoErrorMsg = "No Errors";
const char* NoListCreatedMsg = "No linked list created";
const char* NoArrayCreatedMsg = "No array created";
const char* IndexOutOfRangeMsg = "Index out of range";
const char* DifferentSizedMatricesMsg = "Matrices have different size";
const char* NotSquareMatrixMsg = "This is not square matrix";
const char* ChangingTriangleMatrixMsg = "This won't be a triangle matrix";
const char* NoSuchOptionFoundMsg = "No such option found. Try again";
const char* WrongNumTypeMsg = "You entered number of the wrong type. Try again";

class ErrorInfo : public std::exception {
private:
    int code;
    char message[100];
public:
    ErrorInfo() {
        this->code = NoError;
    };

    ErrorInfo(int errorCode, const char* s) {
        this->code = errorCode;
        for (int i = 0; i < strlen(s); ++i) {
            this->message[i] = s[i];
        }
        this->message[strlen(s)] = '\0';
    }
public:
    void copyErrorMsg(const char* s) {
        for (int i = 0; i < strlen(s); ++i) {
            this->message[i] = s[i];
        }
        this->message[strlen(s)] = '\0';
    }

    int getErrorCode() const {
        return this->code;
    }

    void setErrorCode(int errCode) {
        this->code = errCode;
    }

    void getErrorMsg() const {
        int i = 0;
        while (this->message[i]) {
            std :: cout << message[i];
            ++i;
        }
        std :: cout << '\n';
    }
};
