#include "Algorithms.h"
#include <queue>
#include <vector>
#include <functional>
#include <limits>
#include <SFML/System.hpp>

// BFS Algorithm Implementation
void Algorithms::bfs(Graph& graph, int startNode, sf::RenderWindow& window) {
    auto& nodes = graph.getNodes();
    auto& adjacencyList = graph.getAdjacencyList();

    if (startNode >= nodes.size()) return;

    std::queue<int> q;
    std::vector<bool> visited(nodes.size(), false);

    q.push(startNode);
    visited[startNode] = true;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        nodes[current].shape.setFillColor(sf::Color::Magenta);

        // Render the updated graph
        window.clear();
        for (const auto& edge : graph.getEdges())
            window.draw(edge.line, 2, sf::Lines);
        for (const auto& node : nodes)
            window.draw(node.shape);
        window.display();

        sf::sleep(sf::milliseconds(500)); // Delay for visualization

        for (int neighbor : adjacencyList.at(current)) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}

// DFS Algorithm Implementation
void Algorithms::dfs(Graph& graph, int startNode, sf::RenderWindow& window) {
    auto& nodes = graph.getNodes();
    auto& adjacencyList = graph.getAdjacencyList();

    if (startNode >= nodes.size()) return;

    std::vector<bool> visited(nodes.size(), false);

    std::function<void(int)> dfsHelper = [&](int current) {
        visited[current] = true;
        nodes[current].shape.setFillColor(sf::Color::Blue);

        // Render the updated graph
        window.clear();
        for (const auto& edge : graph.getEdges())
            window.draw(edge.line, 2, sf::Lines);
        for (const auto& node : nodes)
            window.draw(node.shape);
        window.display();

        sf::sleep(sf::milliseconds(500)); // Delay for visualization

        for (int neighbor : adjacencyList.at(current)) {
            if (!visited[neighbor]) dfsHelper(neighbor);
        }
        };

    dfsHelper(startNode);
}

void Algorithms::dijkstra(Graph& graph, int sourceNode, int targetNode, sf::RenderWindow& window) {
    const auto& nodes = graph.getNodes();
    const auto& adjacencyList = graph.getAdjacencyList();
    if (sourceNode >= nodes.size() || targetNode >= nodes.size()) return;

    std::vector<float> dist(nodes.size(), std::numeric_limits<float>::infinity());
    std::vector<int> previous(nodes.size(), -1);
    dist[sourceNode] = 0.0f;

    // Min-heap priority queue for selecting the node with the smallest distance
    std::priority_queue<std::pair<float, int>, std::vector<std::pair<float, int>>, std::greater<>> pq;
    pq.push({ 0.0f, sourceNode });

    while (!pq.empty()) {
        int current = pq.top().second;
        float currentDist = pq.top().first;
        pq.pop();

        if (currentDist > dist[current]) continue; // Skip stale entries

        // Iterate over neighbors
        for (int neighbor : adjacencyList.at(current)) {
            float weight = std::sqrt(
                std::pow(nodes[neighbor].position.x - nodes[current].position.x, 2) +
                std::pow(nodes[neighbor].position.y - nodes[current].position.y, 2)
            );

            if (dist[current] + weight < dist[neighbor]) {
                dist[neighbor] = dist[current] + weight;
                previous[neighbor] = current;
                pq.push({ dist[neighbor], neighbor });
            }
        }
    }

    // Highlight the shortest path
    int currentNode = targetNode;
    while (currentNode != -1 && previous[currentNode] != -1) {
        for (auto& edge : graph.getEdges()) {
            if ((edge.from == currentNode && edge.to == previous[currentNode]) ||
                (edge.to == currentNode && edge.from == previous[currentNode])) {
                edge.line[0].color = sf::Color::Yellow;
                edge.line[1].color = sf::Color::Yellow;
                break;
            }
        }
        graph.getNodes()[currentNode].shape.setFillColor(sf::Color::Yellow);
        currentNode = previous[currentNode];
    }


    // Highlight the source node
    graph.getNodes()[sourceNode].shape.setFillColor(sf::Color::Red);
    graph.getNodes()[targetNode].shape.setFillColor(sf::Color::Red);
}
