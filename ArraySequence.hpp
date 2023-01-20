#include <iostream>
#include <cstring>
#include "DynamicArray.hpp"

template<class T, class Iterator = typename DynamicArray<T>::ArrayIterator>
class ArraySequence : public Sequence<T, Iterator> {
    private:
        DynamicArray<T> *items;
    public:
        ArraySequence(T *items, int count) {
            auto *dynamicArray = new DynamicArray<T>(items, count);
            this->items = dynamicArray;
        }

        ArraySequence(T item, int count) {
            this->items = new DynamicArray<T>(item, count);
        }

        ArraySequence (int count) {
            this->items = new DynamicArray<T>(count);
        }

        explicit ArraySequence() {
            auto *newArray = new DynamicArray<T>();
            this->items = newArray;
        }

        explicit ArraySequence(ArraySequence<T, Iterator> *sequence) {
            auto *newArray = new DynamicArray<T>(sequence->items, sequence->getLength());
            this->items = newArray;
        }

        ~ArraySequence() {
            delete this->items;
        }

    public:
        Iterator begin() override {
            return this->items->begin();
        }

        Iterator end() override {
            return this->items->end();
        }

        Iterator rbegin() override {
            return this->items->rbegin();
        }

        Iterator rend() override {
            return this->items->rend();
        }

        Iterator getLastIterator() override {
            return this->items->getLastIterator();
        }

        Iterator getLastReversedIterator() override {
            return this->items->getLastReversedIterator();
        }
    public:
        const T& getFirst() override {
            return this->items->get(0);
        }

        const T& getLast() override {
            return this->items->get(items->getSize() - 1);
        }

        const T& get(int index) override {
            return this->items->get(index);
        }

        Sequence<T, Iterator>* getSubSequence(int startIndex, int endIndex) override {
            int size = this->items->getSize();
            if (endIndex >= startIndex && endIndex >= 0 && endIndex < size && startIndex >= 0 && startIndex < size) {
                auto *newSequence = new ArraySequence();
                int subArraySize = endIndex - startIndex + 1;
                auto *subArray = new DynamicArray<T>(endIndex - startIndex + 1);
                for (int i = 0; i < subArraySize; ++i) {
                    subArray->set(i, this->items->get(startIndex + i));
                }
                newSequence->items = subArray;
                return newSequence;
            } else {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
            }
        }

        int getLength() override {
            return this->items->getSize();
        }

    public:
        void deleteElement(int index) override {
            if (index < 0 || index >= this->items->getSize()) {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
            }

            for(int i = index; i < this->items->getSize() - 1; ++i) {
                this->items->set(i, this->items->get(i + 1));
            }

            this->items->setSize(this->items->getSize() - 1);
        }

        void set(int index, T item) override {
            this->items->set(index, item);
        }

        void append(T item) override {
            if (this->items->getSize() == this->items->getCapacity()) {
                this->items->resize(this->items->getSize() * 2);
                this->items->set(this->items->getSize(), item);
                this->items->setSize(this->items->getSize() + 1);
            } else {
                this->items->set(this->items->getSize(), item);
                this->items->setSize(this->items->getSize() + 1);
            }
        }

        void prepend(T item) override {
            if (this->items->getCapacity() == this->items->getSize()) {
                this->items->resize(this->items->getSize() + 1);
            }
            for (int i = this->items->getSize(); i > 0; --i) {
                this->items->set(i, this->items->get(i - 1));
            }
            this->items->set(0, item);
            this->items->setSize(this->items->getSize() + 1);
        }

        void insertAt(T item, int index) override {
            this->items->resize(this->items->getSize() + 1);
            this->items->setSize(this->items->getSize() + 1);
            for (int i = this->items->getSize() - 1; i > index; --i) {
                this->items->set(i, this->items->get(i - 1));
            }
            this->items->set(index, item);
        }

        Sequence<T, Iterator>* concat(Sequence<T, Iterator> *list) override {
            auto *newArraySequence = new ArraySequence;
            newArraySequence->items = new DynamicArray<T>(this->items->getSize() + list->getLength());
            for (int i = 0; i < this->items->getSize(); ++i) {
                newArraySequence->items->set(i, this->items->get(i));
                newArraySequence->items->setSize(newArraySequence->items->getSize() + 1);
            }
            for (int i = 0; i < list->getLength(); ++i) {
                newArraySequence->items->set(i + this->items->getSize(), list->get(i));
                newArraySequence->items->setSize(newArraySequence->items->getSize() + 1);
            }
            return newArraySequence;
        }

        Sequence<T, Iterator>* copy() override {
            auto *newArraySequence = new ArraySequence;
            for (int i = 0; i < this->getLength(); ++i) {
                newArraySequence->append(this->get(i));
            }
            return newArraySequence;
        }

        T& operator[] (int index) {
            return (*this->items)[index];
        }

        friend std::ostream& operator <<(std::ostream &os, ArraySequence arraySequence) {
            for (auto i = arraySequence.begin(); i < arraySequence.end(); ++i) {
                std::cout << *i << " ";
            }
            std::cout << "\n";
            return os;
        }
};
