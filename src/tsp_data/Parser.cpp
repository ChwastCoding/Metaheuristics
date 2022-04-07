#include "Parser.h"

#include <fstream>
#include <cmath>

#include "../util.h"
#include "TSPInstance.h"
#include "Euc2DInstance.h"
#include "MatrixInstance.h"

const std::string unsuppoartedProblemMessage = "Unsuppoarted problem type";

std::shared_ptr<TSPInstance> Parser::getInstance(const std::string& path) {
    std::ifstream file(path);
    if(file.is_open()) {
        std::cerr << "Opened file" << std::endl;
        std::string line, name;
        std::shared_ptr<TSPInstance> instance;
        bool symetric, isDiagonal;
        int size;
        MatrixInstance::MatrixType type = MatrixInstance::MatrixType::UNDEFINED;

        while (getline(file, line)){
            if (line.size() < 2) continue;
            auto colon_index = line.find(':');
            std::string keyword = util::trimWhitespace(line.substr(0, colon_index));
            auto value = util::trimWhitespace(line.substr(colon_index + 1));
            if (keyword == "NAME") {
                name = value;
            } else if (keyword == "TYPE") {
                auto type = value;
                if (type != "TSP" && type != "ATSP")
                    throw std::runtime_error(unsuppoartedProblemMessage);
                symetric = (type == "TSP");
            } else if (keyword == "DIMENSION") {
                size = std::stoi(value);
            } else if (keyword == "EDGE_WEIGHT_FORMAT") {
                auto format = value;
                if (format == "FULL_MATRIX") type = MatrixInstance::MatrixType::FULL;
                else if (format == "UPPER_ROW") type = MatrixInstance::MatrixType::UPPER_ROW;
                else if (format == "LOWER_ROW") type = MatrixInstance::MatrixType::LOWER_ROW;
                else if (format == "UPPER_DIAG_ROW") type = MatrixInstance::MatrixType::UPPER_DIAG_ROW;
                else if (format == "LOWER_DIAG_ROW") type = MatrixInstance::MatrixType::LOWER_DIAG_ROW;
                else if (format == "UPPER_COL") type = MatrixInstance::MatrixType::UPPER_COL;
                else if (format == "LOWER_COL") type = MatrixInstance::MatrixType::LOWER_COL;
                else if (format == "UPPER_DIAG_COL") type = MatrixInstance::MatrixType::UPPER_DIAG_COL;
                else if (format == "LOWER_DIAG_COL") type = MatrixInstance::MatrixType::FULL;
                else 
                    throw std::runtime_error("Unsupported matrix type");
                isDiagonal = (type >= MatrixInstance::MatrixType::UPPER_DIAG_ROW);

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
                if (type == MatrixInstance::MatrixType::UNDEFINED)
                    throw std::runtime_error("Did not set Matrix type");
                
                auto tsp = std::make_shared<MatrixInstance>(size);
                tsp->setName(name);
                
                if (type == MatrixInstance::MatrixType::FULL){
                    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));
                    for (int i = 0; i < size; i++ ){
                        for (int j = 0; j < size; j ++) {
                            file >> matrix[i][j];
                        }
                    }
                    getline(file, line);
                    tsp->setMatrix(matrix);
                    tsp->setType(MatrixInstance::MatrixType::FULL);
                    tsp->setIsSymetric(symetric);
                } else {
                    if (type == MatrixInstance::MatrixType::UNDEFINED || !symetric)
                        throw std::runtime_error(unsuppoartedProblemMessage);

                    std::vector<std::vector<int>> matrix(size);
                    for (int i = 0; i < size; i ++)
                        matrix[i] = std::vector<int>(size - i);
                    
                    if (type == MatrixInstance::MatrixType::UPPER_ROW ||
                        type == MatrixInstance::MatrixType::UPPER_DIAG_ROW ||
                        type == MatrixInstance::MatrixInstance::LOWER_COL ||
                        type == MatrixInstance::MatrixInstance::LOWER_DIAG_COL) {
                        for (int i = 0; i < size; i ++) {
                            int j = 0;
                            if (!isDiagonal) matrix[i][j ++] = MatrixInstance::infty;
                            while (j < size - i) file >> matrix[i][j ++];
                        }
                    } else {
                        for (int i = 0; i < size; i ++) {
                            int j = 0;
                            if (!isDiagonal) matrix[j ++][i] = MatrixInstance::infty;
                            while (j < size - i) file >> matrix[j ++][i];
                        }
                    }

                    tsp->setType(MatrixInstance::MatrixType::UPPER_DIAG_ROW);
                    tsp->setMatrix(matrix);
                    tsp->setIsSymetric(true);
                    getline(file, line);
                }
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