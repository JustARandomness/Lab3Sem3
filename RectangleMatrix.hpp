#include <iostream>
#include <cstring>
#include <cmath>

template<class T>
class RectangleMatrix {
    protected:
        DynamicArray<T>* rectangleMatrix;
        size_t lines = 0;
        size_t columns = 0;
    public:
        RectangleMatrix() = default;

        RectangleMatrix(T *items, int linesCount, int columnsCount) {
            this->lines = linesCount;
            this->columns = columnsCount;
            this->rectangleMatrix = new DynamicArray<T>(items, linesCount * columnsCount);
        }

        RectangleMatrix(int linesCount, int columnsCount) {
            T item;
            item = 0;
            this->lines = linesCount;
            this->columns = columnsCount;
            this->rectangleMatrix = new DynamicArray<T>(linesCount * columnsCount);
            this->rectangleMatrix->SetSize(linesCount * columnsCount);
            for (int i = 0; i < linesCount * columnsCount; ++i) {
                this->rectangleMatrix->Set(i, item);
            }
            this->rectangleMatrix->SetSize(linesCount * columnsCount);
        }

        RectangleMatrix(const RectangleMatrix &matrix) {
            this->rectangleMatrix = new DynamicArray<T>(*matrix.rectangleMatrix);
            this->lines = matrix.lines;
            this->columns = matrix.columns;
        }

        ~RectangleMatrix() {
            delete this->rectangleMatrix;
        }

    public:
        int GetColumnsCount() {
            return this->columns;
        }

        int GetLinesCount() {
            return this->lines;
        }

        virtual T Get(int lineSerialNumber, int columnSerialNumber) const {
            return this->rectangleMatrix->Get((lineSerialNumber - 1) * this->columns + (columnSerialNumber - 1));
        }


        T *GetArrayCopy() const {
            T *items = new T[this->rectangleMatrix->GetSize()];
            for (int i = 0; i < this->rectangleMatrix->GetSize(); ++i) {
                items[i] = this->rectangleMatrix->Get(i);
            }
            return items;
        }

        virtual RectangleMatrix GetLine(int lineSerialNumber) {
            T *items = new T[this->columns];
            for (int i = 0; i < this->columns; ++i) {
                items[i] = this->Get(lineSerialNumber, i + 1);
            }
            RectangleMatrix newRectangleMatrix(items, 1, this->columns);
            delete[] items;
            return newRectangleMatrix;
        }

        virtual RectangleMatrix GetColumn(int columnSerialNumber) {
            T *items = new T[this->lines];
            for (int i = 0; i < this->lines; ++i) {
                items[i] = this->Get(i + 1, columnSerialNumber);
            }
            RectangleMatrix newRectangleMatrix(items, this->lines, 1);
            delete[] items;
            return newRectangleMatrix;
        }

    public:
        virtual void Set(T item, int lineSerialNumber, int columnSerialNumber) {
            this->rectangleMatrix->Set((lineSerialNumber - 1) * this->columns + (columnSerialNumber - 1), item);
        }

        /*virtual double EuclideanNorm() {
            if (sizeof(T) != sizeof(ComplexNumber<int>) && sizeof(T) != sizeof(ComplexNumber<int>) {
                double sum = 0;
                double temp = 0;
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        temp = this->Get(i + 1, j + 1);
                        temp = pow(temp, 2);
                        sum += temp;
                    }
                }
                sum = pow(sum, 0.5);
                return sum;
            }
            else if (sizeof(T) == sizeof(ComplexNumber<double>) && sizeof(T) != sizeof(ComplexNumber<int>) {
                ComplexNumber<double> sum = 0;
                ComplexNumber<double> temp = 0;
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        temp = this->Get(i + 1, j + 1);
                        temp = temp.Power(2);
                        sum += temp;
                    }
                }
                sum = pow(sum, 0.5);
                return sum;
            }
        }*/

        virtual void MultiplyLineByNumber(int lineSerialNumber, T number) {
            for (int j = 0; j < this->columns; ++j) {
                this->rectangleMatrix->Set((lineSerialNumber - 1) * this->columns + j, this->Get(lineSerialNumber, j + 1) * number);
            }
        }

        virtual void MultiplyColumnByNumber(int columnSerialNumber, T number) {
            for (int i = 0; i < this->lines; ++i) {
                this->rectangleMatrix->Set(i * this->columns + (columnSerialNumber - 1), this->Get(i + 1, columnSerialNumber) * number);
            }
        }

        void SwapColumns(int firstColumnSerialNumber, int secondColumnSerialNumber) {
            T temp;
            for (int i = 0; i < this->lines; ++i) {
                temp = this->Get(i + 1, firstColumnSerialNumber);
                this->Set(this->Get(i + 1, secondColumnSerialNumber), i + 1, firstColumnSerialNumber);
                this->Set(temp, i + 1, firstColumnSerialNumber);
            }
        }

        void SwapLines(int firstLineSerialNumber, int secondLineSerialNumber) {
            T temp;
            for (int j = 0; j < this->columns; ++j) {
                temp = this->Get(firstLineSerialNumber, j + 1);
                this->Set(this->Get(secondLineSerialNumber, j + 1), firstLineSerialNumber, j + 1);
                this->Set(temp, secondLineSerialNumber, j + 1);
            }
        }

        bool isSquareMatrix() {
            if (this->lines == this->columns) {
                return true;
            } else {
                return false;
            }
        }

    public:
        RectangleMatrix operator+(const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) + B.Get(i + 1, j + 1));
                }
            }
            return result;
        }

        RectangleMatrix operator-(const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) - B.Get(i + 1, j + 1));
                }
            }
            return result;
        }

        virtual RectangleMatrix &operator=(const RectangleMatrix B) {
            delete this->rectangleMatrix;
            this->lines = B.lines;
            this->columns = B.columns;
            this->rectangleMatrix = new DynamicArray<T>(*B.rectangleMatrix);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    this->Set(B.Get(i + 1, j + 1), i + 1, j + 1);
                }
            }
            return *this;
        }

        RectangleMatrix operator*(const RectangleMatrix B) {
            if (this->columns == B.lines) {
                RectangleMatrix result(this->lines, B.columns);
                for (int i = 0; i < result.lines; ++i) {
                    for (int j = 0; j < result.columns; ++j) {
                        for (int l = 0; l < this->columns; ++l) {
                            result.Set(i + 1, j + 1,
                                       result.Get(i + 1, j + 1) + (B.Get(l + 1, j + 1) * this->Get(i + 1, l + 1)));
                        }
                    }
                }
                return result;
            } else {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(DifferentSizedMatricesCode);
                errorInfo.CopyErrorMsg(DifferentSizedMatricesMsg);
                throw errorInfo;
            }
        }

        RectangleMatrix operator*(T item) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.Set(i + 1, j + 1, result.Get(i + 1, j + 1) * item);
                }
            }
            return result;
        }

        friend std::ostream &operator<<(std::ostream &os, RectangleMatrix rectangleMatrix1) {
            for (int i = 0; i < rectangleMatrix1.lines; ++i) {
                for (int j = 0; j < rectangleMatrix1.columns; ++j) {
                    std::cout << std::setprecision(3) << rectangleMatrix1.Get(i + 1, j + 1) << " ";
                }
                std::cout << "\n";
            }
            return os;
        }
};