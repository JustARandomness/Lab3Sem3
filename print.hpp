#include <iostream>
#include <cstring>

template <class T>
void PrintSequence(Sequence<T>* sequence) {
    for (int i = 0; i < sequence->GetLength(); ++i) {
        std :: cout << "Sequence[" << i << "] = " <<sequence->Get(i) << "\n";
    }
}