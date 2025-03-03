#include "Matrix.hpp"
#include "Matrix.hpp"
#include <iostream>
#include "Conspiracy.hpp"

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

int links(int ac, char **av)
{
    Matrix matrix = Matrix::parse_graph(av[2], " is friends with ");
    matrix.print_legend(std::cout);
    std::cout << matrix;
    return 0;
}

int plots(std::string relationship_file, std::string matrix_file, std::string nb)
{
    int n = std::stoi(nb);

    if (n < 0) {
        throw std::runtime_error("n must be a positive integer");
    }
    Conspiracy conspiracy(relationship_file, matrix_file);
    conspiracy.graph.display_graph();
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
            return links(ac, av);
        } else {
            return plots(av[2], av[3], av[4]);
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    return 0;
}
