#pragma once

#include <SFML/Graphics.hpp>

// Define Node
struct Node {
    int id;
    sf::CircleShape shape;
    sf::Vector2f position;
    sf::Text text;

    //Node(int id, sf::Vector2f position);
    Node(int id, sf::Vector2f position, const sf::Font& font);
};

// Define Edge
struct Edge {
    int from, to;
    sf::Vertex line[2];

    Edge(int from, int to, sf::Vector2f pos1, sf::Vector2f pos2);
};

//struct Node {
//    int id;
//    sf::CircleShape shape;
//    sf::Vector2f position;
//
//    Node(int id, sf::Vector2f position);
//};
//
//struct Edge {
//    int from, to;
//    sf::Vertex line[2];
//    float weight;
//
//    Edge(int from, int to, sf::Vector2f pos1, sf::Vector2f pos2, float weight = 1.0f);
//};