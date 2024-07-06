/*
** EPITECH PROJECT, 2024
** Raytracer
** File description:
** main
*/

#include "Library.hpp"

#include <iostream>

#define UNUSED __attribute__((unused))

std::shared_ptr<int> ReturnOne(UNUSED const Library::DesignPatterns::FactoryParams &params)
{
    return std::make_shared<int>(1);
}

std::shared_ptr<int> ReturnTwo(UNUSED const Library::DesignPatterns::FactoryParams &params)
{
    return std::make_shared<int>(2);
}

int main(int argc, char **argv)
{
    try
    {
        Library::Utils::Params &params = Library::Utils::Params::GetInstance(argc, argv);
        if (params.GetArgc() != 2)
            throw std::invalid_argument("Invalid number of arguments");

        Library::DesignPatterns::Factory<int> &factory = Library::DesignPatterns::Factory<int>::GetInstance();
        std::function<std::shared_ptr<int>(const Library::DesignPatterns::FactoryParams &)> func1 = ReturnOne;
        std::function<std::shared_ptr<int>(const Library::DesignPatterns::FactoryParams &)> func2 = ReturnTwo;
        factory.Register("one", func1);
        factory.Register("two", func2);
        std::shared_ptr<int> result = factory.Create(params.GetArgv()[1]);
        std::cout << *result << std::endl;
    }
    catch (const Library::DesignPatterns::Exceptions::FactoryExceptions &except)
    {
        std::cerr << except.what() << std::endl;
        return except.GetReturnValue();
    } catch (const std::exception &except) {
        std::cerr << except.what() << std::endl;
        return 84;
    } catch (...) {
        std::cerr << "An unexpected error occurred" << std::endl;
        return 84;
    }
    return 0;
}
