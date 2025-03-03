#include <iostream>

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

int links()
{
    printf("links\n");
    return 0;
}

int plots()
{
    printf("plots\n");
    return 0;
}

int main(int ac, char **av) {
    if (ac == 2 && (std::string(av[1]) == "--help" || std::string(av[1]) == "-h")) {
        help();
        return 0;
    }
    if (ac != 5 || (std::string(av[1]) != "--links" && std::string(av[1]) != "--plots")) {
        std::cerr << "Invalid arguments" << std::endl;
        return 84;
    }
    if (std::string(av[1]) == "--links") {
        return links();
    } else {
        return plots();
    }
    return 0;
}
