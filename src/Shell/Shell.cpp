/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#include <cstdint>
#include <stdexcept>
#include <string>
#include <iostream>
#include <sstream>

#include "Shell.hpp"

using namespace Plazza;

PizzaType Shell::parsePizzaType(std::string_view type) {
    try {
        return utils::enum_traits<PizzaType>::from_string.at(type);
    } catch (const std::out_of_range &) {
        throw std::invalid_argument("Invalid pizza type.");
    }
}

PizzaSize Shell::parsePizzaSize(std::string_view size) {
    try {
        return utils::enum_traits<PizzaSize>::from_string.at(size);
    } catch (const std::out_of_range &) {
        throw std::invalid_argument("Invalid pizza size.");
    }
}

std::uint32_t Shell::parseAmount(std::string_view amountStr) {
    if (amountStr[0] != 'x')
        throw std::invalid_argument("Amount must start with 'x'");

    int amount = std::stoi(std::string(amountStr.substr(1)));
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than 0");
    return amount;
}


Order Shell::parseOrder(std::string_view input) {
    std::istringstream iss((std::string(input)));
    std::string sType, sSize, amountStr;

    if (!(iss >> sType >> sSize >> amountStr)) {
        throw std::invalid_argument("Invalid input format.\nTry: Pizza Size Amount");
    } else {
        PizzaType type = parsePizzaType(sType);
        PizzaSize size = parsePizzaSize(sSize);
        std::uint32_t amount = parseAmount(amountStr);
        return {type, size, amount};
    }
}

void Shell::run() {
    std::cout << "You have to write your order like this :" << std::endl;
    std::cout << "The pizza you want to order: Margarita, Regina, Americana, Fantasia" << std::endl;
    std::cout << "The size you want for your pizza: S, M, L, XL, XXL" << std::endl;
    std::cout << "The amount of pizza you want like: x1, x2, x3 ..." << std::endl;
    std::cout << "All in one line like this : Pizza Size Amount" << std::endl;
    std::cout << "Example: Margarita XL x2" << std::endl;
    std::cout << "To exit the program, write 'exit'\n" << std::endl;
    while (_status) {
        try {
            std::string input;
            std::cout << "Plazza> ";
            std::getline(std::cin, input);

            if (input == "exit") {
                _status = false;
                break;
            }
            Order order = parseOrder(input);
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
