template<class T>
class Graph {
    private:
        SquareMatrix<T> adjMatrix;
    public:
        Graph() = default;

        Graph(int num_of_columns) {
            adjMatrix = SquareMatrix(8);
        }

        ~Graph() = default;
    public:
        void flipEdge(int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeMsg, IndexOutOfRangeCode);
            adjMatrix.Set(weight, v2, v1);
            adjMatrix.Set(0, v1, v2);
        }

        void changeEgde(T weight, int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeMsg, IndexOutOfRangeCode);
            adjMatrix.Set(weight, v1, v2);    
        }

        void printGraph() {
            std::cout << adjMatrix;
        }

        size_t getSize() {
            return adjMatrix->GetSize();
        }

        T getWeight(int v1, v2) {
            return adjMatrix->Get(v1, v2);
        }

        ArraySequence<int>* getPath(int v1, int v2) {
            ArraySequence<int> distance(getSize());
            ArraySequence<bool> visited(getSize());
            ArraySequence<int> parents(getSize());
            int max = 100000000;

            

            for(int i = 0; i < getSize(); i++) {
                distance.set(max, i);
                visited.set(false, i);
                parents.set(-1, i);
            }

            int min = 0;
            int index_min = 0;
            int temp = 0;
            distance.set(0, v1);

            for(int i = 0; i < getSize(); i++) {
                min = max;
                for(int j = 0; j < getSize(); ++j) {
                    if(!(visited.get(j)) && distance.get(j) < min)
                    {
                        min = distance.get(j);
                        index_min = j;
                    }
                }
                visited.set(true, index_min);
                for (int j = 0; j < getSize(); ++j) {
                    if (adjMatrix->Get(index_min, j) > 0) {
                        temp = min + adjMatrix->Get(index_min, j);

                        if (temp < distance.get(j)) {
                            distance.set(temp, j);
                            parents.set(index_min, j);
                        }
                    }
                }
                if (visited.get(v2) == true)
                    break;
            }
            ArraySequence<int>* path = new ArraySequence<int>(0);
            if (parents.get(v2) == -1) {
                path->append(-1);
                return path;
            }
            for(int i = v2; i != -1; i = parents.get(i))
                path->prepend(i);
            return path;
        }

        T getPathWeight(const ArraySequence<int>& path) {
            
        }    
};