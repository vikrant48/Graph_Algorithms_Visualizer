#pragma once

#include "NodeEdge.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>

class Graph {
private:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::unordered_map<int, std::vector<int>> adjacencyList;
    sf::Font defaultFont;
public:
    void addNode(sf::Vector2f position);
    void addEdge(int from, int to);
    int getNodeAtPosition(sf::Vector2f position);
    std::vector<Node>& getNodes();
    std::vector<Edge>& getEdges();
    const std::unordered_map<int, std::vector<int>>& getAdjacencyList() const;
};

//class Graph {
//private:
//    std::vector<Node> nodes;
//    std::vector<Edge> edges;
//    std::unordered_map<int, std::vector<int>> adjacencyList;
//
//public:
//    void addNode(sf::Vector2f position);
//    void addEdge(int from, int to, float weight = 1.0f);
//    int getNodeAtPosition(sf::Vector2f position);
//    std::vector<Node>& getNodes();
//    std::vector<Edge>& getEdges();
//    std::unordered_map<int, std::vector<int>>& getAdjacencyList();
//    void updateEdgeWeight(sf::Vector2f position, float newWeight);
//};