/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <iostream>
#include <queue>
#include <thread>
#include <optional>

#include "../Wrappers/CountingSemaphore.hpp"
#include "Cook.hpp"

class Kitchen
{
private:
    const uint16_t _maxCooks;
    const double _cookingTime;
    std::optional<std::chrono::milliseconds> _reloadTime;

    std::shared_ptr<std::atomic<bool>> _isRunning = std::make_shared<std::atomic<bool>>(true);
    std::mutex _mutex;

    CountingSemaphore _nbCooks;
    std::vector<std::pair<Cook, std::thread>> _cooks;

    std::queue<Pizza> _waitingPizzas;
    CountingSemaphore _asWaitingPizzas{0};
    std::thread _cooksManager;

    std::vector<std::shared_ptr<BalancingSemaphore>> _ingredients;
    std::vector<std::thread> _threadsIngredients;

    std::ostream& _os;

public:
    Kitchen(uint16_t maxCooks, double cookingTime, std::optional<std::chrono::milliseconds> reloadTime,
            std::ostream& os = std::cout);
    ~Kitchen();

    bool orderPizza(Pizza pizza);

    [[nodiscard]] uint16_t getMaxCooks() const { return _maxCooks; }
    [[nodiscard]] double getCookingTime() const { return _cookingTime; }
    [[nodiscard]] std::optional<std::chrono::milliseconds> getReloadTime() const { return _reloadTime; }
    [[nodiscard]] std::shared_ptr<std::atomic<bool>> getIsRunning() const { return _isRunning; }
    [[nodiscard]] CountingSemaphore& getNbCooks() { return _nbCooks; }
    [[nodiscard]] std::queue<Pizza>& getWaitingPizzas() { return _waitingPizzas; }
    [[nodiscard]] CountingSemaphore& getAsWaitingPizzas() { return _asWaitingPizzas; }
    [[nodiscard]] std::vector<std::shared_ptr<BalancingSemaphore>>& getIngredients() { return _ingredients; }

    friend std::ostream& operator<<(std::ostream& os, const Kitchen& kitchen);
};

#endif // KITCHEN_HPP
