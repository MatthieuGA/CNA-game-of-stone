/*
** EPITECH PROJECT, 2025
** c
** File description:
** c
*/

#include "Conspiracy.hpp"

Conspiracy::Conspiracy(std::string relationship_file, std::string plot_file) : matrix(Matrix::parse_graph(relationship_file, " is friends with "))
{
    parse_file(relationship_file, plot_file);
}

Conspiracy::~Conspiracy()
{
}

void Conspiracy::parse_file(std::string relationship_file, std::string plot_file)
{
    graph = Oriented_Graph::parse_graph(plot_file, " is plotting against ");
}

void Conspiracy::display_matrix()
{
    std::cout << matrix << std::endl;
}