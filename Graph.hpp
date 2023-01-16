template<class T>
class Graph {
    private:
        SquareMatrix<T> adjMatrix;

        void dfs(int v, ArraySequence<bool>* visited, ArraySequence<int>* stack) {
            visited[v] = true;
            for (int i = 0; i < this->getSize(); ++i) {
                if (!visited[i])
                    dfs(i, visited, stack);
            }
            stack->prepend(v);
        }
    public:
        Graph() = default;

        Graph(int num_of_columns) {
            this->adjMatrix = SquareMatrix<T>(8);
        }

        ~Graph() = default;
    public:
        void flipEdge(int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeMsg, IndexOutOfRangeCode);
            this->adjMatrix.set(getWeight(), v2, v1);
            this->adjMatrix.set(0, v1, v2);
        }

        void changeEgde(T weight, int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeMsg, IndexOutOfRangeCode);
            this->adjMatrix.set(weight, v1, v2);    
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
};