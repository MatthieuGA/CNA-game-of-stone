/*
** EPITECH PROJECT, 2025
** c
** File description:
** c
*/

#include "Conspiracy.hpp"
#include <algorithm>

Conspiracy::Conspiracy(std::string relationship_file, std::string plot_file) : matrix(Matrix::parse_graph(relationship_file, " is friends with "))
{
    parse_file(plot_file);
}

Conspiracy::~Conspiracy()
{
}

void Conspiracy::parse_file(std::string plot_file)
{
    graph = Oriented_Graph::parse_graph(plot_file, " is plotting against ");
}

void Conspiracy::display_matrix()
{
    std::cout << matrix << std::endl;
}

static bool is_in_vector(std::vector<std::string> path, std::string node)
{
    return std::find(path.begin(), path.end(), node) != path.end();
}

static PathToTakeDown get_smallest_path(std::vector<PathToTakeDown> paths)
{
    PathToTakeDown smallest_path = PathToTakeDown();

    smallest_path.length = 1000;
    for (auto &p : paths) {
        if (p.length < smallest_path.length)
            smallest_path = p;
    }
    if (smallest_path.length == 1000)
        smallest_path.length = -1;
    return smallest_path;
}

PathToTakeDown Conspiracy::befriend(std::string node_to_befriend, int n, PathToTakeDown path)
{
    std::vector<PathToTakeDown> paths;

    path.length++;
    path.path.push_back(node_to_befriend);
    for (auto &node : graph.nodes.at(node_to_befriend)->plotting_me) {
        if (is_in_vector(path.path, node->name))
            continue;
        paths.push_back(get_path(node->name, n, path));
    }
    return get_smallest_path(paths);
}

PathToTakeDown Conspiracy::get_path(std::string node_to_take_down, int n, PathToTakeDown path)
{
    std::vector<PathToTakeDown> paths;

    path.length++;
    path.path.push_back(node_to_take_down);
    for (auto &node : graph.nodes.at(node_to_take_down)->plotting_me) {
        if (is_in_vector(path.path, node->name))
            continue;
        if (matrix.distance(node->name, QUEEN) <= n) {
            path.path.push_back(node->name);
            path.length++;
            return path;
        }
        else {
            paths.push_back(befriend(node->name, n, path));
        }
    }
    return get_smallest_path(paths);
}