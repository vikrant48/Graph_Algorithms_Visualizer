#include <SFML/Graphics.hpp>
#include "Graph.h"
#include "Algorithms.h"
#include <iostream>


enum AlgorithmMode { NONE, DFS, Dijkstra, BFS };

int main() {
    // Create a window for the visualization
    sf::RenderWindow window(sf::VideoMode(800, 600), "Graph Algorithms Visualizer");
    window.setFramerateLimit(60);
    sf::View view = window.getView();


    // Initialize a graph
    Graph graph;
    bool addingNode = false, addingEdge = false;
    int edgeStartNode = -1;

    AlgorithmMode mode = NONE;

    
    

    // Add nodes to the graph
    graph.addNode({ 50, 50 });     // Node 0 
    graph.addNode({ 200, 100 });   // Node 1 
    graph.addNode({ 300, 300 });   // Node 2 
    graph.addNode({ 500, 200 });   // Node 3 
    graph.addNode({ 650, 400 });   // Node 4 
    graph.addNode({ 700, 100 });   // Node 5 
    graph.addNode({ 100, 400 });   // Node 6 
    graph.addNode({ 400, 500 });   // Node 7 
    graph.addNode({ 550, 550 });   // Node 8 

    // Add edges between nodes
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

            // Event-based key handling
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::N)
                    addingNode = true; // Enable node addition mode
                if (event.key.code == sf::Keyboard::E) {
                    addingEdge = true; // Enable edge addition mode
                    edgeStartNode = -1; // Reset any previous edge creation state
                    std::cout << "Edge mode activated\n";
                }
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
            }
            //// Handle key presses to switch algorithms
            //if (event.type == sf::Event::KeyPressed) {
            //    if (event.key.code == sf::Keyboard::B) {
            //        mode = BFS;
            //        std::cout << "BFS Mode Activated\n";
            //    }
            //    else if (event.key.code == sf::Keyboard::D) {
            //        mode = DFS;
            //        std::cout << "DFS Mode Activated\n";
            //    }
            //    else if (event.key.code == sf::Keyboard::S) {
            //        mode = Dijkstra;
            //        std::cout << "Dijkstra Mode Activated\n";
            //    }
            //    else if (event.key.code == sf::Keyboard::Escape) {
            //        window.close();
            //    }
            //}


        }

        // Detect mouse clicks for adding nodes and edges
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

            if (addingNode) {
                graph.addNode(worldPos);
                addingNode = false; // Stop adding nodes
            }
            else if (addingEdge) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f worldPos = window.mapPixelToCoords(mousePos);

                int selectedNode = graph.getNodeAtPosition(worldPos);
                if (selectedNode != -1) {
                    if (edgeStartNode == -1) {
                        // First node is selected
                        edgeStartNode = selectedNode;
                        std::cout << "Selected starting node: " << edgeStartNode << "\n";
                    }
                    else if (selectedNode != edgeStartNode) {
                        // Second node is selected, and it is not the same as the first
                        std::cout << "Selected ending node: " << selectedNode << "\n";
                        // Check if edge already exists
                        const auto& adjacencyList = graph.getAdjacencyList();
                        auto it = adjacencyList.find(edgeStartNode);
                        if (it != adjacencyList.end() &&
                            std::find(it->second.begin(), it->second.end(), selectedNode) != it->second.end()) {
                            std::cout << "Edge already exists between nodes " << edgeStartNode << " and " << selectedNode << ".\n";
                        }
                        else {
                            // Create the edge
                            graph.addEdge(edgeStartNode, selectedNode);
                            std::cout << "Edge created between " << edgeStartNode << " and " << selectedNode << ".\n";
                        }
                        // Reset edgeStartNode for the next edge
                        edgeStartNode = -1;
                        addingEdge = false; // Exit edge-adding mode
                    }
                    else {
                        std::cout << "Cannot create edge: Same node selected twice.\n";
                    }
                }
            }
        }
        // Handle zoom and pan
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) { view.zoom(0.9f); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) { view.zoom(1.1f); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) { view.move(0, -10); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) { view.move(0, 10); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) { view.move(-10, 0); window.setView(view); }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) { view.move(10, 0); window.setView(view); }

        // Clear the window
        window.clear();

        // Highlight the selected node (edgeStartNode)
        if (edgeStartNode != -1) {
            graph.getNodes()[edgeStartNode].shape.setFillColor(sf::Color::Red);
        }

        // Draw the graph
        for (const auto& edge : graph.getEdges())
            window.draw(edge.line, 2, sf::Lines);
        for (const auto& node : graph.getNodes()){
            window.draw(node.shape);
            window.draw(node.text);
        }
            

        // Display the graph
        window.display();

        // Handle keyboard input for algorithms
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
            Algorithms::bfs(graph, 0, window);
            std::cout << "BFS Mode Activated\n";

        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            Algorithms::dfs(graph, 0, window);
            std::cout << "DFS Mode Activated\n";
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            int sourceNode = 0;    // Change to the desired source node
            int targetNode = 8;    // Change to the desired target node
            Algorithms::dijkstra(graph, sourceNode, targetNode, window);
            
            std::cout << "Dijkstra Mode Activated\n";
        }


        //// Clear the window for the current frame
        //window.clear();

        //// Handle algorithm modes
        //switch (mode) {
        //case BFS:
        //    Algorithms::bfs(graph, 0, window);  // Visualize BFS starting at node 0
        //    break;

        //case DFS:
        //    Algorithms::dfs(graph, 0, window);  // Visualize DFS starting at node 0
        //    break;

        //case Dijkstra: {
        //    int sourceNode = 0;    // Change to the desired source node
        //    int targetNode = 8;    // Change to the desired target node
        //    Algorithms::dijkstra(graph, sourceNode, targetNode, window);
        //    break;
        //}

        //case NONE:
        //    // Display the default graph with no algorithm applied
        //    for (const auto& edge : graph.getEdges())
        //        window.draw(edge.line, 2, sf::Lines);
        //    for (const auto& node : graph.getNodes())
        //        window.draw(node.shape);
        //    break;
        //}

        // Display the updated graph
        window.display();
    }
    return 0;
}

