#ifndef ORIENTED_GRAPH_HPP
#define ORIENTED_GRAPH_HPP

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <fstream>
#include <sstream>
#include <stdexcept>

class Node {
    public:
        Node(std::string name) : name(name) {}
        ~Node() {}
        std::vector<std::shared_ptr<Node>> plotting_against;
        std::vector<std::shared_ptr<Node>> plotting_me;
        std::string name;
};

class Oriented_Graph {
    public:
        Oriented_Graph();
        ~Oriented_Graph();

        void add_node(std::string name);
        void add_plottings(std::string node1, std::string node2);
        void display_graph();
        static Oriented_Graph parse_graph(const std::string &filename, const std::string &delimiter);
        std::map<std::string, std::shared_ptr<Node>> nodes;
};

#endif // ORIENTED_GRAPH_HPP
