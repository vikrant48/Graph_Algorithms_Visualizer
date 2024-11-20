#include "NodeEdge.h"

//Node::Node(int id, sf::Vector2f position)
//    : id(id), position(position) {
//    shape.setRadius(20.0f);
//    shape.setFillColor(sf::Color::Cyan);
//    shape.setOrigin(20.0f, 20.0f);
//    shape.setPosition(position);
//}
Node::Node(int id, sf::Vector2f position, const sf::Font& font)
    : id(id), position(position) {
    shape.setRadius(20.0f);
    shape.setFillColor(sf::Color::Cyan);
    shape.setOrigin(20.0f, 20.0f);
    shape.setPosition(position);

    // Configure the text for the node number
    text.setFont(font); // Use the provided font
    text.setString(std::to_string(id)); // Set the node ID as text
    text.setCharacterSize(15); // Set text size
    text.setFillColor(sf::Color::Black); // Set text color
    sf::FloatRect textBounds = text.getLocalBounds();
    text.setOrigin(textBounds.width / 2, textBounds.height / 2);
    text.setPosition(position); // Center the text in the circle
}

Edge::Edge(int from, int to, sf::Vector2f pos1, sf::Vector2f pos2)
    : from(from), to(to) {
    line[0].position = pos1;
    line[1].position = pos2;
    line[0].color = sf::Color::White;
    line[1].color = sf::Color::White;
}

//Node::Node(int id, sf::Vector2f position) : id(id), position(position) {
//    shape.setRadius(20.0f);
//    shape.setFillColor(sf::Color::Cyan);
//    shape.setOrigin(20.0f, 20.0f);
//    shape.setPosition(position);
//}
//
//Edge::Edge(int from, int to, sf::Vector2f pos1, sf::Vector2f pos2, float weight)
//    : from(from), to(to), weight(weight) {
//    line[0].position = pos1;
//    line[1].position = pos2;
//    line[0].color = sf::Color::White;
//    line[1].color = sf::Color::White;
//}
