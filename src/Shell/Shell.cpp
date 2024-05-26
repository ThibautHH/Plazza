/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#include <sstream>
#include <functional>

#include "Shell.hpp"

PizzaType Shell::parsePizzaType(const std::string &type)
{
    for (const auto &[pizzaType, pizzaName] : pizzaName)
        if (pizzaName == type)
            return pizzaType;

    throw std::invalid_argument("Invalid pizza type.");
}

PizzaSize Shell::parsePizzaSize(const std::string &size)
{
    for (const auto &[pizzaSize, pizzaName] : pizzaSize)
        if (pizzaName == size)
            return pizzaSize;

    throw std::invalid_argument("Invalid pizza size.");
}

int Shell::parseAmount(const std::string &amountStr)
{
    if (amountStr[0] != 'x')
        throw std::invalid_argument("Amount must start with 'x'");

    const int amount = std::stoi(amountStr.substr(1));
    if (amount <= 0)
        throw std::invalid_argument("Amount must be greater than 0");
    return amount;
}


Order Shell::parseOrder(const std::string &input)
{
    std::istringstream iss(input);
    std::string sType, sSize, amountStr;

    if (!(iss >> sType >> sSize >> amountStr))
        throw std::invalid_argument("Invalid input format.\nTry: Pizza Size Amount");

    return {parsePizzaType(sType), parsePizzaSize(sSize), parseAmount(amountStr)};
}

void Shell::run(const std::function<void(Order)> &orderCallback)
{
    std::cout <<
        "You have to write your order like this :"
        "\nThe pizza you want to order: margarita, regina, americana, fantasia"
        "\nThe size you want for your pizza: S, M, L, XL, XXL"
        "\nThe amount of pizza you want like: x1, x2, x3 ..."
        "\nAll in one line like this : Pizza Size Amount"
        "\nExample: margarita XL x2"
        "\nTo exit the program, write 'exit'\n" << std::endl;

    while (_status) {
        try {
            std::string input;
            std::cout << "Plazza> ";
            std::getline(std::cin, input);

            if (input == "exit") {
                _status = false;
                break;
            }
            orderCallback(parseOrder(input));
        } catch (std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
