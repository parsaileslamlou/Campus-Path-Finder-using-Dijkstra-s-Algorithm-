#include <string>
#include <iostream>
#include <stack>
#include <queue>
#include <vector>
#include <functional>
#include <unordered_map>
#include <utility>
#include <limits>
#include "Dijkstra.h"

Dijkstra::Dijkstra(const std::string& filename){
    graph.loadFromFile(filename);
    Init();
}


void Dijkstra::Init(){ //Intializes all helper containers to default Dijkstra friendly values
    for(const auto& pair : graph.getList()){
        prev[pair.first] = "";
        visited[pair.first] = false;
        dist[pair.first] = std::numeric_limits<double>::infinity();
    }
   
}

Dijkstra::PathResult Dijkstra::computePath(const std::string& start, const std::string& end){ //Using Dijkstra's algorithm to find best path
    PathResult result;
    result.reachable = false;
    result.weight = 0.0;
    
    if (!graph.containsNode(start) || !graph.containsNode(end)) {
        return result; // edge check
    }

    Init();  //Resets member variables in the case the program has ran before
    
    dist[start] = 0;
    pq.push(PQItem{0,start});
    
    
    while(!pq.empty()){
        PQItem cur = pq.top();
        pq.pop();
        
        double removed_dist = cur.first;
        std::string removed = cur.second;
        
        if (removed == end) break; //once removed fastest path found
       
        visited[removed] = true;
        
        for(auto& edge : graph.getNeighbors(removed)){
            if(visited[edge.first]) continue;
            double newDist = removed_dist + edge.second;
            if(newDist < dist[edge.first]){
                dist[edge.first] = newDist;
                prev[edge.first] = removed;
                pq.push(PQItem{newDist, edge.first});
            }
        }
    }
    
    if (dist[end] == std::numeric_limits<double>::infinity()) {
        return result; //reachable = false
    }
    
    std::vector<std::string> forwardPath;

    std::string traversal = end;

    while(traversal != start){
        forwardPath.push_back(traversal);
        traversal = prev.at(traversal);
    }
    forwardPath.push_back(start);
    
    std::reverse(forwardPath.begin(),forwardPath.end());
    result.reachable = true;
    result.path = forwardPath;
    result.weight = dist[end];
    return result;
}

void Dijkstra::printPath(const std::string& start, const std::string& end) const{ //helper to print best path
    std::string traversal = end;
    std::stack<std::string> path;
    
    while(traversal != start){
        path.push(traversal);
        traversal = prev.at(traversal);
    }
    path.push(start);
    
    while(!path.empty()){
        std::cout << path.top() << " ";
        path.pop();
    }
}

