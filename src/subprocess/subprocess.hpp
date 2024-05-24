/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** subprocess
*/

#ifndef SUBPROCESS_SUBPROCESS_HPP_
    #define SUBPROCESS_SUBPROCESS_HPP_

    #include <cerrno>
    #include <cstring>
    #include <ext/stdio_filebuf.h>
    #include <functional>
    #include <iostream>
    #include <optional>
    #include <sys/wait.h>

    #include "exit_status.hpp"

namespace subprocess {
    class subprocess {
        public:
            template<typename F, typename ...Args>
                requires std::regular_invocable<F, std::iostream&&, Args&&...>
            void start(F &&function, Args&& ...args)
            {
                std::iostream ipc = make_ipc();
                _pid = fork();
                if (_pid < 0)
                    throw std::runtime_error(std::string("fork: ") + strerror(errno));
                else if (_pid != 0)
                    return;
                std::invoke(function, std::move(ipc), std::forward<Args>(args)...);
                exit(0);
            }

            status wait() const;
            std::optional<status> try_wait() const;

            constexpr std::optional<pid_t> get_pid() const noexcept { return _pid; }

            constexpr std::optional<std::iostream>& get_ipc()  noexcept { return _parent_socket; }

        private:
            std::optional<pid_t> _pid = 0;
            std::optional<std::iostream> _parent_socket;
            std::optional<__gnu_cxx::stdio_filebuf<char>> _pbuf, _cbuf;
            std::iostream make_ipc();
    };
}

#endif /* !SUBPROCESS_SUBPROCESS_HPP_ */
