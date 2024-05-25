/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

using namespace Plazza;

template<>
const std::vector<PizzaType> utils::enum_traits<PizzaType>::valid_values = {
    Regina, Margarita, Americana, Fantasia
};
template<>
utils::enum_traits<PizzaType>::to_string_type utils::enum_traits<PizzaType>::to_string = {
    {Regina, nameof(Regina)},
    {Margarita, nameof(Margarita)},
    {Americana, nameof(Americana)},
    {Fantasia, nameof(Fantasia)}
};
template<>
utils::enum_traits<PizzaType>::from_string_type utils::enum_traits<PizzaType>::from_string = {
    {nameof(Regina), Regina},
    {nameof(Margarita), Margarita},
    {nameof(Americana), Americana},
    {nameof(Fantasia), Fantasia}
};

template<>
const std::vector<PizzaSize> utils::enum_traits<PizzaSize>::valid_values = {
    S, M, L, XL, XXL
};
template<>
utils::enum_traits<PizzaSize>::to_string_type utils::enum_traits<PizzaSize>::to_string = {
    {S, nameof(S)},
    {M, nameof(M)},
    {L, nameof(L)},
    {XL, nameof(XL)},
    {XXL, nameof(XXL)}
};
template<>
utils::enum_traits<PizzaSize>::from_string_type utils::enum_traits<PizzaSize>::from_string = {
    {nameof(S), S},
    {nameof(M), M},
    {nameof(L), L},
    {nameof(XL), XL},
    {nameof(XXL), XXL}
};
