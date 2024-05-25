/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza
*/

#ifndef PLAZZA_PIZZA_HPP_
    #define PLAZZA_PIZZA_HPP_

    #include <algorithm>
    #include <cstdint>
    #include <iostream>
    #include <sstream>

    #include "Utils.hpp"

namespace Plazza {
    enum PizzaType { Regina = 1, Margarita = 2, Americana = 4, Fantasia = 8 };

    enum PizzaSize { S = 1, M = 2, L = 4, XL = 8, XXL = 16 };

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

    static const std::unordered_map<Ingredient, std::string_view> ingredientName = {
        {DOUGH, "Dough"},       {TOMATO, "Tomato"},           {GRUYERE, "Gruyere"},
        {HAM, "Ham"},           {MUSHROOMS, "Mushrooms"},     {STEAK, "Steak"},
        {EGGPLANT, "Eggplant"}, {GOAT_CHEESE, "Goat Cheese"}, {CHIEF_LOVE, "Chief Love"}
    };


    static const std::unordered_map<PizzaType, std::pair<std::uint8_t, std::uint16_t>> pizzaRecipe = {
        {Regina, {1, {DOUGH | TOMATO | GRUYERE | HAM}}},
        {Margarita, {2, {DOUGH | TOMATO | GRUYERE}}},
        {Americana, {2, {DOUGH | TOMATO | GRUYERE | HAM | EGGPLANT}}},
        {Fantasia, {4, {DOUGH | TOMATO | GOAT_CHEESE | CHIEF_LOVE}}}
    };

    struct Pizza {
        PizzaType type;
        PizzaSize size;
    };

    template<typename T> requires std::is_enum_v<T>
    inline std::ostream& operator<<(std::ostream& os, T value)
    {
        if (os.iword(utils::enum_traits<T>::xalloc_index))
            os << utils::enum_traits<T>::to_string.at(value);
        else
            os << static_cast<std::underlying_type_t<T>>(value);
        return os;
    }

    template<typename T> requires std::is_enum_v<T>
    inline std::istream& operator>>(std::istream& is, T& value)
    {
        std::string word;
        is >> word;
        if (is.iword(utils::enum_traits<T>::xalloc_index))
            try {
                value = utils::enum_traits<T>::from_string.at(word);
            } catch (const std::out_of_range &) {
                is.setstate(std::ios_base::failbit);
            }
        else {
            std::underlying_type_t<T> v = 0;
            utils::extract(std::istringstream(word), v, is);
            const auto end = std::end(utils::enum_traits<T>::valid_values);
            if (std::find(std::begin(utils::enum_traits<T>::valid_values), end, static_cast<T>(v)) == end)
                is.setstate(std::ios_base::failbit);
            else
                value = static_cast<T>(v);
        }
        return is;
    }

    inline std::ostream &operator<<(std::ostream &os, Pizza pizza)
    {
        return os << pizza.type << ':' << pizza.size;
    }

    inline std::istream& operator>>(std::istream &is, Pizza &pizza)
    {
        std::string word;
        is >> word;
        std::istringstream ps(word);
        if (std::getline(ps, word, ':').eof())
            is.setstate(std::ios_base::failbit);
        utils::extract(utils::enum_traits<PizzaType>::copy_alpha(std::istringstream(word), is),
            pizza.type, is);
        if (!std::getline(ps, word, ':').eof())
            is.setstate(std::ios_base::failbit);
        utils::extract(utils::enum_traits<PizzaSize>::copy_alpha(std::istringstream(word), is),
            pizza.size, is);
        return is;
    }
}

#endif /* !PLAZZA_PIZZA_HPP_ */
