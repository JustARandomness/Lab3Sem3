#include <iostream>
#include <cstring>

template <class T>
class LinkedList {
    public:
        class LinkedListIterator;
    private:
        class LinkedListNode {
            private:
                LinkedListNode* pPrev = nullptr;
                LinkedListNode* pNext = nullptr;
                T data;
            public:
                explicit LinkedListNode(): pPrev(nullptr), pNext(nullptr), data(T())
                {

                };

                const T& getData() {
                    return this->data;
                }

                void setData(T item) {
                    this->data = item;
                }

                LinkedListNode* getNext() {
                    return this->pNext;
                }

                void setNext(LinkedListNode* element) {
                    this->pNext = element;
                };

                LinkedListNode* getPrev() {
                    return this->pPrev;
                }

                void setPrev(LinkedListNode* element) {
                    this->pPrev = (LinkedListNode*)element;
                };

                friend LinkedListIterator;
        };

        int listSize = 0;

        LinkedListNode* first = nullptr;

        LinkedListNode* last = nullptr;
    public:
        class LinkedListIterator : public BaseIterator<T> {
            public:
                LinkedListNode* element = nullptr;
                bool isReversed = false;
                int counter;
                int list_size;
                int Tag = BidirectionalIterator;
            public:
                explicit LinkedListIterator(LinkedListNode* node, bool is_reversed, int _counter, int _list_size) {
                    this->element = node;
                    this->isReversed = is_reversed;
                    this->counter = _counter;
                    this->list_size = _list_size;
                }
            public:
                int getTag() {
                    return this->Tag;
                }

                int getContainerSize() {
                    return this->list_size;
                }

                int getCounter() {
                    return this->counter;
                }

                LinkedListIterator& operator++() {
                    if (this->isReversed) {
                        this->element = this->element->getPrev();
                        this->counter--;
                    }
                    else {
                        this->element = this->element->getNext();
                        this->counter++;
                    }
                    return *this;
                }

                LinkedListIterator& operator--() {
                    if (this->isReversed) {
                        this->element = this->element->getNext();
                        this->counter++;
                    }
                    else {
                        this->element = this->element->getPrev();
                        this->counter--;
                    }
                    return *this;
                }

                LinkedListIterator operator--(int) {
                    LinkedListIterator current = *this;
                    --(*this);
                    return current;
                }

                LinkedListIterator operator++(int) {
                    LinkedListIterator current = *this;
                    ++(*this);
                    return current;
                }

                LinkedListIterator& advance(int steps) {
                    int i = 0;
                    while (this->element != nullptr && i < steps) {
                        ++(*this);
                        ++i;
                    }
                    return *this;
                }

                LinkedListIterator operator+(int num) {
                    LinkedListIterator current = *this;
                    int i = 0;
                    if (num > 0) {
                        if (this->isReversed) {
                            while (current.element && i < num) {
                                current.element = current.element->getPrev();
                                current.counter--;
                                ++i;
                            }
                        } else {
                            while (current.element && i < num) {
                                current.element = current.element->getNext();
                                current.counter++;
                                ++i;
                            }
                        }
                    }
                    else {
                        if (this->isReversed) {
                            while (current.element && i > num) {
                                current.element = current.element->getNext();
                                current.counter++;
                                --i;
                            }
                        } else {
                            while (current.element && i > num) {
                                current.element = current.element->getPrev();
                                current.counter--;
                                --i;
                            }
                        }
                    }
                    return current;
                }

                bool operator==(const LinkedListIterator& iterator) const {
                    return this->element == iterator.element;
                }

                bool operator!=(const LinkedListIterator& iterator) const {
                    return this->element != iterator.element;
                }

                bool operator<(const LinkedListIterator& iterator) {
                    if (isReversed)
                        return this->counter > iterator.counter;
                    return this->counter < iterator.counter;
                }

                bool operator<=(const LinkedListIterator& iterator) {
                    if (isReversed)
                        return this->counter >= iterator.counter;
                    return this->counter <= iterator.counter;
                }

                bool operator>(const LinkedListIterator& iterator) {
                    if (isReversed)
                        return this->counter < iterator.counter;
                    return this->counter > iterator.counter;
                }

                bool operator>=(const LinkedListIterator& iterator) {
                    if (isReversed)
                        return this->counter <= iterator.counter;
                    return this->counter >= iterator.counter;
                }

                T& operator* () {
                    return this->element->data;
                }
        };
    public:
        LinkedList(T* items, int count) {
            this->listSize = count;
            auto* prev = new LinkedListNode;
            this->first = prev;
            prev->setPrev(nullptr);
            prev->setData(items[0]);
            for (int i = 1; i < count; ++i) {
                auto* next = new LinkedListNode;

                next->setPrev(prev);
                prev->setNext(next);
                next->setData(items[i]);

                prev = next;
                this->last = next;
                next->setNext(nullptr);
            }
        }

        LinkedList() : first(nullptr), last(nullptr), listSize(0){};

        LinkedList(const LinkedList<T>& list) {
            this->listSize = list.listSize;
            auto* prev_element = new LinkedListNode();
            LinkedListNode* element = list.first;
            int count = list.getLength();

            this->first = prev_element;
            prev_element->setData(element->getData());
            element = element->getNext();
            this->last = this->first;
            for (int i = 1; i < count; ++i) {
                auto *next_element = new LinkedListNode();

                prev_element->setNext(next_element);
                next_element->setPrev(prev_element);
                next_element->setData(element->getData());

                prev_element = prev_element->getNext();
                element = element->getNext();
                this->last = next_element;
                next_element->setNext(nullptr);
            }
        };

