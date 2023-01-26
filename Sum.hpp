#include <iostream>
#include <cmath>

int GetSum(int item) {
    int result = 0;
    for (int i = item; i > 0; --i) {
        result += i;
    }
    return result;
}