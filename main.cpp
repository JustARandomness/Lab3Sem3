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
#include "ComplexNumbers.hpp"
#include "Options.hpp"
#include "RandEnter.hpp"
#include "Graph.hpp"
#include <variant>
#include <vector>
#include "Test.hpp"

int main() {
    auto graph = CreateTestGraph();
    std::cout << graph << '\n';
    std::cout << "Topological sort:\n" << graph.topologicalSort() << "\n\n";
    std::cout << "Ford Bellman:\n";
    for (int i = 0; i < graph.getSize(); ++i) {
        std::cout << graph.fordBellman(i);
    }
    std::cout << "Path between vertexes 2 and 4:\n\n" << graph.getPath(2, 4) << "\n";
    std::cout << "Floyd:\n" << graph.floyd();
    Test();
    return 0;
}
