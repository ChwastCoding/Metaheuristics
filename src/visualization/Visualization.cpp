#include "Visualization.h"

const std::string Visualization::pathToFont = "../resources/JetBrainsMono-Regular.ttf";

Visualization::Visualization(int width, int height, const std::string& title)
: window(sf::VideoMode(width, height), title) {
    windowSize = window.getSize();
    if (!font.loadFromFile(pathToFont)) {
        std::cout << "Failed to load font file\n";
        exit(-1);
    }
}

bool Visualization::isOpen()
{
    return window.isOpen();
}

void Visualization::draw(int distance)
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

    sf::Vertex verteceis[] = { positions[solution[solution.size() - 1]], positions[solution[0]] };
    window.draw(verteceis, 2, sf::Lines);

    sf::Text text;
    text.setFont (font);
    text.setCharacterSize(15);

    text.setString(std::to_string(0));
    text.setPosition(positions[0]);
    text.setFillColor(sf::Color::White);

    circle.setFillColor(sf::Color::Red);
    circle.setPosition(positions[0] + offset);

    window.draw(circle);
    window.draw(text);
    circle.setFillColor(sf::Color::Magenta);

    for (int i = 1; i < solution.size(); i ++) {
        circle.setPosition(positions[i] + offset);
        window.draw(circle);

        text.setString(std::to_string(i));
        text.setPosition(positions[i]);
        window.draw(text);
    }

    text.setCharacterSize(30);
    std::string info = "Objective function: " + std::to_string(distance);
    text.setString(info);
    text.setPosition(sf::Vector2f(20, 20));
    window.draw(text);

    window.display();
}

void Visualization::setSolution(const TSPInstance::solution& solution)
{
    this->solution = solution;
}

void Visualization::setInstance(std::shared_ptr<Euc2DInstance> instance)
{
    this->instance = instance;
    this->fieldSize = fieldSize;

    auto nodes = instance->getCoords();
    int maxX = std::max_element(nodes.begin(), nodes.end(), 
        [](std::pair<int, int>a, std::pair<int, int>b) { return a.first < b.first;})->first;
    int maxY = std::max_element(nodes.begin(), nodes.end(), 
        [](std::pair<int, int>a, std::pair<int, int>b) { return a.second < b.second;})->second;
    this->fieldSize = std::max(maxX, maxY);

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
