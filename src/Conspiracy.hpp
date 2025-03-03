#ifndef CONSIPRACY_HPP
#define CONSPIRACY_HPP

#include "Matrix.hpp"
#include "Oriented_Graph.hpp"

class Conspiracy {
    public:
        Conspiracy(std::string relationship_file, std::string matrix_file);
        ~Conspiracy();
        void display_matrix();
        Oriented_Graph graph;
        // Matrix matrix;

    private:
        void parse_file(std::string relationship_file, std::string matrix_file);
};

#endif // CONSPIRACY_HPP