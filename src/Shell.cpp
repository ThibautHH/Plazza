/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#include <iostream>
#include <unistd.h>

#include "Utils.hpp"

#include "Shell.hpp"

using namespace Plazza;

Shell::Shell(Reception &reception)
    : _reception(reception)
{}

static std::optional<bool> isCommandExit(std::string command)
{
    std::istringstream iss(std::move(command));
    command.clear();
    iss >> command;
    if (command.empty())
        return std::nullopt;
    bool ret = command == "exit";
    command.clear();
    iss >> command;
    if (!command.empty())
        return false;
    return ret;
}

std::list<Order> Shell::parseOrders(std::string commandLine, bool &exited)
{
    std::list<Order> orders;
    bool processed = false;
    for (std::istringstream command(std::move(commandLine));
        std::getline(command, commandLine, ';') && !processed;
        processed = command.eof()) {
        const auto res = isCommandExit(commandLine);
        if (!res.has_value())
            continue;
        if (res.value()) {
            exited = true;
            break;
        }
        std::istringstream iss(std::move(commandLine));
        auto order = utils::extract<Order>(iss);
        commandLine.clear();
        iss >> commandLine;
        if (!order.has_value() || !commandLine.empty()) {
            if (isatty(STDIN_FILENO))
                std::cerr << "Invalid command" << std::endl;
            continue;
        }
        orders.push_back(*order);
        if (isatty(STDIN_FILENO))
            std::cout << PizzaTypeTraits::pushalpha << PizzaSizeTraits::pushalpha
                << PizzaTypeTraits::alpha << PizzaSizeTraits::alpha
                << "Ordered " << order->quantity << " \"" << order->type << "\" pizza in size " << order->size << std::endl
                << PizzaTypeTraits::popalpha << PizzaSizeTraits::popalpha;
    }
    return orders;
}

void Shell::run()
{
    if (isatty(STDIN_FILENO))
        std::cout << "You have to write your order like this:\n"
            "- The pizza you want to order: Margarita, Regina, Americana, Fantasia\n"
            "- The size you want for your pizza: S, M, L, XL, XXL\n"
            "- The amount of pizza you want like: x1, x2, x3...\n"
            "All on one line like this: <type> <size> x<amount>\n"
            "Example: Margarita XL x2\n"
            "To exit the program, write 'exit'\n" << std::endl;

    std::string commandLine;
    for (bool exited = false; !exited;) {
        if (isatty(STDIN_FILENO))
            std::cout << "Plazza> ";
        std::getline(std::cin, commandLine);
        for (auto order : parseOrders(commandLine, exited))
            /*_reception.addOrder(order)*/;
        if (std::cin.eof()) {
            std::cout << std::endl;
            break;
        }
    }
}
