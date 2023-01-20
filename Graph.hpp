template<class T>
class Graph {
    private:
        SquareMatrix<T>* adjMatrix = nullptr;

        enum ColourToInt {white, gray, black};

        bool isCyclic(int v, ArraySequence<ColourToInt>& colour) {
            if (colour[v] == gray) {
                return true;
            }
            colour[v] = gray;
            int size = this->getSize();
            for (int i = 0; i < size; ++i) 
            {
                if (i != v && this->adjMatrix->get(v + 1, i + 1) != 0) {
                    if (isCyclic(i, colour)) {
                        return true;
                    }
                }
            }
            colour[v] = black;
            return false;
        }

        void dfs(int v, ArraySequence<bool>* visited, ArraySequence<int>* stack) {
            (*visited)[v] = true;
            int size = this->getSize();
            for (int i = 0; i < size; ++i) {
                if (!(*visited)[i] && this->adjMatrix->get(v + 1, i + 1) != 0)
                    dfs(i, visited, stack);
            }
            stack->prepend(v + 1);    
        }

        
    public:
        Graph(int num_of_columns = 6) {
            this->adjMatrix = new SquareMatrix<T>(num_of_columns);
        }

        ~Graph() {
            delete adjMatrix;
        };
    public:
        void flipEdge(int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeMsg, IndexOutOfRangeCode);
            this->adjMatrix.set(getWeight(), v2, v1);
            this->adjMatrix.set(0, v1, v2);
        }

        void changeEgde(T weight, int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
            this->adjMatrix->set(weight, v1, v2);    
        }

        void printGraph() {
            std::cout << this->adjMatrix;
        }

        size_t getSize() {
            return this->adjMatrix->getSize();
        }

        T getWeight(int v1, int v2) {
            return this->adjMatrix->get(v1, v2);
        }

        bool isCyclic() {
            auto colour = ArraySequence<ColourToInt>(white, this->getSize());
            for (int i = 0; i < this->getSize(); ++i) {
                if (isCyclic(i, colour)) {
                    return true;
                }
            }
            return false;
        }

        ArraySequence<T>* topologicalSort() {
            if (!this->isCyclic()) {
                auto* visited = new ArraySequence<bool>(false, this->getSize());
                auto* stack = new ArraySequence<int>(0);
                for (int i = 0; i < this->getSize(); ++i) {
                    if (!((*visited)[i]))
                        dfs (i, visited, stack);
                }
                delete visited;
                return stack;
            }
            return nullptr;
                    
        }

        friend std::ostream& operator<<(std::ostream& os, Graph<T> g) {
            int size = g.getSize();
            for (int i = 0; i < size; ++i) {
                os << i + 1 << " : { ";
                for (int j = 0; j < size; ++j) {
                    if (g.adjMatrix->get(i + 1, j + 1) != 0)
                        os << j + 1 << ' ';
                }
                os << "};\n";
            }
            return os;
        }
};



Graph<int>* CreateTestGraph() {
    auto* graph = new Graph<int>(6);
    graph->changeEgde(3, 1, 5);
    graph->changeEgde(2, 2, 1);
    graph->changeEgde(8, 3, 1);
    graph->changeEgde(6, 3, 2);
    graph->changeEgde(5, 4, 2);
    graph->changeEgde(3, 6, 2);
    graph->changeEgde(4, 3, 4);
    graph->changeEgde(9, 3, 5);
    graph->changeEgde(2, 4, 6);
    graph->changeEgde(1, 6, 5);
    return graph;
};