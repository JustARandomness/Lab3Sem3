int max = 100000000;

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

        ArraySequence<T>* dijkstra(int v, ArraySequence<int>& parent) {
            auto* distance = new ArraySequence<T>(max, this->getSize());
            ArraySequence<bool> visited(false, this->getSize());
            (*distance)[v - 1] = 0;
            for (int i = 0; i < this->getSize(); ++i) {
                int s = -1;
                for (int j = 0; j < this->getSize(); ++j) {
                    if (!visited[j] && (s == -1 || (*distance)[j] < (*distance)[s])) {
                        s = j;
                    }
                }
                if ((*distance)[s] == max) {
                    break;
                }
                visited[s] = true;
                for (int j = 0; j < this->getSize(); ++j) {
                    if (this->adjMatrix->get(s + 1, j + 1) != 0) {
                        int to = j;
                        int len = this->adjMatrix->get(s + 1, j + 1);
                        if ((*distance)[s] + len < (*distance)[to]) {
                            (*distance)[to] = (*distance)[s] + len;
                            parent[to] = s;
                        }
                    }
                }
            }
            return distance;
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

        ArraySequence<int>* getPath(int v1, int v2) {
            ArraySequence<int> parent(-1, this->getSize());
            auto* path = new ArraySequence<int>(0);
            auto* distance = dijkstra(v1, parent);
            if ((*distance)[v2 - 1] != max) {
                for (int v = v2 - 1; v != v1 - 1; v = parent[v]) {
                    path->prepend(v + 1);
                }
                path->prepend(v1);
                return path;
            }
            delete distance;
            delete path;
            std::cout << "No path found\n";
            return nullptr;
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