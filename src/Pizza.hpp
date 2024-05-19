/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza
*/

#ifndef PIZZA_HPP
#define PIZZA_HPP

#include <map>

enum PizzaType { Regina = 1, Margarita = 2, Americana = 3, Fantasia = 4 };

enum PizzaSize { S = 1, M = 2, L = 3, XL = 4, XXL = 5 };

enum Ingredient {
    DOUGH          = 0b000000001,
    TOMATO         = 0b000000010,
    GRUYERE        = 0b000000100,
    HAM            = 0b000001000,
    MUSHROOMS      = 0b000010000,
    STEAK          = 0b000100000,
    EGGPLANT       = 0b001000000,
    GOAT_CHEESE    = 0b010000000,
    CHIEF_LOVE     = 0b100000000,
    NB_INGREDIENTS = 9
};

struct Pizza {
    PizzaType type;
    PizzaSize size;
    uint16_t number;
};

static const std::map<Ingredient, std::string_view> ingredientName = {
    {DOUGH, "Dough"},       {TOMATO, "Tomato"},           {GRUYERE, "Gruyere"},
    {HAM, "Ham"},           {MUSHROOMS, "Mushrooms"},     {STEAK, "Steak"},
    {EGGPLANT, "Eggplant"}, {GOAT_CHEESE, "Goat Cheese"}, {CHIEF_LOVE, "Chief Love"}};


static const std::map<PizzaType, std::pair<uint8_t, uint16_t>> pizzaRecipe = {
    {Regina, {1, {DOUGH | TOMATO | GRUYERE | HAM}}},
    {Margarita, {2, {DOUGH | TOMATO | GRUYERE}}},
    {Americana, {2, {DOUGH | TOMATO | GRUYERE | HAM | EGGPLANT}}},
    {Fantasia, {4, {DOUGH | TOMATO | GOAT_CHEESE | CHIEF_LOVE}}}};

static const std::map<PizzaType, std::string_view> pizzaName = {
    {Regina, "Regina"}, {Margarita, "Margarita"}, {Americana, "Americana"}, {Fantasia, "Fantasia"}};

static const std::map<PizzaSize, std::string_view> pizzaSize = {{S, "S"}, {M, "M"}, {L, "L"}, {XL, "XL"}, {XXL, "XXL"}};


#endif // PIZZA_HPP
