#ifndef CONSIPRACY_HPP
#define CONSPIRACY_HPP

#include "Matrix.hpp"
#include "Oriented_Graph.hpp"

#define QUEEN "Cersei Lannister"

class PathToTakeDown {
    public:
        PathToTakeDown(){length = 0;}
        ~PathToTakeDown(){}
        std::vector<std::string> path;
        int length;
};

class Conspiracy {
    public:
        Conspiracy(std::string relationship_file, std::string matrix_file, unsigned int n);
        ~Conspiracy();
        void display_matrix();
        Oriented_Graph graph;
        PathToTakeDown get_path(std::string node_to_take_down, int n, PathToTakeDown path);
        Matrix matrix;

    private:
        void parse_file(std::string matrix_file);
        PathToTakeDown befriend(std::string node_to_befriend, int n, PathToTakeDown path);
};

#endif // CONSPIRACY_HPP