/*
** EPITECH PROJECT, 2025
** Game of stones
** File description:
** Oriented Graph
*/

#include "Oriented_Graph.hpp"

Oriented_Graph::Oriented_Graph()
{
}

Oriented_Graph::~Oriented_Graph()
{
}

void Oriented_Graph::add_plottings(std::string node1, std::string node2)
{
    nodes[node1]->plotting_against.push_back(nodes[node2]);
    nodes[node2]->plotting_me.push_back(nodes[node1]);
}

void Oriented_Graph::add_node(std::string name)
{
    nodes[name] = std::make_shared<Node>(name);
}
