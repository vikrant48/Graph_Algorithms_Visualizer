
#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Algorithms.h"
#include <iostream>

// Main Function
int main() {
    // Create a window for the visualization
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Algorithms Visualizer");
    window.setFramerateLimit(60);
    sf::View view = window.getView();

    // Initialize a graph
    Graph graph;

    // Modes and states
    bool addingNode = false, addingEdge = false;
    int edgeStartNode = -1;

    // Dijkstra mode states
    int sourceNode = -1, targetNode = -1;
    bool selectingSource = false;

    // Add sample nodes to the graph
    graph.addNode({ 50, 50 });     // Node 0
    graph.addNode({ 200, 100 });   // Node 1
    graph.addNode({ 300, 300 });   // Node 2
    graph.addNode({ 500, 200 });   // Node 3
    graph.addNode({ 650, 400 });   // Node 4
    graph.addNode({ 700, 100 });   // Node 5
    graph.addNode({ 100, 400 });   // Node 6
    graph.addNode({ 400, 500 });   // Node 7
    graph.addNode({ 550, 550 });   // Node 8

    // Add sample edges
    graph.addEdge(0, 1);
    graph.addEdge(0, 6);
    graph.addEdge(1, 2);
    graph.addEdge(1, 5);
    graph.addEdge(2, 3);
    graph.addEdge(2, 7);
    graph.addEdge(3, 4);
    graph.addEdge(4, 8);
    graph.addEdge(5, 3);
    graph.addEdge(6, 7);
    graph.addEdge(7, 8);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Handle key presses to toggle modes
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::N) {
                    addingNode = true;
                    addingEdge = false;
                    edgeStartNode = -1;
                    std::cout << "Node adding mode activated\n";
                }
                else if (event.key.code == sf::Keyboard::E) {
                    addingEdge = true;
                    addingNode = false;
                    edgeStartNode = -1;
                    std::cout << "Edge adding mode activated\n";
                }
                else if (event.key.code == sf::Keyboard::S) {
                    selectingSource = true;
                    std::cout << "Dijkstra Mode Activated. Select source and target nodes.\n";
                }
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R) {
                    // Reset nodes
                    for (auto& node : graph.getNodes()) {
                        node.shape.setFillColor(sf::Color::Cyan); // Default node color
                    }

                    // Reset edges
                    for (auto& edge : graph.getEdges()) {
                        edge.line[0].color = sf::Color::White; // Default edge color
                        edge.line[1].color = sf::Color::White;
                    }

                    // Reset selections
                    sourceNode = -1;
                    targetNode = -1;
                    selectingSource = true;

                    std::cout << "Graph view reset to default.\n";
                }
                else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Handle mouse input
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            if (addingNode) {
                graph.addNode(worldPos);
                addingNode = false; // Exit node adding mode
                std::cout << "Node added at " << worldPos.x << ", " << worldPos.y << "\n";
            }
            else if (addingEdge) {
                int selectedNode = graph.getNodeAtPosition(worldPos);
                if (selectedNode != -1) {
                    if (edgeStartNode == -1) {
                        edgeStartNode = selectedNode; // Select start node
                        std::cout << "Edge start node selected: " << edgeStartNode << "\n";
                    }
                    else if (selectedNode != edgeStartNode) {
                        graph.addEdge(edgeStartNode, selectedNode);
                        std::cout << "Edge created between " << edgeStartNode << " and " << selectedNode << "\n";
                        edgeStartNode = -1; // Reset edge selection
                        addingEdge = false; // Exit edge adding mode
                    }
                }
            }
        }
        // Highlight selected nodes
        if (edgeStartNode != -1) graph.getNodes()[edgeStartNode].shape.setFillColor(sf::Color::Red);

        // Handle algorithm mode selection (Dijkstra, BFS, DFS)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            std::cout << "BFS mode activated\n";
            Algorithms::bfs(graph, 0, window);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            std::cout << "DFS mode activated\n";
            Algorithms::dfs(graph, 0, window);
        }
        

        // Handle mouse clicks for node selection
        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            int selectedNode = graph.getNodeAtPosition(worldPos);

            if (selectingSource && selectedNode != -1) {
                if (sourceNode == -1) {
                    // Select source node
                    sourceNode = selectedNode;
                    std::cout << "Source node selected: " << sourceNode << "\n";
                    graph.getNodes()[sourceNode].shape.setFillColor(sf::Color::Green); // Highlight source
                }
                else if (targetNode == -1 && selectedNode != sourceNode) {
                    // Select target node
                    targetNode = selectedNode;
                    std::cout << "Target node selected: " << targetNode << "\n";
                    graph.getNodes()[targetNode].shape.setFillColor(sf::Color::Blue); // Highlight target

                    // Execute Dijkstra algorithm
                    Algorithms::dijkstra(graph, sourceNode, targetNode, window);

                    // Reset selection for future
                    sourceNode = -1;
                    targetNode = -1;
                    selectingSource = false;
                    std::cout << "Dijkstra completed. Resetting selection mode.\n";
                }
                else {
                    std::cout << "Target node cannot be the same as the source node.\n";
                }
            }
        }



        // Handle zoom and pan controls
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { view.zoom(0.9f); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { view.zoom(1.1f); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0, -10); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0, 10); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-10, 0); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(10, 0); window.setView(view); }

        // Clear the window
        window.clear();

        // Draw the graph
        for (const auto& edge : graph.getEdges())
            window.draw(edge.line, 2, sf::Lines);
        for (const auto& node : graph.getNodes()) {
            window.draw(node.shape);
            window.draw(node.text);
        }

        // Display the updated frame
        window.display();
    }

    return 0;
}


