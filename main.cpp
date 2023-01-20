#include <iostream>
#include "ErrorInfo.hpp"
#include "Iterators.hpp"
#include "Sequence.hpp"
#include "ArraySequence.hpp"
#include "ListSequence.hpp"
#include "MapWhereReduce.hpp"
#include "print.hpp"
#include <iomanip>
#include "RectangleMatrix.hpp"
#include "SquareMatrix.hpp"
#include "TriangleMatrix.hpp"
#include "ComplexNumbers.hpp"
#include "Options.hpp"
#include "RandEnter.hpp"
#include "Graph.hpp"
#include <variant>
#include <vector>

int main() {
    auto* graph = CreateTestGraph();
    std::cout << (*graph->getPath(2, 5)) << "\n";
    delete graph;
    return 0;
}
