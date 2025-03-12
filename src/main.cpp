#include "Matrix.hpp"
#include "Matrix.hpp"
#include <iostream>
#include "Conspiracy.hpp"
#include <algorithm>

void help()
{
    printf("./game_of_stones --help\n"
    "USAGE\n"
    "\t./game_of_stones [--links FR P1 P2 | --plots FR CR n]\n\n"
    "DESCRIPTION\n"
    "\tFR\tfile containing friendship relations between people\n"
    "\tPi\tname of someone in the friendships file\n"
    "\tCR\tfile containing conspiracies intentions\n"
    "\tn\tmaximum length of friendship paths\n");
}

int links(char **av)
{
    int n = std::stoi(av[4]);

    if (n < 0) {
        throw std::runtime_error("n must be a positive integer");
    }
    Matrix matrix = Matrix::parse_graph(av[2], " is friends with ", (unsigned int)n);

    std::cout << "Degree of separation between " << av[3] << " and " << av[4] << ":" << matrix.distance(av[3], av[4]) << std::endl;
    return 0;
}

int plots(std::string relationship_file, std::string matrix_file, std::string nb)
{
    bool treason = false;
    int n = std::stoi(nb);

    if (n < 0) {
        throw std::runtime_error("n must be a positive integer");
    }
    Conspiracy conspiracy(relationship_file, matrix_file, (unsigned int)n);
    
    conspiracy.display_matrix();

    std::vector<PathToTakeDown> paths;
    std::vector<std::string> no_conspiracy_messages;
    for (auto &node : conspiracy.graph.nodes.at(QUEEN)->plotting_me) {
        PathToTakeDown path = conspiracy.get_path(node->name, n, PathToTakeDown());
        if (path.length == -1) {
            treason = true;
            no_conspiracy_messages.push_back("No conspiracy possible against " + node->name);
        } else {
            paths.push_back(path);
        }
    }

    std::sort(paths.begin(), paths.end(), [](const PathToTakeDown &a, const PathToTakeDown &b) {
        if (a.length == b.length) {
            return a.path > b.path;
        }
        return a.length < b.length;
    });
    std::cout << "Conspiracies:" << std::endl;
    for (const auto &path : paths) {
        for (auto it = path.path.rbegin(); it != path.path.rend();) {
            std::cout << *it << (++it == path.path.rend() ? "" : " -> ");
        }
        std::cout << std::endl;
    }

    for (const auto &message : no_conspiracy_messages) {
        std::cout << message << std::endl;
    }

    std::cout << "\nResult:" << std::endl;
    if (treason)
        std::cout << "There is only one way out: treason!" << std::endl;
    else
        std::cout << "The stone is safe!" << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    (void)ac;
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h")) {
        help();
        return 0;
    }
    if (ac != 5 || (std::string(av[1]) != "--links" && std::string(av[1]) != "--plots")) {
        std::cerr << "Invalid arguments" << std::endl;
        return 84;
    }
    try {
        if (std::string(av[1]) == "--links") {
            return links(av);
        } else {
            return plots(av[2], av[3], av[4]);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
