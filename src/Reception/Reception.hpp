/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#ifndef RECEPTION_HPP
#define RECEPTION_HPP

#include <cstdint>
#include <thread>
#include <list>
#include <optional>

#include "../Shell/Shell.hpp"
#include "../Kitchen/Kitchen.hpp"

class Reception
{
private:
    uint16_t _maxCooks;
    double _cookingTime;
    std::optional<std::chrono::milliseconds> _reloadTime;

    std::thread _shellThread;
    Shell _shell;

    std::list<Kitchen> _kitchens;

    bool _status = true;

public:
    Reception(uint16_t maxCooks, double cookingTime, std::optional<std::chrono::milliseconds> reloadTime);
    ~Reception();

    void run();
};

#endif //RECEPTION_HPP
