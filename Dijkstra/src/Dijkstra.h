#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
#include <utility>
#include "Graph.h"


class Dijkstra {
    public:
        explicit Dijkstra(const std::string& filename);
        void getPath(const std::string& start, const std::string& end);

    private:
        void Init();
        void printPath(const std::string& start, const std::string& end) const;
        Graph graph;
        std::unordered_map<std::string, std::string> prev;
        std::unordered_map<std::string, bool> visited;
        std::unordered_map<std::string, double> dist;

        using PQItem = std::pair<double, std::string>;
        std::priority_queue<
            PQItem,
            std::vector<PQItem>,
            std::greater<PQItem>
        > pq;
};

#endif
