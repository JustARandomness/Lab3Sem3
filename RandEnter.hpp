#include <iostream>
#include <cstring>

int RandEnterInt() {
	return rand() % 100 + 1;
}

double RandEnterDouble() {
	return double(rand() % 2000) / 1000 + rand() % 10;
}
