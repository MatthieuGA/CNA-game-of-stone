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

Oriented_Graph Oriented_Graph::parse_graph(const std::string &filename, const std::string &delimiter)
{
    Oriented_Graph graph;
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t pos = line.find(delimiter);
        if (pos == std::string::npos) {
            throw std::runtime_error("Delimiter not found in line: " + line);
        }

        std::string node1 = line.substr(0, pos);
        std::string node2 = line.substr(pos + delimiter.length());

        graph.add_node(node1);
        graph.add_node(node2);
        graph.add_plottings(node1, node2);
    }

    file.close();
    return graph;
}
