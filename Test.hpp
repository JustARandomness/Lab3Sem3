void Test() {
    Graph<int> graph = CreateTestGraph();
    auto topSort = graph.topologicalSort();
    int topSortRight[8] = {2, 3, 5, 6, 7, 1, 0, 4};
    bool works = true;
    for (int i = 0; i < graph.getSize(); ++i) {
        if (topSort[i] != topSortRight[i]) {
            works = false;
        }
    }
    if (works) {
        std::cout << "Topological sort working properly\n\n";
    }
    else {
        std::cout << "Topological sort doesn't work properly\n\n";
    }
    works = true;
    auto bellman2 = graph.fordBellman(2);
    if (bellman2[0] != 8 || bellman2[1] != 6 || bellman2[2] != 0 || bellman2[3] != 4 || bellman2[4] != 7 || bellman2[5] != 6 || bellman2[6] != 13 || bellman2[7] != 16) {
        works = false;
    }
    if (works) {
        std::cout << "Bellman algorythm working properly\n\n";
    }
    else {
        std::cout << "Bellman algorythm doesn't work properly\n\n";
    }
    works = true;
    auto dijkstra = graph.getPath(2, 4);
    int path[4] = {2, 3, 5, 4};
    for (int i = 0; i < dijkstra.getLength(); ++i) {
        if (dijkstra[i] != path[i]) {
            works = false;
        }
    }
    if (works) {
        std::cout << "Dijkstra algorythm working properly\n\n";
    }
    else {
        std::cout << "Dijkstra algorythm doesn't work properly\n\n";
    }
    works = true;
    auto floyd_line = graph.floyd().getLine(2);
    for (int i = 0; i < graph.getSize(); ++i) {
        if (floyd_line[0][i] != bellman2[i]) {
            works = false;
        }
    }
    if (works) {
        std::cout << "Floyd algorythm working properly\n\n";
    }
    else {
        std::cout << "Floyd algorythm doesn't work properly\n\n";
    }
}