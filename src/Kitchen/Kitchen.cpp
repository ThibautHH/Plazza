/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(const uint16_t maxCooks, const uint16_t cookingTime, const uint32_t reloadTime) :
    _maxCooks(maxCooks), _cookingTime(cookingTime), _reloadTime(reloadTime)
{
    for (uint16_t i = 0; i < _maxCooks; i++)
        _cooks.emplace_back(Cook(i + 1, _cookingTime), std::thread());

    for (uint16_t i = 0; i < NB_INGREDIENTS; i++) {
        _ingredients.emplace_back(std::make_shared<BalancingSemaphore>(5));
        _threadsIngredients.emplace_back(
            [this, i]
            {
                while (*_isRunning)
                    _ingredients[i]->release([] { std::this_thread::sleep_for(std::chrono::milliseconds(1000)); });
            });
    }

    _cooksManager = std::thread(
        [this]
        {
            while (*_isRunning) {
                _asWaitingPizzas.acquire();
                if (!*_isRunning)
                    continue;
                _nbCooks.wait();
                if (!_waitingPizzas.empty()) {
                    for (auto &[cook, thread] : _cooks)
                        if (!cook.isBusy()) {
                            if (thread.joinable())
                                thread.join();

                            const auto &pizza = _waitingPizzas.front();
                            _waitingPizzas.pop();

                            _nbCooks.acquire();
                            cook.setBusy(true);

                            thread = std::thread(
                                [this, pizza, &cook]
                                {
                                    cook.cook(pizza, _ingredients, _mutex);
                                    _nbCooks.release();
                                });
                            break;
                        }
                }
            }
        });
}

Kitchen::~Kitchen()
{
    for (auto &[cook, thread] : _cooks)
        if (thread.joinable())
            thread.join();
    *_isRunning = false;
    for (const auto &ingredient : _ingredients)
        ingredient->acquire();
    for (auto &thread : _threadsIngredients)
        thread.join();
    _asWaitingPizzas.release();
    _cooksManager.join();
}

bool Kitchen::orderPizza(const Pizza pizza)
{
    if (_maxCooks - _nbCooks.getValue() + _waitingPizzas.size() >= _maxCooks * 2)
        return false;

    _asWaitingPizzas.release();
    _waitingPizzas.push(pizza);
    return true;
}

std::ostream &operator<<(std::ostream &os, const Kitchen &kitchen)
{
    os << "Kitchen: (" << kitchen._maxCooks - kitchen._nbCooks.getValue() + kitchen._waitingPizzas.size() << "/"
       << kitchen._maxCooks << " cooks)\n  Cooks:";
    for (const auto &[cook, thread] : kitchen._cooks)
        os << "\n    " << cook;
    os << "\n  Ingredients:";
    for (uint16_t i = 0; i < NB_INGREDIENTS; i++)
        os << "\n    " << ingredientName.at(static_cast<Ingredient>(1 << i)) << ": "
           << kitchen._ingredients[i]->getValue();

    return os;
}
