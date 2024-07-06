/*
** EPITECH PROJECT, 2024
** Library
** File description:
** NumericalParsers
*/

#include "NumericalParsers.hpp"

bool Library::Utils::ParseInt(const std::string &string, int &value) noexcept
{
    try
    {
        value = std::stoi(string);
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseLong(const std::string &string, long &value) noexcept
{
    try
    {
        value = std::stol(string);
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseUnsignedLong(const std::string &string, unsigned long &value) noexcept
{
    try
    {
        value = std::stoul(string);
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseLongLong(const std::string &string, long long &value) noexcept
{
    try
    {
        value = std::stoll(string);
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseUnsignedLongLong(const std::string &string, unsigned long long &value) noexcept
{
    try
    {
        value = std::stoull(string);
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseShort(const std::string &string, short &value) noexcept
{
    try
    {
        value = static_cast<short>(std::stoi(string));
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseUnsignedShort(const std::string &string, unsigned short &value) noexcept
{
    try
    {
        value = static_cast<unsigned short>(std::stoul(string));
    }
    catch (const std::exception &except)
    {
        return false;
    }
    return true;
}

bool Library::Utils::ParseFloat(const std::string &string, float &value) noexcept
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

bool Library::Utils::ParseDouble(const std::string &string, double &value) noexcept
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

bool Library::Utils::ParseLongDouble(const std::string &string, long double &value) noexcept
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

bool Library::Utils::ParseBool(const std::string &string, bool &value) noexcept
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
