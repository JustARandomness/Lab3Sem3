#include "LinkedList.hpp"
#include <iostream>
#include <cstring>

template <class T, class Iterator = typename LinkedList<T>::LinkedListIterator>
class ListSequence : public Sequence<T, Iterator> {
    private:
        LinkedList<T>* linkedList;
    public:
        ListSequence(T* items, int count) {
            auto* list = new LinkedList<T> (items, count);
            this->linkedList = list;
        }

        ListSequence() {
            auto* list = new LinkedList<T> ();
            this->linkedList = list;
        }

        explicit ListSequence(const LinkedList<T>& sequence) {
            auto* newList = new LinkedList<T> (sequence);
            this->linkedList = newList;
        }
    public:
        Iterator begin() override {
            return this->linkedList->begin();
        }

        Iterator end() override {
            return this->linkedList->end();
        }

        Iterator rbegin() override {
            return this->linkedList->rbegin();
        }

        Iterator rend() override {
            return this->linkedList->rend();
        }

        Iterator getLastIterator() {
            return this->linkedList->getLastIterator();
        }

        Iterator getLastReversedIterator() override {
            return this->linkedList->getLastReversedIterator();
        }
    public:
        const T& getFirst() override {
            return this->linkedList->getFirst()->getData();
        }

        const T& getLast() override{
            return this->linkedList->getLast()->getData();
        }

        const T& get(int index) override {
            return (this->linkedList->get(index))->getData();
        }

        Sequence<T, Iterator>* getSubSequence(int startIndex, int endIndex) {
            auto* newListSequence = new ListSequence;
            newListSequence->linkedList = this->linkedList->getSubList(startIndex, endIndex);
            return newListSequence;
        }

        int getLength() override {
            return this->linkedList->getLength();
        }
    public:
        void deleteElement (int index) override{
            this->linkedList->deleteElement(index);
        }

        void set (int index, T item) override{
            (this->linkedList->get(index))->setData(item);
        }

        void append(T item) override {
            this->linkedList->append(item);
        }

        void prepend(T item) override{
            this->linkedList->prepend(item);
        }

        void insertAt(T item, int index) override {
            this->linkedList->insertAt(item, index);
        }
        Sequence<T, Iterator>* concat(Sequence<T, Iterator>* list) override {
            auto* newListSequence = new ListSequence;
            int size = this->linkedList->getLength();
            for (int i = 0; i < size; ++i) {
                newListSequence->linkedList->append(this->linkedList->get(i)->getData());
            }
            size = list->getLength();
            for (int i = 0; i < size; ++i) {
                newListSequence->linkedList->append(list->get(i));
            }
            return newListSequence;
        }

        Sequence<T, Iterator>* copy() override {
            auto* newListSequence = new ListSequence;
            for (int i = 0; i < this->getLength(); ++i) {
                newListSequence->append(this->get(i));
            }
            return newListSequence;
        }

        T& operator[] (int index) {
            return this->get(index);
        }

        friend std::ostream& operator<< (std::ostream& os, ListSequence listSequence) {
            for (auto i = listSequence.begin(); i < listSequence.end(); ++i) {
                std::cout << *i << " ";
            }
            std::cout << "\n";
            return os;
        }
};
