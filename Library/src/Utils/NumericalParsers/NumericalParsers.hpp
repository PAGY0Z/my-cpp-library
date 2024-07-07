/*
** EPITECH PROJECT, 2024
** Library
** File description:
** NumericalParsers
*/

/// \file NumericalParsers.hpp
/// \author PAG_Y0Z
/// \brief NumericalParsers
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of
///
/// \details The
///
/// \par Example:
/// \code
/// #include "Library.hpp"
///
/// int main()
/// {
///     int value;
///
///     if (Library::Utils::ParseInt("42", value))
///         std::cout << "Parsed value: " << value << std::endl;
///     else
///         std::cerr << "Failed to parse value" << std::endl;
///
///     return 0;
/// }
/// \endcode
///
/// \see NumericalParsers.cpp

#ifndef NUMERICALPARSERS_HPP_
#define NUMERICALPARSERS_HPP_

#include <string>

namespace Library
{
    namespace Utils
    {
        namespace NumericalParsers
        {
            /// \brief Check if a string is an integer number
            ///
            /// This function checks if a string is an integer number. If the string
            /// is an integer number, the function returns `true`. Otherwise, the
            /// function returns `false`.
            ///
            /// \param string The string to check
            /// \return `true` if the string is an integer number, `false` otherwise
            [[nodiscard]] bool IsIntegerNumber(const std::string &string) noexcept;

            /// \brief Parse an integer from a string
            ///
            /// This function attempts to parse an integer from a string. If the
            /// parsing is successful, the integer value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseInt(const std::string &string, int &value) noexcept;

            /// \brief Parse a long integer from a string
            ///
            /// This function attempts to parse a long integer from a string. If the
            /// parsing is successful, the long integer value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The long integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseLong(const std::string &string, long &value) noexcept;

            /// \brief Parse an unsigned long integer from a string
            ///
            /// This function attempts to parse an unsigned long integer from a string.
            /// If the parsing is successful, the unsigned long integer value is stored
            /// in the `value` parameter and the function returns `true`. If the parsing
            /// fails, the function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The unsigned long integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseUnsignedLong(const std::string &string, unsigned long &value) noexcept;

            /// \brief Parse a long long integer from a string
            ///
            /// This function attempts to parse a long long integer from a string. If the
            /// parsing is successful, the long long integer value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The long long integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseLongLong(const std::string &string, long long &value) noexcept;

            /// \brief Parse an unsigned long long integer from a string
            ///
            /// This function attempts to parse an unsigned long long integer from a string.
            /// If the parsing is successful, the unsigned long long integer value is stored
            /// in the `value` parameter and the function returns `true`. If the parsing
            /// fails, the function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The unsigned long long integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseUnsignedLongLong(const std::string &string, unsigned long long &value) noexcept;

            /// \brief Parse a short integer from a string
            ///
            /// This function attempts to parse a short integer from a string. If the
            /// parsing is successful, the short integer value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The short integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseShort(const std::string &string, short &value) noexcept;

            /// \brief Parse an unsigned short integer from a string
            ///
            /// This function attempts to parse an unsigned short integer from a string.
            /// If the parsing is successful, the unsigned short integer value is stored
            /// in the `value` parameter and the function returns `true`. If the parsing
            /// fails, the function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The unsigned short integer value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseUnsignedShort(const std::string &string, unsigned short &value) noexcept;

            /// \brief Parse a float from a string
            ///
            /// This function attempts to parse a float from a string. If the
            /// parsing is successful, the float value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The float value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseFloat(const std::string &string, float &value) noexcept;

            /// \brief Parse a double from a string
            ///
            /// This function attempts to parse a double from a string. If the
            /// parsing is successful, the double value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The double value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseDouble(const std::string &string, double &value) noexcept;

            /// \brief Parse a long double from a string
            ///
            /// This function attempts to parse a long double from a string. If the
            /// parsing is successful, the long double value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \param string The string to parse
            /// \param value The long double value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseLongDouble(const std::string &string, long double &value) noexcept;

            /// \brief Parse a boolean from a string
            ///
            /// This function attempts to parse a boolean from a string. If the
            /// parsing is successful, the boolean value is stored in the `value`
            /// parameter and the function returns `true`. If the parsing fails, the
            /// function returns `false`.
            ///
            /// \details The function accepts the following values as `true`:
            /// - `true`
            /// - `1`
            ///
            /// \details The function accepts the following values as `false`:
            /// - `false`
            /// - `0`
            ///
            /// \param string The string to parse
            /// \param value The boolean value
            /// \return `true` if the parsing is successful, `false` otherwise
            [[nodiscard]] bool ParseBool(const std::string &string, bool &value) noexcept;
        } // namespace NumericalParsers
    } // namespace Utils
} // namespace Library

#endif /* !NUMERICALPARSERS_HPP_ */
