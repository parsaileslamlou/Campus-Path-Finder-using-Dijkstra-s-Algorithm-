#include <iostream>
#include "Dijkstra.h"

int main() {
    try {
        std::string filename = "data/campus_graph.txt";
        // Load the graph
        Dijkstra d(filename);

        std::cout << "Test 1: ENTRANCE -> DORM\n";
        d.getPath("ENTRANCE", "DORM");
        std::cout << "\n";

        std::cout << "Test 2: GYM -> ADMIN\n";
        d.getPath("GYM", "ADMIN");
        std::cout << "\n";

        std::cout << "Test 3: LIBRARY -> CAFETERIA\n";
        d.getPath("LIBRARY", "CAFETERIA");
        std::cout << "\n";

        std::cout << "Test 4: ADMIN -> ENTRANCE (should fail) \n";
        d.getPath("ADMIN", "ENTRANCE");
        std::cout << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    return 0;
}
