/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Cook
*/

#ifndef COOK_HPP
#define COOK_HPP

#include <chrono>
#include <iostream>
#include <map>
#include <thread>

#include "../Pizza.hpp"

static const std::map<PizzaType, std::pair<uint8_t, uint16_t>> pizzaRecipe = {
    {Regina, {1, {DOUGH | TOMATO | GRUYERE | HAM}}},
    {Margarita, {2, {DOUGH | TOMATO | GRUYERE}}},
    {Americana, {2, {DOUGH | TOMATO | GRUYERE | HAM | EGGPLANT}}},
    {Fantasia, {4, {DOUGH | TOMATO | GOAT_CHEESE | CHIEF_LOVE}}}};

static const std::map<PizzaType, std::string_view> pizzaName = {
    {Regina, "Regina"}, {Margarita, "Margarita"}, {Americana, "Americana"}, {Fantasia, "Fantasia"}};

static const std::map<Ingredient, std::string_view> ingredientName = {
    {DOUGH, "Dough"},       {TOMATO, "Tomato"},           {GRUYERE, "Gruyere"},
    {HAM, "Ham"},           {MUSHROOMS, "Mushrooms"},     {STEAK, "Steak"},
    {EGGPLANT, "Eggplant"}, {GOAT_CHEESE, "Goat Cheese"}, {CHIEF_LOVE, "Chief Love"}};

static const std::map<PizzaSize, std::string_view> pizzaSize = {{S, "S"}, {M, "M"}, {L, "L"}, {XL, "XL"}, {XXL, "XXL"}};

class Cook {
private:
    const uint16_t _id;
    uint16_t _cookingTime;
    Pizza _pizza;

    bool _isCooking = false;

    std::chrono::system_clock::time_point _endCookingTime;

public:
    Cook(const uint16_t id, const uint16_t cookingTime) : _id(id), _cookingTime(cookingTime) {}

    void cook(const Pizza pizza, std::mutex &mutex)
    {
        mutex.lock();
        _pizza     = pizza;
        _isCooking = true;

        const auto duration = std::chrono::milliseconds(_cookingTime * pizzaRecipe.at(_pizza.type).first * 1000);
        _endCookingTime     = std::chrono::system_clock::now() + duration;
        mutex.unlock();

        for (uint16_t i = 0; i < _pizza.number; i++)
            std::this_thread::sleep_for(duration);

        mutex.lock();
        _isCooking = false;

        std::cout << "Cook " << _id << " finished cooking a " << pizzaName.at(_pizza.type) << " "
                  << pizzaSize.at(_pizza.size) << " x" << _pizza.number << std::endl;
        mutex.unlock();
    }

    [[nodiscard]] uint16_t getId() const { return _id; }
    [[nodiscard]] uint16_t getCookingTime() const { return _cookingTime; }
    [[nodiscard]] Pizza getPizza() const { return _pizza; }
    [[nodiscard]] bool isCooking() const { return _isCooking; }
    [[nodiscard]] std::chrono::system_clock::time_point getEndCookingTime() const { return _endCookingTime; }

    friend std::ostream &operator<<(std::ostream &os, const Cook &cook)
    {

        if (const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(cook.getEndCookingTime() -
                                                                                    std::chrono::system_clock::now())
                                  .count();
            cook.isCooking() && diff > 0)
            os << "Cook " << cook.getId() + 1 << " is cooking a " << pizzaName.at(cook.getPizza().type) << " "
               << pizzaSize.at(cook.getPizza().size) << " x" << cook.getPizza().number << " end in " << diff << "ms";

        else
            os << "Cook " << cook.getId() << " is waiting for a pizza";
        return os;
    }
};

#endif // COOK_HPP
