#include "Parser.h"

#include <fstream>
#include <cmath>

#include "../util.h"
#include "Euc2DInstance.h"
#include "MatrixInstance.h"

const std::string unsuppoartedProblemMessage = "Unsuppoarted problem type";

std::shared_ptr<TSPInstance> Parser::getInstance(const std::string& path) {
    std::ifstream file(path);
    if(file.is_open()) {
        std::cout << "Opened file" << std::endl;
        std::string line, name;
        std::shared_ptr<TSPInstance> instance;
        bool symetric;
        int size;

        while (getline(file, line)){
            auto colon_index = line.find(':');
            std::string keyword = util::trimWhitespace(line.substr(0, colon_index));
            auto value = util::trimWhitespace(line.substr(colon_index + 1));
            if (keyword == "NAME") {
                name = value; // line.substr(colon_index + 2);
            } else if (keyword == "TYPE") {
                auto type = value; // line.substr(colon_index + 2);
                std::cout << "TYPE " << type << std::endl;
                if (type != "TSP" && type != "ATSP")
                    throw std::runtime_error(unsuppoartedProblemMessage);
                symetric = (type == "TSP");
            } else if (keyword == "DIMENSION") {
                size = std::stoi(value);
            } else if (keyword == "EDGE_WEIGHT_FORMAT") {
                auto format = value; // line.substr(colon_index + 2);
                std::cout << "FORMAT " << format << std::endl;
                if (format != "FULL_MATRIX") 
                    throw std::runtime_error(unsuppoartedProblemMessage);
            } else if (keyword == "NODE_COORD_SECTION") {
                std::vector<std::pair<int, int>> coords(size);
                for (int i = 0; i < size; i ++) {
                    int index;
                    double x, y;
                    file >> index;
                    file >> x;
                    file >> y;
                    coords[i] = std::pair<int, int>(round(x), round(y));
                }
                getline(file, line);
                auto tsp = std::make_shared<Euc2DInstance>(size);
                tsp->setCoords(coords);
                tsp->setName(name); 
                instance = tsp;
            } else if (keyword == "EDGE_WEIGHT_SECTION") {
                std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
                for (int i = 0; i < size; i++ ){
                    for (int j = 0; j < size; j ++) {
                        file >> matrix[i][j];
                    }
                }
                getline(file, line);
                auto tsp = std::make_shared<MatrixInstance>(size);
                tsp->setMatrix(matrix);
                tsp->setName(name);
                instance = tsp;
            }  
        }
        if (!instance) throw std::runtime_error("Failed to read problem instance");
        return instance;
    } else {
        throw std::runtime_error("Failed to open file: " + path);
    }
}

void Parser::saveInstance(std::shared_ptr<TSPInstance> instance, const std::string& path) {
    std::ofstream file(path);
    if (file.is_open()) {
        file << *instance.get();
    } else {
        throw std::runtime_error("Failed to open file: " + path);
    }
}