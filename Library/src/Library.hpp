/*
** EPITECH PROJECT, 2024
** Library
** File description:
** Library
*/

#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#include "DesignPatterns/Factory/Factory.hpp"
#include "DesignPatterns/Singleton/Singleton.hpp"

#include "Utils/AException/AException.hpp"
#include "Utils/Params/Params.hpp"
#include "Utils/NumericalParsers/NumericalParsers.hpp"

/// \brief Program entry point
///
/// This function is the entry point for the program. It is called by the main
/// function in the Main.cpp file. The function is responsible for executing the
/// main logic of the program and returning an exit code.
///
/// \details The program_main function is the main logic of the program. It is
/// responsible for executing the main logic of the program and returning an exit
/// code. The function is called by the main function in the Main.cpp file. The
/// program_main function is the main entry point for the program and is responsible
/// for executing the main logic of the program.
///
/// \warning This function should not be called directly. It is called by the main
/// function in the Main.cpp file.
/// \warning No exceptions should be let through this function. All exceptions
/// should be caught and handled by the program_main function. Any uncaught
/// exceptions will be caught by the main function but it is recommended to catch
/// all exceptions in the program_main function.
///
/// \return The exit code of the program
/// \see Main.cpp
[[nodiscard]] int program_main();

#endif /* !LIBRARY_HPP_ */
