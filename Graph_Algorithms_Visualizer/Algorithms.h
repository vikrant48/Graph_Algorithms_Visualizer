#pragma once

#include "Graph.h"
#include <SFML/Graphics.hpp>

// Class for graph algorithms
class Algorithms {
public:
    static void bfs(Graph& graph, int startNode, sf::RenderWindow& window);
    static void dfs(Graph& graph, int startNode, sf::RenderWindow& window);
    //static void dijkstra(Graph& graph, int startNode, sf::RenderWindow& window);
    static void dijkstra(Graph& graph, int startNode, int targetNode, sf::RenderWindow& window);
};


//class Algorithms {
//public:
//    void bfs(Graph& graph, int startNode, sf::RenderWindow& window);
//    void dfs(Graph& graph, int startNode, sf::RenderWindow& window);
//    void dijkstra(Graph& graph, int startNode, sf::RenderWindow& window);
//};