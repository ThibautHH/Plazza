/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Cook
*/

#ifndef COOK_HPP
#define COOK_HPP

#include <memory>

#include "../Pizza.hpp"
#include "../Wrappers/BalancingSemaphore.hpp"

class Cook {
private:
    const uint16_t _id;
    float _cookingTime;
    Pizza _pizza;

    bool _isBusy = false;

    std::chrono::system_clock::time_point _endCookingTime;

public:
    Cook(const uint16_t id, const float cookingTime) : _id(id), _cookingTime(cookingTime) {}

    void cook(Pizza pizza, const std::vector<std::shared_ptr<BalancingSemaphore>> &ingredients, std::mutex &mutex,
              std::ostream &os);

    [[nodiscard]] uint16_t getId() const { return _id; }
    [[nodiscard]] float getCookingTime() const { return _cookingTime; }
    [[nodiscard]] Pizza getPizza() const { return _pizza; }
    [[nodiscard]] bool isBusy() const { return _isBusy; }
    [[nodiscard]] std::chrono::system_clock::time_point getEndCookingTime() const { return _endCookingTime; }

    void setBusy(const bool isBusy) { _isBusy = isBusy; }

    friend std::ostream &operator<<(std::ostream &os, const Cook &cook);
};

#endif // COOK_HPP
