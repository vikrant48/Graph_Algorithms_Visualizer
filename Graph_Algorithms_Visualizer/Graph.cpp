#include "Graph.h"
#include <iostream>

//void Graph::addNode(sf::Vector2f position) {
//    int id = nodes.size();
//    nodes.emplace_back(id, position);
//
//    // Ensure the adjacency list is ready for the new node
//    adjacencyList[id] = {};
//}
void Graph::addNode(sf::Vector2f position) {
    int id = nodes.size();
    nodes.emplace_back(id, position, defaultFont);

    // Ensure the adjacency list is ready for the new node
    adjacencyList[id] = {};
}

void Graph::addEdge(int from, int to) {
    if (from >= nodes.size() || to >= nodes.size()) {
        std::cerr << "Invalid edge: from " << from << " to " << to << ". Node index out of range.\n";
        return;
    }

    // Prevent duplicate edges
    if (std::find(adjacencyList[from].begin(), adjacencyList[from].end(), to) != adjacencyList[from].end()) {
        std::cerr << "Edge already exists between nodes " << from << " and " << to << ".\n";
        return;
    }

    adjacencyList[from].push_back(to);
    adjacencyList[to].push_back(from); // For undirected graph
    edges.emplace_back(from, to, nodes[from].position, nodes[to].position);

    std::cout << "Edge successfully added between nodes " << from << " and " << to << ".\n";
}

int Graph::getNodeAtPosition(sf::Vector2f position) {
    for (const auto& node : nodes) {
        float distance = std::sqrt(std::pow(node.position.x - position.x, 2) +
                         std::pow(node.position.y - position.y, 2));
        std::cout << "Checking node " << node.id << " at position (" << node.position.x << ", " << node.position.y << ") "
            << "Distance: " << distance << " Radius: " << node.shape.getRadius() << "\n";
        if (distance <= node.shape.getRadius() + 5.0f) { // Tolerate slight offset
            std::cout << "Node " << node.id << " selected.\n";
            return node.id;
        }
    }
    return -1; // No node found at this position
}




std::vector<Node>& Graph::getNodes() {
    return nodes;
}

std::vector<Edge>& Graph::getEdges() {
    return edges;
}

const std::unordered_map<int, std::vector<int>>& Graph::getAdjacencyList() const {
    return adjacencyList;
}


//void Graph::updateEdgeWeight(sf::Vector2f position, float newWeight) {
//    for (auto& edge : edges) {
//        sf::Vector2f midPoint = (edge.line[0].position + edge.line[1].position) / 2.0f;
//        if (std::hypot(position.x - midPoint.x, position.y - midPoint.y) < 10.0f) {
//            edge.weight = newWeight;
//        }
//    }
//}

