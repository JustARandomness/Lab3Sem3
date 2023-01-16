cmake_minimum_required(VERSION 3.24)
project(Lab3Sem3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Lab3Sem3 main.cpp Graph.hpp ErrorInfo.hpp DynamicArray.hpp LinkedList.hpp ArraySequence.hpp ListSequence.hpp Sequence.hpp MapWhereReduce.hpp print.hpp SquareMatrix.hpp RectangleMatrix.hpp TriangleMatrix.hpp ComplexNumbers.hpp Options.hpp RandEnter.hpp)
