/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** exit_status
*/

#ifndef SUBPROCESS_EXIT_STATUS_HPP_
    #define SUBPROCESS_EXIT_STATUS_HPP_

    #include <optional>
    #include <sys/wait.h>
namespace subprocess {
    class status {
        int _wait_result;

        public:
            constexpr status(int wait_result) noexcept : _wait_result(wait_result) {};

            constexpr bool was_continued() const noexcept
            {
                return WIFCONTINUED(_wait_result);
            }

            constexpr bool is_terminated() const noexcept
            {
                return was_signaled().has_value() || has_exited().has_value();
            }

            constexpr std::optional<int> was_stopped() const noexcept
            {
                if (WIFSTOPPED(_wait_result))
                    return WSTOPSIG(_wait_result);
                return std::nullopt;
            }

            constexpr std::optional<int> was_signaled() const noexcept
            {
                if (WIFSIGNALED(_wait_result))
                    return WTERMSIG(_wait_result);
                return std::nullopt;
            }

            constexpr std::optional<int> has_exited() const noexcept
            {
                if (WIFEXITED(_wait_result))
                    return WEXITSTATUS(_wait_result);
                return std::nullopt;
            }
    };
}

#endif /* !SUBPROCESS_EXIT_STATUS_HPP_ */
