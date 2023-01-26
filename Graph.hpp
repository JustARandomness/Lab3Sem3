#include <queue>

int max = 1000000000;

template<class T>
class Graph {
    private:
        SquareMatrix<T> adjMatrix;

        enum ColourToInt {white, gray, black};

        bool isCyclic(int v, ArraySequence<ColourToInt>& colour) {
            if (colour[v] == gray) {
                return true;
            }
            colour[v] = gray;
            int size = this->getSize();
            for (int i = 0; i < size; ++i) {
                if (i != v && this->adjMatrix.get(v, i) != 0) {
                    if (isCyclic(i, colour)) {
                        return true;
                    }
                }
            }
            colour[v] = black;
            return false;
        }

        void dfs(int v, ArraySequence<bool>& visited, ArraySequence<int>& stack) {
            visited[v] = true;
            int size = this->getSize();
            for (int i = 0; i < size; ++i) {
                if (!visited[i] && this->adjMatrix.get(v, i) != 0) {
                    dfs(i, visited, stack);
                }
            }
            stack.prepend(v);    
        }

        ArraySequence<T> dijkstra(int v, ArraySequence<int>& parent) {
            ArraySequence<T> distance(max, this->getSize());
            ArraySequence<bool> visited(false, this->getSize());
            distance[v] = 0;
            for (int i = 0; i < this->getSize(); ++i) {
                int s = -1;
                for (int j = 0; j < this->getSize(); ++j) {
                    if (!visited[j] && (s == -1 || distance[j] < distance[s])) {
                        s = j;
                    }
                }
                if (distance[s] == max) {
                    break;
                }
                visited[s] = true;
                for (int j = 0; j < this->getSize(); ++j) {
                    if (this->adjMatrix.get(s, j) != 0) {
                        int to = j;
                        int len = this->adjMatrix.get(s, j);
                        if (distance[s] + len < distance[to]) {
                            distance[to] = distance[s] + len;
                            parent[to] = s;
                        }
                    }
                }
            }
            return distance;
        }
    public:
        Graph(int num_of_columns = 6) {
            this->adjMatrix = SquareMatrix<T>(num_of_columns);
        }

        ~Graph() = default;
    public:
        void flipEdge(int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeMsg, IndexOutOfRangeCode);
            this->adjMatrix.set(this->getWeight(), v2, v1);
            this->adjMatrix.set(0, v1, v2);
        }

        // ArraySequence<int> bfs(int v) {
        //     std::queue<int> q;
        //     q.push(v);
        //     while (!q.empty()) {
        //         int s = q.front();
        //         q.pop()
        //         for (int i = 0; i < this->adjMatrix())
        //     }
        // }

        void changeEgde(T weight, int v1, int v2) {
            if (v1 == v2)
                throw ErrorInfo(IndexOutOfRangeCode, IndexOutOfRangeMsg);
            this->adjMatrix.set(weight, v1, v2);    
        }

        void printGraph() {
            std::cout << this->adjMatrix;
        }

        size_t getSize() {
            return this->adjMatrix.getSize();
        }

        T getWeight(int v1, int v2) {
            return this->adjMatrix.get(v1, v2);
        }

        bool isCyclic() {
            ArraySequence<ColourToInt> colour(white, this->getSize());
            for (int i = 0; i < this->getSize(); ++i) {
                if (isCyclic(i, colour)) {
                    return true;
                }
            }
            return false;
        }

        ArraySequence<int> getPath(int v1, int v2) {
            ArraySequence<int> parent(-1, this->getSize());
            ArraySequence<int> path(0);
            ArraySequence<T> distance = dijkstra(v1, parent);
            if (distance[v2] != max) {
                for (int v = v2; v != v1; v = parent[v]) {
                    path.prepend(v);
                }
                path.prepend(v1);
                return path;
            }
            std::cout << "No path found\n";
            return path;
        }

        ArraySequence<T> fordBellman (int v) {
            ArraySequence<T> distance(max, this->getSize());
            distance[v] = 0;
            for (int k = 0; k < this->getSize(); ++k){
                for (int i = 0; i < this->getSize(); ++i) {
                    bool anyChange = false;
                    for (int j = 0; j < this->getSize(); ++j) {
                        if (this->adjMatrix[i][j] != 0) {
                            if (distance[i] < max) {
                                if (distance[j] > distance[i] + this->adjMatrix[i][j]) {
                                    distance[j] = distance[i] + this->adjMatrix[i][j];
                                }
                            }
                        }
                    }
                }
            }
            for (int i = 0 ; i < this->getSize(); ++i) {
                distance[i] = (distance[i] == max) ? -1 : distance[i];
            }
            return distance;
        }

        SquareMatrix<T> floyd() {
            SquareMatrix<T> distance(this->adjMatrix);
            for (int i = 0; i < this->getSize(); ++i) {
                for (int j = 0; j < this->getSize(); ++j) {
                    if (i != j) {
                        distance[i][j] = (distance[i][j] == 0) ? max : distance[i][j];
                    }
                }
            }
            for (int k = 0; k < this->getSize(); ++k) {
                for (int i = 0; i < this->getSize(); ++i) {
                    for (int j = 0; j < this->getSize(); ++j) {
                        distance[i][j] = std::min(distance[i][j], distance[i][k] + distance[k][j]);
                    }
                }
            }
            for (int i = 0; i < this->getSize(); ++i) {
                for (int j = 0; j < this->getSize(); ++j) {
                    distance[i][j] = (distance[i][j] == max) ? 0 : distance[i][j];
                }
            }
            return distance;
        }

        ArraySequence<T> topologicalSort() {
            ArraySequence<int> stack(0);
            if (!this->isCyclic()) {
                ArraySequence<bool> visited(false, this->getSize());
                for (int i = 0; i < this->getSize(); ++i) {
                    if (!(visited[i])) {
                        dfs (i, visited, stack);
                    }
                }
            }
            return stack;
        }

        friend std::ostream& operator<<(std::ostream& os, Graph<T>& g) {
            int size = g.getSize();
            for (int i = 0; i < size; ++i) {
                os << i << " : { ";
                for (int j = 0; j < size; ++j) {
                    if (g.adjMatrix.get(i, j) != 0)
                        os << j << ' ';
                }
                os << "};\n";
            }
            return os;
        }
};



Graph<int> CreateTestGraph() {
    Graph<int> graph(8);
    graph.changeEgde(3, 0, 4);
    graph.changeEgde(2, 1, 0);
    graph.changeEgde(8, 2, 0);
    graph.changeEgde(6, 2, 1);
    graph.changeEgde(5, 3, 1);
    graph.changeEgde(3, 5, 1);
    graph.changeEgde(4, 2, 3);
    graph.changeEgde(9, 2, 4);
    graph.changeEgde(2, 3, 5);
    graph.changeEgde(1, 5, 4);
    graph.changeEgde(7, 5, 6);
    graph.changeEgde(3, 6, 7);
    graph.changeEgde(4, 7, 4);
    return graph;
};

