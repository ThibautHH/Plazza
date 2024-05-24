/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#ifndef PLAZZA_KITCHEN_KITCHEN_HPP_
    #define PLAZZA_KITCHEN_KITCHEN_HPP_

    #include <iostream>
    #include <mutex>
    #include <queue>
    #include <thread>

    #include "../Wrappers/CountingSemaphore.hpp"
    #include "Cook.hpp"

namespace Plazza::Kitchen {
    class Kitchen {
        private:
            const uint16_t _maxCooks;
            const float _cookingTime;
            const uint32_t _reloadTime;

            std::shared_ptr<std::atomic<bool>> _isRunning = std::make_shared<std::atomic<bool>>(true);
            std::mutex _mutex;

            CountingSemaphore _nbCooks{5};
            std::vector<std::pair<Cook, std::thread>> _cooks;

            std::queue<Pizza> _waitingPizzas;
            CountingSemaphore _asWaitingPizzas{0};
            std::thread _cooksManager;

            std::vector<std::shared_ptr<BalancingSemaphore>> _ingredients;
            std::vector<std::thread> _threadsIngredients;

            std::ostream &_os;

        public:
            Kitchen(uint16_t maxCooks, uint16_t cookingTime, uint32_t reloadTime, std::ostream &os = std::cout);
            ~Kitchen();

            bool orderPizza(Pizza pizza);

            [[nodiscard]] constexpr uint16_t getMaxCooks() const noexcept { return _maxCooks; }
            [[nodiscard]] constexpr float getCookingTime() const noexcept { return _cookingTime; }
            [[nodiscard]] constexpr uint32_t getReloadTime() const noexcept { return _reloadTime; }
            [[nodiscard]] std::shared_ptr<std::atomic<bool>> getIsRunning() const noexcept { return _isRunning; }
            [[nodiscard]] constexpr CountingSemaphore &getNbCooks() noexcept { return _nbCooks; }
            [[nodiscard]] constexpr std::queue<Pizza> &getWaitingPizzas() noexcept { return _waitingPizzas; }
            [[nodiscard]] constexpr CountingSemaphore &getAsWaitingPizzas() noexcept { return _asWaitingPizzas; }
            [[nodiscard]] constexpr std::vector<std::shared_ptr<BalancingSemaphore>> &getIngredients() noexcept { return _ingredients; }

            friend std::ostream &operator<<(std::ostream &os, const Kitchen &kitchen)
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
    };
}

#endif /* !PLAZZA_KITCHEN_KITCHEN_HPP_ */
