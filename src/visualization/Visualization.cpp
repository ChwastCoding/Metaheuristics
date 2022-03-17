#include "Visualization.h"

Visualization::Visualization(int width, int height, const std::string& title)
: window(sf::VideoMode(width, height), title) {
    windowSize = window.getSize();
}

bool Visualization::isOpen()
{
    return window.isOpen();
}

void Visualization::draw()
{
    sf::Event event;
    auto dimensions = window.getSize();

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
    }

    window.clear(sf::Color::Black);

    auto circle = sf::CircleShape(5.0f);
    sf::Vector2f offset(-5, -5);

    for (int i = 1; i < solution.size(); i ++) {
        sf::Vertex verteceis[] = { positions[solution[i - 1]], positions[solution[i]] };
        window.draw(verteceis, 2, sf::Lines);
    }

    sf::Vertex verteceis[] = { positions[solution[positions.size() - 1]], positions[solution[0]] };
    window.draw(verteceis, 2, sf::Lines);

    circle.setFillColor(sf::Color::Red);
    circle.setPosition(positions[solution[0]] + offset);

    window.draw(circle);
    circle.setFillColor(sf::Color::Magenta);

    for (int i = 1; i < solution.size(); i ++) {
        circle.setPosition(positions[solution[i]] + offset);
        window.draw(circle);
    }

    window.display();
}

void Visualization::setSolution(const TSPInstance::solution& solution)
{
    this->solution = solution;
}

void Visualization::setInstance(std::shared_ptr<Euc2DInstance> instance, int fieldSize)
{
    this->instance = instance;
    this->fieldSize = fieldSize;

    positions = std::vector<sf::Vector2f>(instance->getSize());
    for (int i = 0; i < instance->getSize(); i++)
        positions[i] = toWindowSpace(instance->getCoords(i));
}

sf::Vector2f Visualization::toWindowSpace(const std::pair<int, int>& pair)
{
    return sf::Vector2f(
        pair.first / (float)fieldSize * windowSize.x, 
        (1.0f - pair.second / (float)fieldSize) * windowSize.y);
}
