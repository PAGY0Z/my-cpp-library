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
///     for (unsigned int i = 0; i < params.GetArgc(); i++)
///         std::cout << "Argv[" << i << "]: " << params.GetArgv()[i] << std::endl;
///
///     return 0;
/// }
/// \endcode
///
/// \see Singleton.hpp
/// \see Params.hpp
///
/// ## Quotes
///
/// > Parameters ? Everywhere ? I don't ever have to manage them again ?
/// > Why didn't I think of this before ?
/// >
/// > The guy who invented this is a genius !
/// *- Said no one... Ever*

#ifndef PARAMS_HPP_
#define PARAMS_HPP_

#include "DesignPatterns/Singleton/Singleton.hpp"

#include <string>
#include <vector>

static const char *const emptyArgv[] = {NULL};

#define EMPTY_ARGV emptyArgv

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
            static inline Params &GetInstance(const unsigned int argc = 0, const char *const *argv = EMPTY_ARGV) { return Library::DesignPatterns::Singleton<Params>::GetInstance(argc, argv); }

            /// \brief Get the number of command-line arguments
            ///
            /// This method returns the number of command-line arguments passed to
            /// the program.
            ///
            /// \return The number of command-line arguments
            inline unsigned int GetArgc() const { return __ac; }

            /// \brief Get the array of command-line arguments
            ///
            /// This method returns the array of command-line arguments passed to
            /// the program.
            ///
            /// \return The array of command-line arguments
            inline const char *const *GetArgv() const { return __av; }

        private:
            /// \brief Constructor
            ///
            /// The constructor of the Params class. This constructor is private to
            /// ensure that only one instance of the class is created. The constructor
            /// stores the `argc` and `argv` values passed to the `main` function.
            ///
            /// \param argc The number of command-line arguments
            /// \param argv The array of command-line arguments
            Params(const unsigned int argc, const char *const *argv)
                : Library::DesignPatterns::Singleton<Params>(), __ac(argc), __av(argv) {}

            /// \brief The number of command-line arguments
            const unsigned int __ac;

            /// \brief The array of command-line arguments
            const char *const *__av;
        };
    }    // namespace Utils
}    // namespace Library

#endif /* !PARAMS_HPP_ */
