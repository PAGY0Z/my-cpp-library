/*
** EPITECH PROJECT, 2024
** Library
** File description:
** Params
*/

/// \file Params.hpp
/// \author PAG_Y0Z
/// \brief Params Singleton Class implementation
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of a Singleton class that provides a
/// global point of access to the command-line arguments passed to the program.
///
/// \details The Params class is a Singleton class that provides a global point
/// of access to the command-line arguments passed to the program. The class
/// stores the `argc` and `argv` values passed to the `main` function and
/// provides methods to access these values. The class is implemented as a
/// Singleton to ensure that only one instance of the class is created and that
/// the command-line arguments are stored in a thread-safe manner.
///
/// \par Example:
/// \code
/// #include "Params.hpp"
///
/// int main(int argc, char *argv[])
/// {
///     Params &params = Params::GetInstance(argc, argv);
///
///     std::cout << "argc: " << params.GetArgc() << std::endl;
///     std::cout << "argv: ";
///     for (const auto &param : params.GetParamsVector())
///         std::cout << param << " ";
///     std::cout << std::endl;
///
///     return 0;
/// }
/// \endcode
///
/// \see Singleton.hpp
/// \see std::vector
/// \see std::string

#ifndef PARAMS_HPP_
#define PARAMS_HPP_

#include <vector>
#include <string>

#include "DesignPatterns/Singleton/Singleton.hpp"

namespace Library
{
    namespace Utils
    {
        /// \brief Params Singleton Class
        ///
        /// The Params class is a Singleton class that provides a global point of
        /// access to the command-line arguments passed to the program. The class
        /// stores the `argc` and `argv` values passed to the `main` function and
        /// provides methods to access these values. The class is implemented as a
        /// Singleton to ensure that only one instance of the class is created and
        /// that the command-line arguments are stored in a thread-safe manner.
        class Params : public Library::DesignPatterns::Singleton<Params>
        {
            friend class Library::DesignPatterns::Singleton<Params>;

        public:
            /// \brief Get the Singleton instance of the Params class
            ///
            /// This method returns the Singleton instance of the Params class. If
            /// the instance does not exist, it is created with the provided `argc`
            /// and `argv` values.
            ///
            /// \param argc The number of command-line arguments
            /// \param argv The array of command-line arguments
            /// \return The Singleton instance of the Params class by reference
            [[nodiscard]] static Params &GetInstance(const int argc = 0, const char *const *argv = nullptr) { return Library::DesignPatterns::Singleton<Params>::GetInstance(argc, argv); }

            /// \brief Get the number of command-line arguments
            ///
            /// This method returns the number of command-line arguments passed to
            /// the program.
            ///
            /// \return The number of command-line arguments
            [[nodiscard]] int GetArgc() const { return __argc; }

            /// \brief Get the array of command-line arguments
            ///
            /// This method returns the array of command-line arguments passed to
            /// the program.
            ///
            /// \return The array of command-line arguments
            [[nodiscard]] const char *const *GetArgv() const { return __argv; }

            /// \brief Get the vector of command-line arguments
            ///
            /// This method returns the vector of command-line arguments passed to
            /// the program as strings.
            ///
            /// \return The vector of command-line arguments as strings
            [[nodiscard]] const std::vector<std::string> &GetParamsVector() const { return __paramsVector; }

        private:
            /// \brief Constructor
            ///
            /// The constructor of the Params class. This constructor is private to
            /// ensure that only one instance of the class is created. The constructor
            /// stores the `argc` and `argv` values passed to the `main` function and
            /// populates the `__paramsVector` with the command-line arguments.
            ///
            /// \param argc The number of command-line arguments
            /// \param argv The array of command-line arguments
            Params(const int argc = 0, const char *const *argv = nullptr) : Library::DesignPatterns::Singleton<Params>(), __argc(argc), __argv(argv)
            {
                for (int i = 0; i < argc; i++)
                    __paramsVector.push_back(argv[i]);
            }

            /// \brief The number of command-line arguments
            const int __argc;

            /// \brief The array of command-line arguments
            const char *const *__argv;

            /// \brief The vector of command-line arguments as strings
            std::vector<std::string> __paramsVector;
        };
    } // namespace Utils
} // namespace Library

#endif /* !PARAMS_HPP_ */
