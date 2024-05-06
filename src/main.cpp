/*
** EPITECH PROJECT, 2024
** The Plazza
** File description:
** Program entrypoint
*/

#include <chrono>
#include <iostream>
#include <sstream>
#include <utility>

static const char USAGE[] = " [SPEED MULTIPLIER] [COOK COUNT] [RESTOCK TIME]\n\n"
"Starts The Plazza with kitchens restocking every RESTOCK TIME milliseconds\n"
"and having COOK COUNT cooks cooking at a speed of SPEED MULTIPLIER times the\n"
"normal speed.\n",
    INVALID_SPEED_MULTIPLIER[] = "Invalid speed multiplier",
    INVALID_COOK_COUNT[] = "Invalid cook count",
    INVALID_RESTOCK_DELAY[] = "Invalid restock delay";

static std::ostream &printUsage(std::ostream &os, const char * const command)
{
    return os << "Usage: " << command << USAGE;
}

template<typename T>
static T parseArg(std::string &&input, const char * const message)
{
    std::istringstream ss(std::forward<std::string>(input));
    T output;
    std::string rest;

    if (!(ss >> output) || (ss >> rest))
        throw std::runtime_error(message);
    return output;
}

int main(const int argc, const char * const * const argv)
{
    if (argc != 4) {
        printUsage(std::cerr, argv[0]);
        return 84;
    }

    auto speed = parseArg<double>(argv[1], INVALID_SPEED_MULTIPLIER);
    auto cookCount = parseArg<std::uint16_t>(argv[2], INVALID_COOK_COUNT);
    std::chrono::milliseconds restockDelay(parseArg<std::uint64_t>(argv[3], INVALID_RESTOCK_DELAY));

    return 0;
}