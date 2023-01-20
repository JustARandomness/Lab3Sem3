#include <iostream>
#include <cstring>
#include <cmath>

template<class T>
class RectangleMatrix {
    protected:
        DynamicArray<T>* rectangleMatrix;
        size_t lines = 0;
        size_t columns = 0;

        struct access {
            DynamicArray<T>* data;
            size_t i;
            size_t columns;

            access(DynamicArray<T>* _data, size_t _i, size_t _columns) : data(_data), i(_i), columns(_columns) {}

            T& operator[](size_t j){
                return (*this->data)[i * columns + j];
            }
        };
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
            this->rectangleMatrix->setSize(linesCount * columnsCount);
            for (int i = 0; i < linesCount * columnsCount; ++i) {
                this->rectangleMatrix->set(i, item);
            }
            this->rectangleMatrix->setSize(linesCount * columnsCount);
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
        int getColumnsCount() {
            return this->columns;
        }

        int getLinesCount() {
            return this->lines;
        }

        virtual const T& get(int lineSerialNumber, int columnSerialNumber) const {
            return this->rectangleMatrix->get((lineSerialNumber - 1) * this->columns + (columnSerialNumber - 1));
        }

        T* getArrayCopy() const {
            T *items = new T[this->rectangleMatrix->getSize()];
            for (int i = 0; i < this->rectangleMatrix->getSize(); ++i) {
                items[i] = this->rectangleMatrix->get(i);
            }
            return items;
        }

        virtual RectangleMatrix getLine(int lineSerialNumber) {
            T *items = new T[this->columns];
            for (int i = 0; i < this->columns; ++i) {
                items[i] = this->get(lineSerialNumber, i + 1);
            }
            RectangleMatrix newRectangleMatrix(items, 1, this->columns);
            delete[] items;
            return newRectangleMatrix;
        }

        virtual RectangleMatrix getColumn(int columnSerialNumber) {
            T *items = new T[this->lines];
            for (int i = 0; i < this->lines; ++i) {
                items[i] = this->get(i + 1, columnSerialNumber);
            }
            RectangleMatrix newRectangleMatrix(items, this->lines, 1);
            delete[] items;
            return newRectangleMatrix;
        }

    public:
        virtual void set(T item, int lineSerialNumber, int columnSerialNumber) {
            this->rectangleMatrix->set((lineSerialNumber - 1) * this->columns + (columnSerialNumber - 1), item);
        }

        /*virtual double EuclideanNorm() {
            if (sizeof(T) != sizeof(ComplexNumber<int>) && sizeof(T) != sizeof(ComplexNumber<int>) {
                double sum = 0;
                double temp = 0;
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        temp = this->get(i + 1, j + 1);
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
                        temp = this->get(i + 1, j + 1);
                        temp = temp.Power(2);
                        sum += temp;
                    }
                }
                sum = pow(sum, 0.5);
                return sum;
            }
        }*/

        virtual void multiplyLineByNumber(int lineSerialNumber, T number) {
            for (int j = 0; j < this->columns; ++j) {
                this->rectangleMatrix->set((lineSerialNumber - 1) * this->columns + j, this->get(lineSerialNumber, j + 1) * number);
            }
        }

        virtual void multiplyColumnByNumber(int columnSerialNumber, T number) {
            for (int i = 0; i < this->lines; ++i) {
                this->rectangleMatrix->set(i * this->columns + (columnSerialNumber - 1), this->get(i + 1, columnSerialNumber) * number);
            }
        }

        void swapColumns(int firstColumnSerialNumber, int secondColumnSerialNumber) {
            T temp;
            for (int i = 0; i < this->lines; ++i) {
                temp = this->get(i + 1, firstColumnSerialNumber);
                this->set(this->get(i + 1, secondColumnSerialNumber), i + 1, firstColumnSerialNumber);
                this->set(temp, i + 1, firstColumnSerialNumber);
            }
        }

        void swapLines(int firstLineSerialNumber, int secondLineSerialNumber) {
            T temp;
            for (int j = 0; j < this->columns; ++j) {
                temp = this->get(firstLineSerialNumber, j + 1);
                this->set(this->get(secondLineSerialNumber, j + 1), firstLineSerialNumber, j + 1);
                this->set(temp, secondLineSerialNumber, j + 1);
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
                    result.set(i + 1, j + 1, result.Get(i + 1, j + 1) + B.Get(i + 1, j + 1));
                }
            }
            return result;
        }

        RectangleMatrix operator-(const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.set(i + 1, j + 1, result.Get(i + 1, j + 1) - B.Get(i + 1, j + 1));
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
                    this->set(B.get(i + 1, j + 1), i + 1, j + 1);
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
                                       result.Get(i + 1, j + 1) + (B.Get(l + 1, j + 1) * this->get(i + 1, l + 1)));
                        }
                    }
                }
                return result;
            } else {
                throw ErrorInfo(DifferentSizedMatricesCode, DifferentSizedMatricesMsg);
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

        access operator[](int i) {
            return access(this->rectangleMatrix, i, this->columns);
        }

        friend std::ostream &operator<<(std::ostream &os, RectangleMatrix rectangleMatrix1) {
            for (int i = 0; i < rectangleMatrix1.lines; ++i) {
                for (int j = 0; j < rectangleMatrix1.columns; ++j) {
                    os << std::setprecision(3) << rectangleMatrix1.get(i + 1, j + 1) << " ";
                }
                os << "\n";
            }
            return os;
        }
};