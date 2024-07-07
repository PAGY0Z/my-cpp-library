/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** program_main
*/

#include "Library.hpp"
#include <iostream>

int program_main()
{
    int value = 0;
    std::cout << "Hello, World!" << std::endl;
    if (Library::Utils::Params::GetInstance().GetArgc() <= 1)
    {
        std::cerr << "Usage: ./Template <value>" << std::endl;
        return 84;
    }
    if (!Library::Utils::NumericalParsers::ParseInt(Library::Utils::Params::GetInstance().GetArgv()[1], value))
    {
        std::cerr << "Invalid value" << std::endl;
        return 84;
    }
    std::cout << "Value: " << value << std::endl;
    return 0;
}
