/*
** EPITECH PROJECT, 2024
** The Plazza
** File description:
** Program entrypoint
*/

#include <iostream>

static const char USAGE[] = " [SPEED MULTIPLIER] [COOK COUNT] [RESTOCK TIME]\n\n"
"Starts The Plazza with kitchens restocking every RESTOCK TIME milliseconds\n"
"and having COOK COUNT cooks cooking at a speed of SPEED MULTIPLIER times the\n"
"normal speed.\n";

static std::ostream &printUsage(std::ostream &os, const char * const command)
{
    return os << "Usage: " << command << USAGE;
}

int main(const int argc, const char * const * const argv)
{
    if (argc != 4) {
        printUsage(std::cerr, argv[0]);
        return 84;
    }

    return 0;
}
