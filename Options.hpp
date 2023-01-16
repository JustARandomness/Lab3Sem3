#include <iostream>
#include <cstring>

void PrintMatrixOptions() {
	std::cout << "What matrix would you like to work with?\n\n";
	std::cout << "1. Rectangle matrix\n";
	std::cout << "2. Square matrix\n";
	std::cout << "3. Triangle matrix\n";
}

void NumberTypeOptions() {
	std::cout << "What type of numbers you want to work with?\n\n";
	std::cout << "1. Integer numbers\n";
	std::cout << "2. Real numbers\n";
	std::cout << "3. Complex numbers\n";
}

void ComplexNumberTypeOptions() {
	std::cout << "1. Integer numbers\n";
	std::cout << "2. Real numbers\n";
}

void RandEnterOptions() {
	std::cout << "1. Random input\n";
	std::cout << "2. Input with keyboard\n";
}

void PrintMenuRectangleAndSquareMatrixOptions() {
	std::cout << "1. Multiply line by number\n";
	std::cout << "2. Multiply column by number\n";
	std::cout << "3. Swap lines\n";
	std::cout << "4. Swap columns\n";
	std::cout << "5. Print matrix\n";
	std::cout << "6. End program\n";
}