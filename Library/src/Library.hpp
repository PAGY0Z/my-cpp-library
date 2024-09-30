/*
** EPITECH PROJECT, 2024
** Library
** File description:
** Library
*/

/// \file Library.hpp
/// \author PAG_Y0Z
/// \brief Header file for the Library
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the includes for the Library project. The Library project
/// is a template project that can be used as a starting point for new projects.
/// The Library project contains a number of utility classes and functions that
/// can be used to simplify the development of new projects.
///
/// \details The Library project is a template project that can be used as a
/// starting point for new projects. The Library project contains a number of
/// utility classes and functions that can be used to simplify the development
/// of new projects. The Library project is organized into a number of directories,
/// each containing a different set of classes and functions. The Library project
/// is designed to be easy to use and extend, making it an ideal starting point
/// for new projects.
///
/// \par Example:
/// \code
/// #include "Library.hpp"
///
/// int program_main()
/// {
///     // Main program logic goes here
///     return 0;
/// }
///
/// \endcode
///
/// \see Library.hpp
/// \see DesignPatterns/ECS/ECS.hpp
/// \see DesignPatterns/Factory/Factory.hpp
/// \see DesignPatterns/Singleton/Singleton.hpp
/// \see Utils/AException/AException.hpp
/// \see Utils/Clock/Clock.hpp
/// \see Utils/Logger/Logger.hpp
/// \see Utils/NumericalParsers/NumericalParsers.hpp
/// \see Utils/Params/Params.hpp
/// \see Utils/Profiler/Profiler.hpp
///
/// ## Quotes
///
/// > Library : the pinnacle of code reusability !
/// >
/// > #reuse #recycle #reusablecode #cleancode #codequality #codeefficiency #mycpuwillthankme
/// *- PAGY0Z*

#ifndef LIBRARY_HPP_
#define LIBRARY_HPP_

#include "DesignPatterns/ECS/ECS.hpp"
#include "DesignPatterns/Factory/Factory.hpp"
#include "DesignPatterns/Singleton/Singleton.hpp"
#include "Utils/AException/AException.hpp"
#include "Utils/Clock/Clock.hpp"
#include "Utils/Logger/Logger.hpp"
#include "Utils/NumericalParsers/NumericalParsers.hpp"
#include "Utils/Params/Params.hpp"
#include "Utils/Profiler/Profiler.hpp"

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
///
/// \warning No exceptions should be let through this function. All exceptions
/// should be caught and handled by the program_main function. Any uncaught
/// exceptions will be caught by the main function but it is recommended to catch
/// all exceptions in the program_main function.
///
/// \return The exit code of the program
/// \see Main.cpp
[[nodiscard]] int program_main();

#endif /* !LIBRARY_HPP_ */
