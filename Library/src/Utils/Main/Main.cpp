/*
** EPITECH PROJECT, 2024
** Template
** File description:
** Main
*/

/// \file Main.cpp
/// \author PAG_Y0Z
/// \brief Main entry point for the program
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of the main entry point for the program.
/// The main function is responsible for parsing command-line arguments, creating
/// the Params singleton instance, and calling the program_main function. The
/// main function catches any exceptions thrown by the program and prints an
/// error message to the standard error stream.
///
/// \details The main function uses the Params singleton class to parse command-line
/// arguments and store them for later use. The main function then calls the
/// program_main function, which is defined in the Library.hpp file. The main
/// function catches any exceptions thrown by the program and prints an error
/// message to the standard error stream. The main function returns the return
/// value of the program_main function or 84 if an unexpected error occurs.
///
/// \par Example:
/// \code
///
/// #include "Library.hpp"
/// #include <iostream>
///
/// int main(int argc, char **argv)
/// {
///     try
///     {
///         Library::Utils::Params &params = Library::Utils::Params::GetInstance(argc, argv);
///         return program_main();
///     }
///     catch (const Library::Utils::AException &except)
///     {
///         std::cerr << except.what() << std::endl;
///         return except.GetReturnValue();
///     }
///     catch (const std::exception &except)
///     {
///         std::cerr << except.what() << std::endl;
///         return 84;
///     }
///     catch (...)
///     {
///         std::cerr << "An unexpected error occurred" << std::endl;
///         return 84;
///     }
///     return 0;
/// }
/// \endcode
///
/// \see Library.hpp
/// \see Utils/Params/Params.hpp
/// \see Utils/AException/AException.hpp
/// \see program_main

#include "Library.hpp"

#include <iostream>

/// \brief Main entry point for the program
///
/// This function is the main entry point for the program. The main function is
/// responsible for parsing command-line arguments, creating the Params singleton
/// instance, and calling the program_main function. The main function catches
/// any exceptions thrown by the program and prints an error message to the
/// standard error stream.
///
/// \details The main function uses the Params singleton class to parse command-line
/// arguments and store them for later use. The main function then calls the
/// program_main function, which is defined in the Library.hpp file. The main
/// function catches any exceptions thrown by the program and prints an error
/// message to the standard error stream. The main function returns the return
/// value of the program_main function or 84 if an unexpected error occurs.
///
/// \param argc The number of command-line arguments
/// \param argv The command-line arguments
///
/// \return The return value of the program_main function or 84 if an unexpected
/// error occurs
///
/// \remark Catching all exceptions and printing an error message to the standard
/// error stream is a good practice to ensure that the program does not crash
/// unexpectedly. This allows the program to gracefully handle errors and provide
/// useful information to the user.
int main(int argc, char **argv)
{
    try
    {
        Library::Utils::Params &params = Library::Utils::Params::GetInstance(argc, argv);
        return program_main();
    }
    catch (const Library::Utils::AException &except)
    {
        std::cerr << except.what() << std::endl;
        return except.GetReturnValue();
    }
    catch (const std::exception &except)
    {
        std::cerr << except.what() << std::endl;
        return 84;
    }
    catch (...)
    {
        std::cerr << "An unexpected error occurred" << std::endl;
        return 84;
    }
    return 0;
}
