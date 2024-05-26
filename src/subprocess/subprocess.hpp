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
    #include <mutex>
    #include <optional>
    #include <sys/wait.h>

    #include "exit_status.hpp"

namespace subprocess {
    class subprocess {
        public:
            typedef __gnu_cxx::stdio_filebuf<char> buffer;

            template<typename F, typename ...Args>
                requires std::regular_invocable<F, std::iostream &&, int, Args&&...>
            void start(F &&function, Args&& ...args)
            {
                buffer buf = make_ipc();
                _pid = fork();
                if (_pid < 0)
                    throw std::runtime_error(std::string("fork: ") + strerror(errno));
                else if (_pid != 0)
                    return;
                this->_buf.~buffer();
                std::invoke(function, std::iostream(std::addressof(buf)), buf.fd(), std::forward<Args>(args)...);
                buf.~buffer();
                std::exit(0);
            }

            status wait() const;
            std::optional<status> try_wait() const;

            constexpr std::optional<pid_t> get_pid() const noexcept { return _pid; }

            template<typename F, typename ...Args>
                requires std::regular_invocable<F, std::iostream &, Args&&...>
            constexpr decltype(auto) ipc(F &&function, Args&& ...args)
            {
                std::lock_guard lock(_mutex);
                if (!_pid.has_value())
                    throw std::runtime_error("Subprocess not started");
                return function(_ipc, std::forward<Args>(args)...);
            }
            template<typename F, typename ...Args>
                requires std::regular_invocable<F, std::iostream &, int, Args&&...>
            constexpr decltype(auto) ipc(F &&function, Args&& ...args)
            {
                std::lock_guard lock(_mutex);
                if (!_pid.has_value())
                    throw std::runtime_error("Subprocess not started");
                return function(_ipc, _buf.fd(), std::forward<Args>(args)...);
            }
            template<typename F, typename ...Args>
                requires std::regular_invocable<F, buffer &, Args&&...>
            constexpr decltype(auto) ipc(F &&function, Args&& ...args)
            {
                std::lock_guard lock(_mutex);
                if (!_pid.has_value())
                    throw std::runtime_error("Subprocess not started");
                return function(_buf, std::forward<Args>(args)...);
            }

        private:
            std::mutex _mutex;
            std::optional<pid_t> _pid = std::nullopt;
            std::iostream _ipc = std::iostream(nullptr);
            buffer _buf;
            buffer make_ipc();
    };
}

#endif /* !SUBPROCESS_SUBPROCESS_HPP_ */
