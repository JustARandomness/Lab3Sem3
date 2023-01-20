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

        virtual const T& get(int line, int column) const {
            return this->rectangleMatrix->get(line * this->columns + column);
        }

        T* getArrayCopy() const {
            T *items = new T[this->rectangleMatrix->getSize()];
            for (int i = 0; i < this->rectangleMatrix->getSize(); ++i) {
                items[i] = this->rectangleMatrix->get(i);
            }
            return items;
        }

        virtual RectangleMatrix getLine(int line) {
            T *items = new T[this->columns];
            for (int i = 0; i < this->columns; ++i) {
                items[i] = this->get(line, i);
            }
            RectangleMatrix newRectangleMatrix(items, 1, this->columns);
            delete[] items;
            return newRectangleMatrix;
        }

        virtual RectangleMatrix getColumn(int column) {
            T *items = new T[this->lines];
            for (int i = 0; i < this->lines; ++i) {
                items[i] = this->get(i, column);
            }
            RectangleMatrix newRectangleMatrix(items, this->lines, 1);
            delete[] items;
            return newRectangleMatrix;
        }

    public:
        virtual void set(T item, int line, int column) {
            this->rectangleMatrix->set(line * this->columns + column, item);
        }

        virtual void multiplyLineByNumber(int line, T number) {
            for (int j = 0; j < this->columns; ++j) {
                this->rectangleMatrix->set(line * this->columns + j, this->get(line, j) * number);
            }
        }

        virtual void multiplyColumnByNumber(int column, T number) {
            for (int i = 0; i < this->lines; ++i) {
                this->rectangleMatrix->set(i * this->columns + column, this->get(i, column) * number);
            }
        }

        void swapColumns(int firstColumn, int secondColumn) {
            T temp;
            for (int i = 0; i < this->lines; ++i) {
                temp = this->get(i, firstColumn);
                this->set(this->get(i, secondColumn), i, firstColumn);
                this->set(temp, i, firstColumn);
            }
        }

        void swapLines(int firstLine, int secondLine) {
            T temp;
            for (int j = 0; j < this->columns; ++j) {
                temp = this->get(firstLine, j);
                this->set(this->get(secondLine, j), firstLine, j);
                this->set(temp, secondLine, j);
            }
        }

        bool isSquareMatrix() {
            return this->lines == this->columns;
        }

    public:
        RectangleMatrix operator+(const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.set(i, j, result.get(i, j) + B.get(i, j));
                }
            }
            return result;
        }

        RectangleMatrix operator-(const RectangleMatrix B) {
            RectangleMatrix result(*this);
            for (int i = 0; i < this->lines; ++i) {
                for (int j = 0; j < this->columns; ++j) {
                    result.set(i, j, result.get(i, j) - B.get(i, j));
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
                    this->set(B.get(i, j), i, j);
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
                            result.set(i, j,
                                       result.get(i, j) + (B.get(l, j) * this->get(i, l)));
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
                    result.set(i, j, result.get(i, j) * item);
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
                    os << std::setprecision(3) << rectangleMatrix1.get(i, j) << " ";
                }
                os << "\n";
            }
            return os;
        }
};