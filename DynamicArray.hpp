#include <iostream>
#include <cstring>

template <class T>
class DynamicArray {
    private :
        T* array = nullptr;
        int size = 0;
        int capacity = 0;
    public:
        class ArrayIterator : public BaseIterator<T> {
            public:
                T* element = nullptr;
                bool isReversed = false;
                int counter = 0;
                int array_size = 0;
                int Tag = RandomAccessIterator;
            public:
                explicit ArrayIterator(T* element, bool is_reversed, int _array_size, int _counter = 0) {
                    this->element = element;
                    this->isReversed = is_reversed;
                    this->array_size = _array_size;
                    this->counter = _counter;
                }
            public:
                int getTag() {
                    return this->Tag;
                }

                int getContainerSize() {
                    return this->array_size;
                }

                int getCounter() {
                    return this->counter;
                }

                ArrayIterator& operator++() {
                    if (this->isReversed) {
                        if (this->counter > 0) {
                            this->element -= 1;
                            --counter;
                        }
                        else {
                            this->element -= 1;
                            --counter;
                            this->element = nullptr;
                        }
                    }
                    else {
                        if (this->counter < this->array_size - 1) {
                            this->element += 1;
                            ++counter;
                        }
                        else {
                            this->element += 1;
                            ++counter;
                            this->element = nullptr;
                        }
                    }

                    return *this;
                }

                ArrayIterator& operator--() {
                    if (this->isReversed) {
                        if (this->counter < this->array_size) {
                            this->element += 1;
                            ++counter;
                        }
                        else {
                            this->element += 1;
                            ++counter;
                            this->element = nullptr;
                        }
                    }
                    else {
                        if (this->counter > 0) {
                            this->element -= 1;
                            --counter;
                        }
                        else {
                            this->element -= 1;
                            --counter;
                            this->element = nullptr;
                        }
                    }

                    return *this;
                }

                ArrayIterator operator--(int) {
                    ArrayIterator current = *this;
                    --(*this);
                    return current;
                }

                ArrayIterator operator++(int) {
                    ArrayIterator current = *this;
                    ++(*this);
                    return current;
                }

                ArrayIterator& advance(int steps) {
                    if (this->isReversed) {
                        this->element -= steps;
                        this->counter -= steps;
                        if (this->counter < 0) {
                            this->element = nullptr;
                            this->counter = -1;
                        }
                        else if (this->counter >= array_size) {
                            this->element = nullptr;
                            this->counter = this->array_size;
                        }
                    }
                    else {
                        this->element += steps;
                        this->counter += steps;
                        if (this->counter < 0) {
                            this->element = nullptr;
                            this->counter = -1;
                        } else if (this->counter >= array_size) {
                            this->element = nullptr;
                            this->counter = this->array_size;
                        }
                    }
                    return *this;
                }

                ArrayIterator& operator+=(int steps) {
                    return this->advance(steps);
                }

                ArrayIterator& operator-=(int steps) {
                    return this->advance(-steps);
                }

                bool operator<(const ArrayIterator& iterator) {
                    if (isReversed)
                        return this->counter > iterator.counter;
                    return this->counter < iterator.counter;
                }

                bool operator<=(const ArrayIterator& iterator) {
                    if (isReversed)
                        return this->counter >= iterator.counter;
                    return this->counter <= iterator.counter;
                }

                bool operator>(const ArrayIterator& iterator) {
                    if (isReversed)
                        return this->counter < iterator.counter;
                    return this->counter > iterator.counter;
                }

                bool operator>=(const ArrayIterator& iterator) {
                    if (isReversed)
                        return this->counter <= iterator.counter;
                    return this->counter >= iterator.counter;
                }

                bool operator==(const ArrayIterator& iterator) const {
                    return this->counter == iterator.counter;
                }

                bool operator!=(const ArrayIterator& iterator) const {
                    return this->counter != iterator.counter;
                }

                ArrayIterator operator+(int num) {
                    ArrayIterator current = *this;
                    current += num;
                    return current;
                }

                ArrayIterator operator- (int num) {
                    ArrayIterator current = *this;
                    current -= num;
                    return current;
                }

                T& operator* () {
                    return *(this->element);
                }
        };
    public:
        ArrayIterator begin() {
            return ArrayIterator(&(this->array[0]), false, this->size);
        }

        ArrayIterator end() {
            return ArrayIterator(nullptr, false, this->size, this->size);
        }

        ArrayIterator rbegin() {
            return ArrayIterator(&(this->array[this->size - 1]), true, this->size, this->size - 1);
        }

        ArrayIterator rend() {
            return ArrayIterator(nullptr, true, this->size, -1);
        }

        ArrayIterator getLastIterator() {
            return ArrayIterator(&(this->array[this->size - 1]), false, this->size, this->size - 1);
        }

        ArrayIterator getLastReversedIterator() {
            return ArrayIterator(&(this->array[0]), true, this->size);
        }
    public:
        DynamicArray(T* items, int count) {
            this->array = new T [count];
            this->size = count;
            this->capacity = count;
            memcpy(this->array, items, sizeof(T) * count);
        }

        DynamicArray() = default;

        explicit DynamicArray(int count, int _size = 0):size(_size) {
            auto* newArray = new T [count];
            this->array = newArray;
            this->capacity = count;
        }

        DynamicArray(T item, int _size) {
            
        }

        DynamicArray(const DynamicArray<T>& dynamicArray) {
            auto* new_array = new T [dynamicArray.capacity];
            this->array = new_array;
            this->size = dynamicArray.size;
            this->capacity = dynamicArray.capacity;
            for (int i = 0; i < this->size; ++i) {
                this->array[i] = dynamicArray.array[i];
            }
        }

        ~DynamicArray() {
            delete [] this->array;
        }
    public:
        const T& get(int index) {
            if (!this->array) {
                throw ErrorInfo(NoArrayCreatedCode, NoArrayCreatedMsg);
            }

            if (index < 0 || index >= this->size) {
                throw ErrorInfo(NoArrayCreatedCode, NoArrayCreatedMsg);
            }

            return this->array[index];
        }
        int getSize() {
            return this->size;
        }

        int getCapacity() {
            return this->capacity;
        }
    public:
        void set(int index, T value) {
            if (!this->array) {
                throw ErrorInfo(NoListCreatedCode, NoListCreatedMsg);
            }

            if (index < 0 || (index >= this->size && this->size == this->capacity)) {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
            }

            this->array[index] = value;
        }

        void resize(int NewSize) {
            T* buffer_array = new T [this->size];
            memcpy(buffer_array, this->array, sizeof(T) * this->size);
            int oldSize = this->size;
            delete[] this->array;
            if (oldSize < NewSize) {
                this->array = new T [NewSize];
                this->capacity = NewSize;
                this->size = oldSize;
                for (int i = 0; i < oldSize; ++i) {
                    this->array[i] = buffer_array[i];
                }
            }
            else {
                this->array = new T[NewSize];
                this->size = NewSize;
                this->capacity = NewSize;
                for (int i = 0; i < NewSize; ++i) {
                    this->array[i] = buffer_array[i];
                }
            }
            delete[] buffer_array;
        }

        void setSize(int NewSize) {
            this->size = NewSize;
        }
    public:
        T& operator[] (int index) {
            return this->array[index];
        }
};
