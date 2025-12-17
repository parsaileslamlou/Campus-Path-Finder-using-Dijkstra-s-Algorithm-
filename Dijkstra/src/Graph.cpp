#include "Graph.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <fstream>

void Graph::loadFromFile(const std::string& filename){
    parseFile(filename);
}

bool Graph::containsNode(const std::string& node) const {
    return adjList.find(node) != adjList.end();
}
// Key is the starting Node, and value is an array of Nodes to visit with the weight
std::vector<std::pair<std::string, double>> Graph::getNeighbors(const std::string& node) const{
    auto it = adjList.find(node);
    if (it != adjList.end()) return it->second;
    return {};
}

std::unordered_map<std::string, std::vector<std::pair<std::string, double>>> Graph::getList() const{
    return adjList;
}

void Graph::parseFile(const std::string& filename){ 
    std::ifstream inFile;
    inFile.open(filename);
    
    std::string str;
    std::string key;
    std::string destination;
    double weight = 0.0;
    int index = 1;
    while(inFile >> str){
        if(index == 5) index = 1;
        if(index == 1) key = str;
        else if(index == 2) destination = str;
        else if(index == 3) weight = std::stod(str);
        
        else if(index == 4){
            bool found = false;
            if(str != "FLAT"){
                weight *= (str == "STAIRS_UP" ? 1.8 : 1.2);
            }
            weight = std::round(weight * 1000.0) / 1000.0; // limits to 3 decimal places to ensure no floating point errors
            
            //Note for futre self: worst case is O(n) which can be a problem for a bigger datasets
            //      if so, switch to an unordered_set for O(1)
            for(auto it = adjList[key].begin(); it != adjList[key].end(); it++){
                if(it->first == destination && it->second == weight){
                    found = true;
                    break;
                }
            }
            if(!found) adjList[key].push_back({destination, weight});
        }
        index++;
    }
}



