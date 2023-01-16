#include <iostream>
#include <cstring>

int RandEnterInt() {
	return rand() % 100 + 1;
}

double RandEnterDouble() {
	return double(rand() % 2000) / 1000 + rand() % 10;
}

ComplexNumber<int> RandEnterComplexInt() {
	ComplexNumber<int> item;
	item.SetRealPart(rand() % 100 + 1);
	item.SetImaginaryPart(rand() % 100 + 1);
	return item;
}

ComplexNumber<double> RandEnterComplexDouble() {
	ComplexNumber<double> item;
	item.SetRealPart(double(rand() % 2000) / 1000 + rand() % 10);
	item.SetImaginaryPart(double(rand() % 2000) / 1000 + rand() % 10);
	return item;
}