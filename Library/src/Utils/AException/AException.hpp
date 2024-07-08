/*
** EPITECH PROJECT, 2024
** Template
** File description:
** AException
*/

/// \file AException.hpp
/// \author PAG_Y0Z
/// \brief AException Class implementation
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of a custom exception class that inherits
/// from the `std::exception` class. The AException class provides a way to
/// create custom exception messages that include additional information such as
/// the file name, line number, and function name where the exception occurred.
///
/// \details The AException class is a custom exception class that inherits from
/// the `std::exception` class. The class provides a way to create custom
/// exception messages that include additional information such as the file name,
/// line number, and function name where the exception occurred. The class
/// provides a constructor that takes a message, additional message, and file
/// data as arguments and constructs an error message that includes all of this
/// information. The class also provides a method to retrieve the return value
/// associated with the exception.
///
/// \par Example:
/// \code
/// #include "AException.hpp"
///
/// void foo()
/// {
///     throw Library::Utils::AException("An error occurred", "Additional information", FILE_DATA);
/// }
///
/// \endcode
///
/// \see std::exception
/// \see std::string
/// \see FILE_DATA

#ifndef AEXCEPTION_HPP_
#define AEXCEPTION_HPP_

#include <exception>
#include <string>

/// \brief Create a string containing the file name, line number, and function name
///
/// This macro creates a string containing the file name, line number, and
/// function name where the exception occurred.
///
/// \return A string containing the file name, line number, and function name
#define FILE_DATA Library::Utils::CreateFileData(__FILE__, __LINE__, __func__)

namespace Library
{
    namespace Utils
    {
        /// \brief Create a string containing the file name, line number, and function name
        ///
        /// This function creates a string containing the file name, line number, and
        /// function name where the exception occurred.
        ///
        /// \param file The name of the file where the exception occurred
        /// \param line The line number where the exception occurred
        /// \param func The name of the function where the exception occurred
        /// \return A string containing the file name, line number, and function name
        [[nodiscard]] inline std::string CreateFileData(const char *file, int line, const char *func) noexcept
        {
            return "In " + std::string(file) + " at line n°" + std::to_string(line) + " in function " + std::string(func) + "()";
        }

        /// \brief AException Class
        ///
        /// The AException class is a custom exception class that inherits from the
        /// `std::exception` class. The class provides a way to create custom
        /// exception messages that include additional information such as the file
        /// name, line number, and function name where the exception occurred. The
        /// class provides a constructor that takes a message, additional message, and
        /// file data as arguments and constructs an error message that includes all
        /// of this information. The class also provides a method to retrieve the
        /// return value associated with the exception.
        class AException : public std::exception
        {
        public:
            /// \brief AException Constructor
            ///
            /// This constructor creates an AException object with the specified
            /// message, additional message, file data, and return value.
            ///
            /// \param message The main message of the exception
            /// \param additional_message Additional information about the exception
            /// \param file_data The file data where the exception occurred
            /// \param return_value The return value associated with the exception
            explicit AException(const std::string &message, const std::string &additional_message = "", const std::string &file_data = "", const int return_value = 84) noexcept : __message(BuildErrorMessage(message, additional_message, file_data)), __returnValue(return_value) {}

            /// \brief AException Destructor
            ///
            /// This destructor is the default destructor for the AException class.
            virtual ~AException() noexcept = default;

            /// \brief Get the exception message
            ///
            /// This method returns the exception message as a C-style string.
            ///
            /// \return The exception message as a C-style string
            [[nodiscard]] virtual const char *what() const noexcept override final { return __message.c_str(); }

            /// \brief Get the return value associated with the exception
            ///
            /// This method returns the return value associated with the exception.
            ///
            /// \return The return value associated with the exception
            [[nodiscard]] int GetReturnValue() const noexcept { return __returnValue; }

        private:
            /// \brief The main message of the exception
            const std::string __message;

            /// \brief The return value associated with the exception
            const int __returnValue;

            /// \brief Build the error message
            ///
            /// This method constructs the error message from the main message,
            /// additional message, and file data.
            ///
            /// \param message The main message of the exception
            /// \param additional_message Additional information about the exception
            /// \param file_data The file data where the exception occurred
            /// \return The full error message
            [[nodiscard]] static std::string BuildErrorMessage(const std::string &message, const std::string &additional_message, const std::string &file_data)
            {
                std::string full_message = message;
                if (!additional_message.empty())
                    full_message += ": " + additional_message;
                if (!file_data.empty())
                    full_message += "\n>>> " + file_data;
                return full_message;
            }
        };
    } // namespace Utils
} // namespace Library

#endif /* !AEXCEPTION_HPP_ */
