/*
** EPITECH PROJECT, 2024
** Template
** File description:
** NumericalParsers
*/

/// \file NumericalParsers.cpp
/// \author PAG_Y0Z
/// \brief NumericalParsers implementation
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of the NumericalParsers functions.
/// The NumericalParsers functions are used to parse numerical values from
/// strings. The NumericalParsers functions are used to parse integers, floats,
/// and booleans from strings.
///
/// \details The NumericalParsers functions are used to parse numerical values
/// from strings. The NumericalParsers functions are used to parse integers,
/// floats, and booleans from strings. The NumericalParsers uses the standard
/// library functions std::stoi, std::stol, std::stoul, std::stoll, std::stoull,
/// std::stof, std::stod, std::stold to parse numerical values from strings.
///
/// \par Example:
/// \code
///
/// #include "Library.hpp"
///
/// int main()
/// {
///     int value;
///
///     if (Library::Utils::NumericalParsers::ParseInt("42", value))
///         std::cout << "Parsed value: " << value << std::endl;
///     else
///         std::cerr << "Failed to parse value" << std::endl;
///
///     return 0;
/// }
///
/// \endcode
///
/// \see NumericalParsers.hpp
///
/// ## Quotes
///
/// > So you are telling me that I can parse a string to an integer ?
/// > And you are telling me that I can parse a string to a float ?
/// > And you are telling me that I can parse a string to a double ?
/// > And you are telling me that I can parse a string to a long double ?
/// > And you are telling me that I can parse a string to a boolean ?
/// > ...
/// >
/// > I don't believe you ! You are a liar ! AND IT WORKS ?!?!?!
/// *- PAGY0Z*

#include "NumericalParsers.hpp"

namespace Library
{
    namespace Utils
    {
        namespace NumericalParsers
        {
            bool IsIntegerNumber(const std::string &string) noexcept
            {
                try
                {
                    size_t i    = 0;
                    size_t len  = string.length();
                    size_t save = i;

                    while (i < len && (string[i] == ' ' || string[i] == '\t'))
                        i++;
                    while (i < len && (string[i] == '+' || string[i] == '-'))
                        i++;
                    save = i;
                    while (i < len && '0' <= string[i] && string[i] <= '9')
                        i++;
                    if (i == save)
                        return false;
                    while (i < len && (string[i] == ' ' || string[i] == '\t'))
                        i++;
                    return i == len;
                }
                catch (const std::exception &except)
                {
                    return false;
                }
            }

            bool ParseInt(const std::string &string, int &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = std::stoi(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseLong(const std::string &string, long &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = std::stol(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseUnsignedLong(const std::string &string, unsigned long &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = std::stoul(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseLongLong(const std::string &string, long long &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = std::stoll(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseUnsignedLongLong(const std::string &string, unsigned long long &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = std::stoull(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseShort(const std::string &string, short &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = static_cast<short>(std::stoi(string));
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseUnsignedShort(const std::string &string, unsigned short &value) noexcept
            {
                try
                {
                    if (!IsIntegerNumber(string))
                        return false;
                    value = static_cast<unsigned short>(std::stoul(string));
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseFloat(const std::string &string, float &value) noexcept
            {
                try
                {
                    value = std::stof(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseDouble(const std::string &string, double &value) noexcept
            {
                try
                {
                    value = std::stod(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseLongDouble(const std::string &string, long double &value) noexcept
            {
                try
                {
                    value = std::stold(string);
                }
                catch (const std::exception &except)
                {
                    return false;
                }
                return true;
            }

            bool ParseBool(const std::string &string, bool &value) noexcept
            {
                if (string == "true" || string == "1")
                {
                    value = true;
                    return true;
                }
                else if (string == "false" || string == "0")
                {
                    value = false;
                    return true;
                }
                return false;
            }

        }    // namespace NumericalParsers
    }        // namespace Utils
}    // namespace Library
