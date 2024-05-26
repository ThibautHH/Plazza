/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

using namespace Plazza;

template<>
const std::vector<PizzaType> PizzaTypeTraits::valid_values = {
    Regina, Margarita, Americana, Fantasia
};
template<>
PizzaTypeTraits::to_string_type PizzaTypeTraits::to_string = {
    {Regina, nameof(Regina)},
    {Margarita, nameof(Margarita)},
    {Americana, nameof(Americana)},
    {Fantasia, nameof(Fantasia)}
};
template<>
PizzaTypeTraits::from_string_type PizzaTypeTraits::from_string = {
    {nameof(Regina), Regina},
    {nameof(Margarita), Margarita},
    {nameof(Americana), Americana},
    {nameof(Fantasia), Fantasia}
};

template<>
const std::vector<PizzaSize> PizzaSizeTraits::valid_values = {
    S, M, L, XL, XXL
};
template<>
PizzaSizeTraits::to_string_type PizzaSizeTraits::to_string = {
    {S, nameof(S)},
    {M, nameof(M)},
    {L, nameof(L)},
    {XL, nameof(XL)},
    {XXL, nameof(XXL)}
};
template<>
PizzaSizeTraits::from_string_type PizzaSizeTraits::from_string = {
    {nameof(S), S},
    {nameof(M), M},
    {nameof(L), L},
    {nameof(XL), XL},
    {nameof(XXL), XXL}
};