        ~LinkedList() {
            auto* prev_element = this->first;
            if (prev_element != nullptr) {
                auto *next_element = prev_element->getNext();
                while (next_element != nullptr) {
                    next_element = prev_element->getNext();
                    delete prev_element;
                    prev_element = next_element;
                }
                delete prev_element;
            }
        }
    public:
        LinkedListIterator begin() {
            return LinkedListIterator(this->first, false, 0, this->listSize);
        }

        LinkedListIterator end() {
            return LinkedListIterator(nullptr, false, this->listSize, this->listSize);
        }

        LinkedListIterator rbegin() {
            return LinkedListIterator(this->last, true, this->listSize - 1, this->listSize);
        }

        LinkedListIterator rend() {
            return LinkedListIterator(nullptr, true, -1, this->listSize);
        }

        LinkedListIterator getLastIterator() {
            return LinkedListIterator(this->last, false, this->listSize - 1, this->listSize);
        }

        LinkedListIterator getLastReversedIterator() {
            return LinkedListIterator(this->first, true, 0, this->listSize);
        }
    public:
        int getLength() const{
            return this->listSize;
        }
        LinkedListNode* getFirst() {
            if (!this) {
                throw ErrorInfo(NoListCreatedCode, NoListCreatedMsg);
                return nullptr;
            }

            return this->first;
        }

        LinkedListNode* getLast() {
            if (!this) {
                throw ErrorInfo(NoListCreatedCode, NoListCreatedMsg);
                return nullptr;
            }

            return this->last;
        }

        LinkedListNode* get(int index) {
            if (index >= 0 && index < this->getLength()) {
                LinkedListNode* element = this->first;
                int counter = 0;
                while (counter != index) {
                    element = element->getNext();
                    ++counter;
                }
                return element;
            }
            else {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
                return nullptr;
            }
        }

        LinkedList<T>* getSubList(int startIndex, int endIndex) {
            if (startIndex < 0 || startIndex >= this->getLength() || endIndex < 0 || endIndex >= this->getLength()) {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
                return nullptr;
            }

            LinkedListNode* element = this->first;
            int counter = 0;
            T* items = new T [endIndex - startIndex + 1];

            while (counter != startIndex) {
                element = element->getNext();
                ++counter;
            }

            for (int i = startIndex; i <= endIndex; ++i) {
                items[i - startIndex] = element->getData();
                element = element->getNext();
            }

            auto* subList = new LinkedList(items, endIndex - startIndex + 1);
            delete [] items;
            return subList;
        }
    public:
        void deleteElement (int index) {
            if (index < 0 || index >= this->getLength()) {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
            }

            LinkedListNode* element = this->get(index);
            LinkedListNode* nextElement = element->getNext();
            LinkedListNode* prevElement = element->getPrev();

            int length = this->getLength();
            if (length == 1) {
                delete element;
                this->first = nullptr;
                this->last = nullptr;
            }
            else {
                if (index == 0) {
                    delete element;
                    this->first = nextElement;
                    nextElement->setPrev(nullptr);
                }
                else if (index == length - 1) {
                    delete element;
                    this->last = prevElement;
                    prevElement->setNext(nullptr);
                }
                else {
                    delete element;
                    prevElement->setNext(nextElement);
                    nextElement->setPrev(prevElement);
                }
            }
            this->listSize--;
        }

        void append(const T& item) {
            LinkedListNode* old_last;

            LinkedListNode* new_last = new LinkedListNode();

            new_last->setData(item);
            new_last->setPrev(this->last);
            new_last->setNext(nullptr);

            old_last = new_last->getPrev();
            if (old_last != nullptr)
                old_last->setNext(new_last);
            else
                this->first = new_last;

            this->last = new_last;
            this->listSize++;
        }

        void prepend(T item) {
            auto* new_element = new LinkedListNode;

            new_element->setData(item);
            new_element->setPrev(nullptr);
            new_element->setNext(this->first);
            if (this->first != nullptr)
                this->first->setPrev(new_element);
            else
                this->last = new_element;
            this->first = new_element;
            this->listSize++;
        }

        void insertAt(T item, int index) {
            if (!this) {
                throw ErrorInfo(NoListCreatedCode, NoListCreatedMsg);
                return;
            }

            if (index < 0 || index >= this->getLength()) {
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
                return;
            }

            LinkedListNode* nextElement = this->first;
            int counter = 0;
            while (counter != index) {
                nextElement = nextElement->getNext();
                ++counter;
            }

            LinkedListNode* prevElement = nextElement->getPrev();
            auto* newElement = new LinkedListNode;

            newElement->setData(item);
            newElement->setNext(nextElement);
            newElement->setPrev(prevElement);

            nextElement->setPrev(newElement);
            prevElement->setNext(newElement);
            this->listSize++;
        }

        LinkedList<T>* concat(LinkedList<T>* list) {
            auto* new_list = new LinkedList<T> (*this);
            auto* prev_element = new LinkedListNode;
            LinkedListNode* element = this->first;
            prev_element->setData(element->getData());
            new_list->first = prev_element;
            element = element->getNext();
            int count = this->getLength();
            for (int i = 1; i < count; ++i) {
                auto *next_element = new LinkedListNode;

                prev_element->setNext(next_element);
                next_element->setPrev(prev_element);
                next_element->setData(element->getData());

                prev_element = prev_element->getNext();
                element = element->getNext();
                new_list->last = next_element;
                next_element->setNext(nullptr);
            }

            count = list->getLength();
            element = list->first;

            for (int i = 0; i < count; ++i) {
                auto* next_element = new LinkedListNode;

                prev_element->setNext(next_element);
                next_element->setPrev(prev_element);
                next_element->setData(element->getData());

                prev_element = prev_element->getNext();
                element = element->getNext();
                new_list->last = next_element;
                next_element->setNext(nullptr);
            }
            new_list->listSize += list->listSize;
            return new_list;
        }
};
