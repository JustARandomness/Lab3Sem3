template <class T, class Iterator = BaseIterator<T>>
class Sequence {
    public:
        virtual const T& getFirst() = 0;
        virtual const T& getLast() = 0;
        virtual const T& get(int index) = 0;
        virtual Sequence<T, Iterator>* getSubSequence(int startIndex, int endIndex) = 0;
        virtual int getLength() = 0;
    public:

    public:
        virtual Iterator begin() = 0;
        virtual Iterator end() = 0;
        virtual Iterator rbegin() = 0;
        virtual Iterator rend() = 0;
        virtual Iterator getLastIterator() = 0;
        virtual Iterator getLastReversedIterator() = 0;
        virtual void deleteElement(int index) = 0;
        virtual void set(int index, T item) = 0;
        virtual void append(T item) = 0;
        virtual void prepend(T item) = 0;
        virtual void insertAt(T item, int index) = 0;
        virtual Sequence<T, Iterator>* concat(Sequence<T, Iterator>* list) = 0;
        virtual Sequence<T, Iterator>* copy() = 0;
};
