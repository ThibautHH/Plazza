/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza
*/

#ifndef PIZZA_HPP
#define PIZZA_HPP

#include <cstdint>

enum PizzaType { Regina = 1, Margarita = 2, Americana = 3, Fantasia = 4 };

enum PizzaSize { S = 1, M = 2, L = 3, XL = 4, XXL = 5 };

enum Ingredient {
    DOUGH       = 0b000000001,
    TOMATO      = 0b000000010,
    GRUYERE     = 0b000000100,
    HAM         = 0b000001000,
    MUSHROOMS   = 0b000010000,
    STEAK       = 0b000100000,
    EGGPLANT    = 0b001000000,
    GOAT_CHEESE = 0b010000000,
    CHIEF_LOVE  = 0b100000000
};

struct Pizza {
    PizzaType type;
    PizzaSize size;
    uint16_t number;
};

#endif // PIZZA_HPP
