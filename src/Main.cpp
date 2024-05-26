/*
** EPITECH PROJECT, 2024
** The Plazza
** File description:
** Program entrypoint
*/

#include <chrono>
#include <iostream>
#include <optional>
#include <sstream>
#include <utility>

#include "Reception/Reception.hpp"

static const char USAGE[] = " [SPEED MULTIPLIER] [COOK COUNT] [RESTOCK DELAY]\n\n"
                      "Starts The Plazza with kitchens restocking every RESTOCK DELAY milliseconds\n"
                      "and having COOK COUNT cooks cooking at a speed of SPEED MULTIPLIER times the\n"
                      "normal speed.\n\n"
                      "If RESTOCK DELAY is 0, the kitchens will never run out of ingredients.\n"
                      "If RESTOCK DELAY is negative, the kitchens will never restock.\n",
                  INVALID_SPEED_MULTIPLIER[] = "Invalid speed multiplier",
                  INVALID_COOK_COUNT[] = "Invalid cook count",
                  INVALID_RESTOCK_DELAY[] = "Invalid restock delay";

using namespace std::chrono_literals;

static std::ostream& printUsage(std::ostream& os, const char* const command)
{
    return os << "Usage: " << command << USAGE;
}

template <typename T>
static T parseArg(std::string&& input, const char* const message)
{
    std::istringstream ss(std::forward<std::string>(input));
    T output;
    std::string rest;

    if (!(ss >> output) || (ss >> rest))
        throw std::runtime_error(message);
    return output;
}

int main(const int argc, const char* const * const argv)
{
    if (argc != 4)
    {
        printUsage(std::cerr, argv[0]);
        return 84;
    }

    auto speed = parseArg<double>(argv[1], INVALID_SPEED_MULTIPLIER);
    if (speed < 0)
        throw std::runtime_error(INVALID_SPEED_MULTIPLIER);
    auto cookCount = parseArg<std::uint16_t>(argv[2], INVALID_COOK_COUNT);
    if (static_cast<std::int16_t>(cookCount) <= 0)
        throw std::runtime_error(INVALID_COOK_COUNT);
    std::optional<std::chrono::milliseconds> restockDelay(parseArg<std::int64_t>(argv[3], INVALID_RESTOCK_DELAY));
    if (restockDelay < 0ms)
        restockDelay = std::nullopt;

    try
    {
        Reception reception(
            cookCount,
            speed,
            restockDelay
        );
        reception.run();
    }
    catch (const std::exception&)
    {
        std::cerr << "Invalid arguments." << std::endl;
        return 84;
    }

    return 0;
}
