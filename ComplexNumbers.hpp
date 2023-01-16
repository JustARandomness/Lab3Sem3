#include <iostream>
#include <cstring>
#include <cmath>

template <typename T>
class ComplexNumber {
    private:
        T Real = 0;
        T Imaginary = 0;
    public:
        ComplexNumber() {
            this->Imaginary = 0;
            this->Real = 0;
        }

        ComplexNumber(T item) {
            this->Real = item;
            this->Imaginary = 0;
        }

        ComplexNumber(T realItem, T imaginaryItem) {
            this->Real = realItem;
            this->Imaginary = imaginaryItem;
        }

        ComplexNumber(const ComplexNumber& number) {
            this->Real = number.Real;
            this->Imaginary = number.Imaginary;
        }
    public:
        T GetRealPart() {
            return this->Real;
        }

        T GetImaginaryPart() {
            return this->Imaginary;
        }
    public:
        void SetRealPart(T item) {
            this->Real = item;
        }

        void SetImaginaryPart(T item) {
            this->Imaginary = item;
        }

        ComplexNumber Power(int power) {
            ComplexNumber<T> result(*this);
            for (int i = 0; i < power; ++i) {
                result *= this;
            }
        }
    public:
        ComplexNumber operator+ (const ComplexNumber B) {
            ComplexNumber resultNumber(*this);
            resultNumber.Real = resultNumber.Real + B.Real;
            resultNumber.Imaginary = resultNumber.Imaginary + B.Imaginary;
            return resultNumber;
        }

        ComplexNumber operator- (const ComplexNumber B) {
            ComplexNumber resultNumber(*this);
            resultNumber.Real = resultNumber.Real - B.Real;
            resultNumber.Imaginary = resultNumber.Imaginary - B.Imaginary;
            return resultNumber;
        }

        ComplexNumber operator* (const ComplexNumber B) {
            ComplexNumber resultNumber(*this);
            resultNumber.Real = resultNumber.Real * B.Real - resultNumber.Imaginary * B.Imaginary;
            resultNumber.Imaginary = resultNumber.Imaginary * B.Real + resultNumber.Real * B.Imaginary;
            return resultNumber;
        }

        ComplexNumber operator* (const T number) {
            ComplexNumber resultNumber(*this);
            resultNumber.Real = resultNumber.Real * number - resultNumber.Imaginary * number;
            resultNumber.Imaginary = resultNumber.Imaginary * number + resultNumber.Real * number;
            return resultNumber;
        }

        ComplexNumber& operator= (const ComplexNumber B) {
            this->Real = B.Real;
            this->Imaginary = B.Imaginary;
            return *this;
        }

        ComplexNumber& operator= (const T item) {
            this->Real = item;
            this->Imaginary = 0;
            return *this;
        }

        bool operator== (const T item) {
            if (this->Real == item && this->Imaginary == 0) {
                return true;
            }
            else {
                return false;
            }
        }

        bool operator!= (const T item) {
            if (this->Real != item || this->Imaginary != 0) {
                return true;
            }
            else {
                return false;
            }
        }

        friend std::ostream& operator<< (std::ostream& os, const ComplexNumber& complexNumber) {
            if (complexNumber.Real == 0 && complexNumber.Imaginary == 0) {
                std::cout << complexNumber.Real << "    ";
            }
            else {
                if (complexNumber.Imaginary >= 0) {
                    std::cout << complexNumber.Real << " + " << complexNumber.Imaginary << "i";
                } else {
                    std::cout << complexNumber.Real << " - " << (-complexNumber.Imaginary) << "i";
                }
            }
            return os;
        }

        friend std::istream& operator>> (std::istream& is, ComplexNumber& complexNumber) {
            std::cout << "\nEnter real part:\n";
            is >>  complexNumber.Real;
            std::cout << "Enter imaginary part:\n";
            is >> complexNumber.Imaginary;
            return is;
        }
};