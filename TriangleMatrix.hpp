#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class TriangleMatrix : public SquareMatrix<T> {
    public:
        int getTriangleMatrixElementCount(int item) {
            int result = 0;
            for (int i = item; i > 0; --i) {
                result += i;
            }
            return result;
        }

        TriangleMatrix() = default;

        TriangleMatrix(T item, int count) {  // Заполняет все элементы, стоящие выше главной диагонали введенным числом
            this->rectangleMatrix = new DynamicArray<T>(getTriangleMatrixElementCount(count));
            this->lines = count;
            this->columns = count;
            this->size = count;
            for (int i = 0; i < getTriangleMatrixElementCount(count); ++i) {
                this->rectangleMatrix->set(i, item);
            }
            this->rectangleMatrix->setSize(getTriangleMatrixElementCount(count));
        }

        TriangleMatrix(T* items, int count) {
            this->rectangleMatrix = new DynamicArray<T>(getTriangleMatrixElementCount(count));
            this->lines = count;
            this->columns = count;
            this->size = count;
            for (int i = 0; i < count * count - int((count * count - count) * 0.5); ++i) {
                this->rectangleMatrix->set(i, items[i]);
            }
            this->rectangleMatrix->setSize(getTriangleMatrixElementCount(count));
        }

        TriangleMatrix(const TriangleMatrix<T>& triangleMatrix) {
            this->rectangleMatrix = new DynamicArray<T>(*triangleMatrix.rectangleMatrix);
            this->size = triangleMatrix.size;
            this->columns = this->size;
            this->lines = this->size;
        }
    public:
        T get(int lineSerialNumber, int columnSerialNumber) const override {
            if (lineSerialNumber > 1 && columnSerialNumber <= lineSerialNumber - 1) {
                T item;
                item = 0;
                return item;
            }
            else {
                if (lineSerialNumber == this->size && columnSerialNumber == this->size) {
                    return this->rectangleMatrix->get(this->rectangleMatrix->getSize() - 1);
                }
                else {
                    return this->rectangleMatrix->get((lineSerialNumber - 1) * this->size + (columnSerialNumber - 1) - (lineSerialNumber - 1));
                }
            }
        }

        void set(T item, int lineSerialNumber, int columnSerialNumber) override {
            if (lineSerialNumber > 1 && columnSerialNumber <= lineSerialNumber - 1) {
                throw ErrorInfo(ChangingTriangleMatrixCode, ChangingTriangleMatrixMsg);
            }

            if (lineSerialNumber == this->size && columnSerialNumber == this->size) {
                this->rectangleMatrix->set(this->rectangleMatrix->getSize() - 1, item);
            }
            else {
                this->rectangleMatrix->set((lineSerialNumber - 1) * this->size + (columnSerialNumber - 1) - (lineSerialNumber - 1), item);
            }
        }

        /*double EuclideanNorm() override {
            double sum = 0;
            double temp = 0;
            for (int i = 0; i < this->rectangleMatrix->getSize(); ++i) {
                temp = this->rectangleMatrix->get(i);
                temp = pow(temp, 2);
                sum += temp;
            }
            sum = pow(sum, 0.5);
            return sum;
        }*/

        RectangleMatrix<T> getLine(int lineSerialNumber) override {
            T* items = new T [this->columns];
            for (int i = 0; i < this->columns; ++i) {
                if (i + 1 <= lineSerialNumber - 1) {
                    T item;
                    item = 0;
                    items[i] = item;
                }
                else {
                    items[i] = this->get(lineSerialNumber, i + 1);
                }
            }
            RectangleMatrix<T> newRectangleMatrix(items, 1, this->columns);
            delete[] items;
            return newRectangleMatrix;
        }

        RectangleMatrix<T> getColumn(int columnSerialNumber) override {
            T* items = new T [this->lines];
            for (int i = 0; i < this->lines; ++i) {
                if (i >= columnSerialNumber) {
                    T item;
                    item = 0;
                    items[i] = item;
                }
                else {
                    items[i] = this->get(i + 1, columnSerialNumber);
                }
            }
            RectangleMatrix<T> newRectangleMatrix(items, this->lines, 1);
            delete[] items;
            return newRectangleMatrix;
        }

        void MultiplyLineByNumber(int lineSerialNumber, T number) override {
            for (int j = 0; j < this->columns; ++j) {
                if (lineSerialNumber > 1 && j + 1 <= lineSerialNumber - 1) {
                    continue;
                }
                else {
                    this->set(this->get(lineSerialNumber, j + 1) * number, lineSerialNumber, j + 1);
                    std::cout << this->get(lineSerialNumber, j + 1) << "\n";
                }
            }
        }

        void MultiplyColumnByNumber(int columnSerialNumber, T number) override {
            for (int i = 0; i < this->lines; ++i) {
                if (i + 1 > 1 && columnSerialNumber <= i) {
                    continue;
                }
                else {
                    this->set(this->get(i + 1, columnSerialNumber) * number, i + 1, columnSerialNumber);
                }
            }
        }
    public:
        TriangleMatrix operator+ (const TriangleMatrix B) {
            auto newTriangleMatrix (*this);
            if (newTriangleMatrix.rectangleMatrix->getSize() == B.rectangleMatrix->getSize()) {
                for (int i = 0; i < newTriangleMatrix.rectangleMatrix->getSize(); ++i) {
                    newTriangleMatrix.rectangleMatrix->set(i, newTriangleMatrix.rectangleMatrix->get(i) + B.rectangleMatrix->get(i));
                }
            }
            return newTriangleMatrix;
        }

    TriangleMatrix operator- (const TriangleMatrix B) {
        auto newTriangleMatrix = new TriangleMatrix(*this);
        if (newTriangleMatrix.rectangleMatrix->getSize() == B.rectangleMatrix->getSize()) {
            for (int i = 0; i < newTriangleMatrix.rectangleMatrix->getSize(); ++i) {
                newTriangleMatrix.rectangleMatrix->set(i, newTriangleMatrix.rectangleMatrix->get(i) - B.rectangleMatrix->get(i));
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
                std :: cout << std :: setprecision(3) << triangleMatrix.get(i + 1, j + 1) << " ";
            }
            std :: cout << "\n";
        }
        return os;
    }
};
