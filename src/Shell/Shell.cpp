/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#include <string>
#include <iostream>
#include <sstream>
#include "Shell.hpp"

Shell::Shell() {}
Shell::~Shell() {}

PizzaType Shell::parsePizzaType(const std::string& type) {
    for (const auto& pair : pizzaName) {
        if (pair.second == type)
            return pair.first;
    }
    throw std::invalid_argument("Invalid pizza type.");
}

PizzaSize Shell::parsePizzaSize(const std::string& size) {
    for (const auto& pair : pizzaSize) {
        if (pair.second == size)
            return pair.first;
    }
    throw std::invalid_argument("Invalid pizza size.");
}

int Shell::parseAmount(const std::string& amountStr) {
    if (amountStr[0] != 'x')
        throw std::invalid_argument("Amount must start with 'x'");

    int amount = std::stoi(amountStr.substr(1));
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than 0");
    return amount;
}


Order Shell::parseOrder(const std::string &input) {
    std::istringstream iss(input);
    std::string sType, sSize, amountStr;

    if (!(iss >> sType >> sSize >> amountStr)) {
        throw std::invalid_argument("Invalid input format.\nTry: Pizza Size Amount");
    } else {
        PizzaType type = parsePizzaType(sType);
        PizzaSize size = parsePizzaSize(sSize);
        int amount = parseAmount(amountStr);
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

constexpr PizzaType Order::getType() const noexcept {
    return _type;
}

constexpr PizzaSize Order::getSize() const noexcept {
    return _size;
}

constexpr int Order::getQuantity() const noexcept {
    return _quantity;
}
