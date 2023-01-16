#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class TriangleMatrix : public SquareMatrix<T> {
    public:
        int GetTriangleMatrixElementCount(int item) {
            int result = 0;
            for (int i = item; i > 0; --i) {
                result += i;
            }
            return result;
        }

        TriangleMatrix() = default;

        TriangleMatrix(T item, int count) {  // Заполняет все элементы, стоящие выше главной диагонали введенным числом
            this->rectangleMatrix = new DynamicArray<T>(GetTriangleMatrixElementCount(count));
            this->lines = count;
            this->columns = count;
            this->size = count;
            for (int i = 0; i < GetTriangleMatrixElementCount(count); ++i) {
                this->rectangleMatrix->Set(i, item);
            }
            this->rectangleMatrix->SetSize(GetTriangleMatrixElementCount(count));
        }

        TriangleMatrix(T* items, int count) {
            this->rectangleMatrix = new DynamicArray<T>(GetTriangleMatrixElementCount(count));
            this->lines = count;
            this->columns = count;
            this->size = count;
            for (int i = 0; i < count * count - int((count * count - count) * 0.5); ++i) {
                this->rectangleMatrix->Set(i, items[i]);
            }
            this->rectangleMatrix->SetSize(GetTriangleMatrixElementCount(count));
        }

        TriangleMatrix(const TriangleMatrix<T>& triangleMatrix) {
            this->rectangleMatrix = new DynamicArray<T>(*triangleMatrix.rectangleMatrix);
            this->size = triangleMatrix.size;
            this->columns = this->size;
            this->lines = this->size;
        }
    public:
        T Get(int lineSerialNumber, int columnSerialNumber) const override {
            if (lineSerialNumber > 1 && columnSerialNumber <= lineSerialNumber - 1) {
                T item;
                item = 0;
                return item;
            }
            else {
                if (lineSerialNumber == this->size && columnSerialNumber == this->size) {
                    return this->rectangleMatrix->Get(this->rectangleMatrix->GetSize() - 1);
                }
                else {
                    return this->rectangleMatrix->Get((lineSerialNumber - 1) * this->size + (columnSerialNumber - 1) - (lineSerialNumber - 1));
                }
            }
        }

        void Set(T item, int lineSerialNumber, int columnSerialNumber) override {
            if (lineSerialNumber > 1 && columnSerialNumber <= lineSerialNumber - 1) {
                ErrorInfo errorInfo;
                errorInfo.SetErrorCode(ChangingTriangleMatrixCode);
                errorInfo.CopyErrorMsg(ChangingTriangleMatrixMsg);
                throw errorInfo;
            }

            if (lineSerialNumber == this->size && columnSerialNumber == this->size) {
                this->rectangleMatrix->Set(this->rectangleMatrix->GetSize() - 1, item);
            }
            else {
                this->rectangleMatrix->Set((lineSerialNumber - 1) * this->size + (columnSerialNumber - 1) - (lineSerialNumber - 1), item);
            }
        }

        /*double EuclideanNorm() override {
            double sum = 0;
            double temp = 0;
            for (int i = 0; i < this->rectangleMatrix->GetSize(); ++i) {
                temp = this->rectangleMatrix->Get(i);
                temp = pow(temp, 2);
                sum += temp;
            }
            sum = pow(sum, 0.5);
            return sum;
        }*/

        RectangleMatrix<T> GetLine(int lineSerialNumber) override {
            T* items = new T [this->columns];
            for (int i = 0; i < this->columns; ++i) {
                if (i + 1 <= lineSerialNumber - 1) {
                    T item;
                    item = 0;
                    items[i] = item;
                }
                else {
                    items[i] = this->Get(lineSerialNumber, i + 1);
                }
            }
            RectangleMatrix newRectangleMatrix(items, 1, this->columns);
            delete[] items;
            return newRectangleMatrix;
        }

        RectangleMatrix<T> GetColumn(int columnSerialNumber) override {
            T* items = new T [this->lines];
            for (int i = 0; i < this->lines; ++i) {
                if (i >= columnSerialNumber) {
                    T item;
                    item = 0;
                    items[i] = item;
                }
                else {
                    items[i] = this->Get(i + 1, columnSerialNumber);
                }
            }
            RectangleMatrix newRectangleMatrix(items, this->lines, 1);
            delete[] items;
            return newRectangleMatrix;
        }

        void MultiplyLineByNumber(int lineSerialNumber, T number) override {
            for (int j = 0; j < this->columns; ++j) {
                if (lineSerialNumber > 1 && j + 1 <= lineSerialNumber - 1) {
                    continue;
                }
                else {
                    this->Set(this->Get(lineSerialNumber, j + 1) * number, lineSerialNumber, j + 1);
                    std::cout << this->Get(lineSerialNumber, j + 1) << "\n";
                }
            }
        }

        void MultiplyColumnByNumber(int columnSerialNumber, T number) override {
            for (int i = 0; i < this->lines; ++i) {
                if (i + 1 > 1 && columnSerialNumber <= i) {
                    continue;
                }
                else {
                    this->Set(this->Get(i + 1, columnSerialNumber) * number, i + 1, columnSerialNumber);
                }
            }
        }
    public:
        TriangleMatrix operator+ (const TriangleMatrix B) {
            auto newTriangleMatrix (*this);
            if (newTriangleMatrix.rectangleMatrix->GetSize() == B.rectangleMatrix->GetSize()) {
                for (int i = 0; i < newTriangleMatrix.rectangleMatrix->GetSize(); ++i) {
                    newTriangleMatrix.rectangleMatrix->Set(i, newTriangleMatrix.rectangleMatrix->Get(i) + B.rectangleMatrix->Get(i));
                }
            }
            return newTriangleMatrix;
        }

    TriangleMatrix operator- (const TriangleMatrix B) {
        auto newTriangleMatrix = new TriangleMatrix(*this);
        if (newTriangleMatrix.rectangleMatrix->GetSize() == B.rectangleMatrix->GetSize()) {
            for (int i = 0; i < newTriangleMatrix.rectangleMatrix->GetSize(); ++i) {
                newTriangleMatrix.rectangleMatrix->Set(i, newTriangleMatrix.rectangleMatrix->Get(i) - B.rectangleMatrix->Get(i));
            }
        }
        return newTriangleMatrix;
    }

    TriangleMatrix& operator= (const TriangleMatrix B) {
        delete this->rectangleMatrix;
        this->rectangleMatrix = new DynamicArray<T>(*B.rectangleMatrix);
        return (*this);
    }

    friend std :: ostream& operator<< (std :: ostream& os, TriangleMatrix triangleMatrix) {
        for (int i = 0; i < triangleMatrix.lines; ++i) {
            for (int j = 0; j < triangleMatrix.columns; ++j) {
                std :: cout << std :: setprecision(3) << triangleMatrix.Get(i + 1, j + 1) << " ";
            }
            std :: cout << "\n";
        }
        return os;
    }
};
