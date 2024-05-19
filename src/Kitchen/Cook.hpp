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
#include <memory>

#include "../Pizza.hpp"
#include "../Wrappers/BalancingSemaphore.hpp"

class Cook {
private:
    const uint16_t _id;
    uint16_t _cookingTime;
    Pizza _pizza;

    bool _isCooking = false;

    std::chrono::system_clock::time_point _endCookingTime;

public:
    Cook(const uint16_t id, const uint16_t cookingTime) : _id(id), _cookingTime(cookingTime) {}

    void cook(Pizza pizza, const std::vector<std::shared_ptr<BalancingSemaphore>> &ingredients, std::mutex &mutex);

    [[nodiscard]] uint16_t getId() const { return _id; }
    [[nodiscard]] uint16_t getCookingTime() const { return _cookingTime; }
    [[nodiscard]] Pizza getPizza() const { return _pizza; }
    [[nodiscard]] bool isCooking() const { return _isCooking; }
    [[nodiscard]] std::chrono::system_clock::time_point getEndCookingTime() const { return _endCookingTime; }

    friend std::ostream &operator<<(std::ostream &os, const Cook &cook);
};

#endif // COOK_HPP