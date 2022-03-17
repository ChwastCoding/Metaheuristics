#ifndef __VISUALIZATION_H__
#define __VISUALIZATION_H__

#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "../tsp_data/Euc2DInstance.h"

class Visualization {
private:
    sf::RenderWindow window;
    std::shared_ptr<Euc2DInstance> instance;
    TSPInstance::solution solution;
    
    int fieldSize;
    sf::Vector2u windowSize;
    std::vector<sf::Vector2f> positions;
    
    sf::Vector2f toWindowSpace(const std::pair<int, int>& pair);

public:
    Visualization(int width = 1024, int height = 768, const std::string& title = "Visualization");

    bool isOpen();
    void draw();
    void setSolution(const TSPInstance::solution& solution);
    void setInstance(std::shared_ptr<Euc2DInstance> instance, int fieldSize);
};

#endif // __VISUALIZATION_H__