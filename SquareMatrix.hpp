#include <iostream>
#include <cstring>
#include <cmath>

template <class T>
class SquareMatrix : public RectangleMatrix<T>{
    protected:
        size_t size = 0;
    public:
        SquareMatrix() = default;

        explicit SquareMatrix(int count) {
            T item;
            item = 0;
            this->lines = count;
            this->columns = count;
            this->size = count;
            this->rectangleMatrix = new DynamicArray<T>(count * count);
            for (int i = 0; i < count * count; ++i) {
                this->rectangleMatrix->set(i, item);
            }
            this->rectangleMatrix->setSize(count * count);
        }

        SquareMatrix(T* items, int count) {
            this->lines = count;
            this->columns = count;;
            this->rectangleMatrix = new DynamicArray<T>(items, count * count);
            for (int i = 0; i < count * count; ++i) {
                this->rectangleMatrix->set(i, items[i]);
            }
        }

        SquareMatrix(const SquareMatrix& matrix) {
            this->lines = matrix.lines;
            this->columns = matrix.columns;
            this->size = matrix.size;
            this->rectangleMatrix = new DynamicArray<T>(*matrix.rectangleMatrix);
        }
    public:
        int getSize() {
            return this->size;
        }
    public:
        SquareMatrix<T> operator+ (SquareMatrix<T> B) {
            if (this->lines == B.lines && this->columns == B.columns) {
                SquareMatrix<T> resultMatrix(*this);
                for (int i = 0; i < resultMatrix.size; ++i) {
                    for (int j = 0; j < resultMatrix.size; ++j) {
                        resultMatrix.set(i + 1, j + 1, this->get(i + 1, j + 1) + B.get(i + 1, j + 1));
                    }
                }
                return resultMatrix;
            }
            else {
                throw ErrorInfo(DifferentSizedMatricesCode, DifferentSizedMatricesMsg);
            }
        };

        SquareMatrix<T> operator- (const SquareMatrix<T> B) {
            if (this->lines == B.lines && this->columns == B.columns) {
                SquareMatrix<T> resultMatrix(*this);
                for (int i = 0; i < resultMatrix.size; ++i) {
                    for (int j = 0; j < resultMatrix.size; ++j) {
                        resultMatrix.set(i + 1, j + 1, this->get(i + 1, j + 1) - B.get(i + 1, j + 1));
                    }
                }
                return resultMatrix;
            }
            else {
                throw ErrorInfo(DifferentSizedMatricesCode, DifferentSizedMatricesMsg);
            }
        };

        SquareMatrix<T> operator* (SquareMatrix<T> B) {
            if (this->size == B.lines && this->size == B.columns) {
                SquareMatrix<T> resultMatrix(this->size);
                for (int i = 0; i < resultMatrix.size; ++i) {
                    for (int j = 0; j < resultMatrix.size; ++j) {
                        for (int l = 0; l < this->size; ++l) {
                            resultMatrix.set(i + 1, j + 1, resultMatrix.get(i + 1, j + 1) + (B.get(l + 1, j + 1) * this->get(i + 1, l + 1)));
                        }
                    }
                }
                return resultMatrix;
            }
            else {
                throw ErrorInfo(DifferentSizedMatricesCode, DifferentSizedMatricesMsg);
            }
        };

        SquareMatrix<T>& operator= (SquareMatrix<T> B) {
            if (this->lines == B.lines) {
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        this->set(B.get(i + 1, j + 1), i + 1, j + 1);
                    }
                }
            }
            else {
                delete this->rectangleMatrix;
                this->rectangleMatrix = new DynamicArray<T>(*B.rectangleMatrix);
                this->lines = B.lines;
                this->columns = B.columns;
            }
            return *this;
        };

        SquareMatrix<T>& operator= (RectangleMatrix<T> B) {
            if (B.isSquareMatrix() && this->lines == B.getLinesCount()) {
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        this->set(B.get(i + 1, j + 1), i + 1, j + 1);
                    }
                }
                return *this;
            }
            else if (!B.isSquareMatrix()) {
                throw ErrorInfo(NotSquareMatrixCode, NotSquareMatrixMsg);
            }
            else if (B.isSquareMatrix() && this->lines != B.getLinesCount()) {
                delete this->rectangleMatrix;
                this->rectangleMatrix = new DynamicArray<T>(B.getArrayCopy(), B.getLinesCount() * B.getColumnsCount());
                this->lines = B.getLinesCount();
                this->columns = B.getColumnsCount();
                for (int i = 0; i < this->lines; ++i) {
                    for (int j = 0; j < this->columns; ++j) {
                        this->set(B.get(i + 1, j + 1), i + 1, j + 1);
                    }
                }
                return *this;
            }
        };

        friend std :: ostream& operator<< (std :: ostream& os, SquareMatrix squareMatrix) {
            for (int i = 0; i < squareMatrix.lines; ++i) {
                for (int j = 0; j < squareMatrix.columns; ++j) {
                    std :: cout << std :: setprecision(3) << squareMatrix.get(i + 1, j + 1) << " ";
                }
                std :: cout << "\n";
            }
            return os;
        }
};
