/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Utils
*/

#ifndef UTILS_HPP_
    #define UTILS_HPP_

    #include <istream>
    #include <optional>
    #include <unordered_map>
    #include <utility>
    #include <vector>

    #define nameof(x) #x

namespace utils {
    template<typename T> requires std::is_enum_v<T>
    struct enum_traits {
        static const int xalloc_index;
        typedef T value_type;
        typedef const std::unordered_map<T, std::string_view> to_string_type;
        typedef const std::unordered_map<std::string_view, T> from_string_type;

        static to_string_type to_string;
        static from_string_type from_string;
        static const std::vector<value_type> valid_values;

        static std::ios_base& alpha(std::ios_base &s)
        {
            s.iword(xalloc_index) = !s.iword(xalloc_index);
            return s;
        }

        template<typename U, typename V>
            requires std::convertible_to<std::add_lvalue_reference_t<U>, std::ios_base&>
                && std::convertible_to<std::add_lvalue_reference_t<V>, std::ios_base&>
        static decltype(auto) copy_alpha(U &&s, V &&other)
        {
            s.iword(xalloc_index) = other.iword(xalloc_index);
            return std::forward<U>(s);
        }
    };

    template<typename T> requires std::is_enum_v<T>
    const int enum_traits<T>::xalloc_index = std::ios_base::xalloc();

    template <typename T>
    inline void extract(std::istream &is, T &value, std::istream &target)
    {
        T v{};
        is >> v;
        if (is.fail())
            target.setstate(std::ios_base::failbit);
        else value = v;
    }

    template<typename T>
    constexpr void extract(std::istream &is, T &value) { extract(is, value, is); }

    template<typename T>
    constexpr void extract(std::istream &&is, T &value, std::istream &target) { extract(is, value, target); }

    template <typename T>
    inline std::optional<T> extract(std::istream &is)
    {
        T value{};
        is >> value;
        if (is.fail())
            return std::nullopt;
        return value;
    }

    template <typename T>
    constexpr decltype(auto) extract(std::istream &&is) { return extract<T>(is); }

    template <typename T>
    inline T extract(std::istream &is, T &&defaultValue)
    {
        T value{};
        is >> value;
        if (is.fail())
            return std::forward<T>(defaultValue);
        return value;
    }

    template <typename T>
    constexpr decltype(auto) extract(std::istream &&is, T &&defaultValue) { return extract(is, std::forward<T>(defaultValue)); }
}

#endif /* !UTILS_HPP_ */
