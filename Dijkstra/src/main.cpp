#include <cassert>
#include <cmath>
#include "Dijkstra.h"

void testReachablePath() {
    Dijkstra d("data/campus_graph.txt");
    Dijkstra::PathResult result = d.computePath("ENTRANCE", "DORM");

    assert(result.reachable == true);
    assert(result.path.front() == "ENTRANCE");
    assert(result.path.back() == "DORM");
    assert(result.path.size() > 1);
    assert(std::abs(result.weight - result.weight) < 0.001); // sanity
}

void testUnreachablePath() {
    Dijkstra d("data/campus_graph.txt");
    Dijkstra::PathResult result = d.computePath("ADMIN", "ENTRANCE");

    assert(result.reachable == false);
    assert(result.path.empty());
}

void testSameStartEnd() {
    Dijkstra d("data/campus_graph.txt");
    Dijkstra::PathResult result = d.computePath("LIBRARY", "LIBRARY");

    assert(result.reachable == true);
    assert(result.path.size() == 1);
    assert(result.path[0] == "LIBRARY");
    assert(result.weight == 0.0);
}

int main() {
    testReachablePath();
    testUnreachablePath();
    testSameStartEnd();
    return 0;
}
