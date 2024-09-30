/*
** EPITECH PROJECT, 2024
** Template
** File description:
** Logger
*/

/// \file Logger.hpp
/// \author PAG_Y0Z
/// \brief Logger Singleton Class [Thread-Safe] implementation
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of a Singleton class that provides a
/// thread-safe way to log messages to the console.
///
/// \details The Logger class is a Singleton class that provides a thread-safe
/// way to log messages to the console. The class uses a mutex to ensure that
/// only one thread can write to the console at a time. The class provides
/// methods to log messages at different levels of severity, such as INFO, WARN,
/// and ERROR. The class is implemented as a Singleton to ensure that only one
/// instance of the class is created and that the logging functionality is
/// thread-safe.
///
/// \par Example:
/// \code
/// #include "Logger.hpp"
///
/// int main()
/// {
///     Library::Utils::Logger &logger = Library::Utils::GetInstance();
///
///     logger.WriteInfo("This is an informational message");
///     logger.WriteWarn("This is a warning message");
///     logger.WriteError("This is an error message");
///
///     return 0;
/// }
/// \endcode
///
/// \see Singleton.hpp
/// \see Logger.hpp
///
/// ## Quotes
///
/// > Logging ? Everywhere ? I don't ever have to manage it again ?
/// > It will be so easy to debug my code now... Debugging ? What is that ?
/// >
/// > Debugging is for the weak ! I am a god of programming ! I use logging to debug !
/// > What am I saying ? I don't need to debug ! My code is perfect !
/// *- PAGY0Z*

#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include "DesignPatterns/Singleton/Singleton.hpp"

#include <array>
#include <iostream>
#include <mutex>
#include <string>

namespace Library
{
    namespace Utils
    {
        /// \brief Color Code Enumeration
        ///
        /// The ColorCode enumeration defines the different color codes that can be
        /// used to format text in the console. The color codes are used to change
        /// the color of the text in the console.
        ///
        /// \note The enumeration values are as follows:
        /// \note - FG_RED: Red foreground color
        /// \note - FG_GREEN: Green foreground color
        /// \note - FG_YELLOW: Yellow foreground color
        /// \note - FG_BLUE: Blue foreground color
        /// \note - FG_DEFAULT: Default foreground color
        /// \note - BG_RED: Red background color
        /// \note - BG_GREEN: Green background color
        /// \note - BG_BLUE: Blue background color
        /// \note - BG_DEFAULT: Default background color
        typedef enum ColorCode_e
        {
            FG_RED     = 31,
            FG_GREEN   = 32,
            FG_YELLOW  = 33,
            FG_BLUE    = 34,
            FG_DEFAULT = 39,
            BG_RED     = 41,
            BG_GREEN   = 42,
            BG_BLUE    = 44,
            BG_DEFAULT = 49
        } ColorCode_t;

        class ColorModifier
        {
        private:
            ColorCode_t code;

        public:
            ColorModifier(ColorCode_t pCode)
                : code(pCode) {}
            friend std::ostream &operator<<(std::ostream &os, const ColorModifier &mod)
            {
                return os << "\033[" << mod.code << "m";
            }
        };

        /// \brief Logger Level Enumeration
        ///
        /// The LoggerLevel enumeration defines the different levels of severity
        /// that can be used to log messages.
        ///
        /// \note The enumeration values are as follows:
        /// \note - INFO: Informational messages
        /// \note - WARN: Warning messages
        /// \note - ERROR: Error messages
        /// \note - ALL: All messages [SHOULD NEVER BE USED BUT SAFE]
        /// \warning The ALL level should never be used in production code.
        enum class LoggerLevel
        {
            /// \note Informational messages [INFO]
            INFO,
            /// \note Warning messages [WARN]
            WARN,
            /// \note Error messages [ERROR]
            ERROR,
            /// \note All messages [SHOULD NEVER BE USED BUT SAFE]
            ALL,
        };

        /// \brief Logger Identifier Structure
        ///
        /// The LoggerIdentifier structure defines the identifier associated with
        /// each level of severity that can be used to log messages.
        ///
        /// \note The structure includes the following members:
        /// \note - __level: The level of severity
        /// \note - __identifier: The identifier associated with the level of severity
        /// \note - __color: The color associated with the level of severity
        struct LoggerIdentifier
        {
            /// \brief The level of severity
            const LoggerLevel __level;
            /// \brief The identifier associated with the level of severity
            const std::string &__identifier;
            /// \brief The color associated with the level of severity
            const ColorModifier &__color;
        };

        /// \brief Default Color Modifier
        ///
        /// The DEFAULT_COLOR constant defines the default color modifier that is
        /// used to reset the color of the text in the console.
        ///
        /// \note The default color modifier is used to reset the color of the text
        /// in the console to the default color.
        static const ColorModifier DEFAULT_COLOR = ColorModifier(FG_DEFAULT);

        /// \brief Logger Identifiers
        static const LoggerIdentifier LOGGER_IDENTIFIERS[] = {
            {LoggerLevel::INFO, "INFO", ColorModifier(FG_GREEN)},
            {LoggerLevel::WARN, "WARN", ColorModifier(FG_YELLOW)},
            {LoggerLevel::ERROR, "ERROR", ColorModifier(FG_RED)},
            {LoggerLevel::ALL, "ALL", DEFAULT_COLOR}};

        /// \brief Logger Singleton Class
        ///
        /// The Logger class is a Singleton class that provides a thread-safe way
        /// to log messages to the console. The class uses a mutex to ensure that
        /// only one thread can write to the console at a time. The class provides
        /// methods to log messages at different levels of severity, such as INFO,
        /// WARN, and ERROR. The class is implemented as a Singleton to ensure that
        /// only one instance of the class is created and that the logging functionality
        /// is thread-safe.
        ///
        /// \invariant The Logger class maintains the invariant that each level of
        /// severity has a separate count of messages.
        ///
        /// \post After writing a message, the count of messages for the specified
        /// level of severity is incremented.
        ///
        /// \remark This implementation uses a thread-safe Singleton pattern to ensure
        /// that only one instance of the Logger class is created.
        class Logger : public Library::DesignPatterns::Singleton<Logger>
        {
            friend class Library::DesignPatterns::Singleton<Logger>;

        public:
            /// \brief Get the Logger instance
            ///
            /// This method returns the Logger instance. If the instance does not
            /// exist, it is created.
            ///
            /// \return The Logger instance
            [[nodiscard]] static Logger &GetInstance() { return Library::DesignPatterns::Singleton<Logger>::GetInstance(); }

            /// \brief Get the count of messages for the specified level of severity
            ///
            /// This method returns the count of messages for the specified level of
            /// severity. If no level is specified, the count of all messages is returned.
            ///
            /// \param level The level of severity
            /// \return The count of messages for the specified level of severity
            [[nodiscard]] inline size_t GetCount(const LoggerLevel level = LoggerLevel::ALL) const noexcept
            {
                std::lock_guard<std::mutex> lock(__mutex);
                return __counts[static_cast<size_t>(level)];
            }

            /// \brief Write an informational message to the console
            ///
            /// This method writes an informational message to the console. The message
            /// is formatted with the level of severity and a message count. The message
            /// is written to the console using a mutex to ensure that only one thread
            /// can write to the console at a time.
            ///
            /// \param message The message to write to the console
            ///
            /// \post The count of messages for the INFO level of severity is incremented.
            void WriteInfo(const std::string &message) { Write(message, LoggerLevel::INFO); }

            /// \brief Write a warning message to the console
            ///
            /// This method writes a warning message to the console. The message is
            /// formatted with the level of severity and a message count. The message
            /// is written to the console using a mutex to ensure that only one thread
            /// can write to the console at a time.
            ///
            /// \param message The message to write to the console
            ///
            /// \post The count of messages for the WARN level of severity is incremented.
            void WriteWarn(const std::string &message) { Write(message, LoggerLevel::WARN); }

            /// \brief Write an error message to the console
            ///
            /// This method writes an error message to the console. The message is
            /// formatted with the level of severity and a message count. The message
            /// is written to the console using a mutex to ensure that only one thread
            /// can write to the console at a time.
            ///
            /// \param message The message to write to the console
            void WriteError(const std::string &message) { Write(message, LoggerLevel::ERROR); }

        private:
            /// \brief Constructor
            ///
            /// The constructor of the Logger class. This constructor is private to
            /// ensure that only one instance of the class is created.
            Logger()
                : Library::DesignPatterns::Singleton<Logger>()
            {
                __counts.fill(0);
                WriteInfo("Logger initialized");
            }

        private:
            /// \brief Write a message to the console
            ///
            /// This method writes a message to the console at the specified level of
            /// severity. The message is formatted with the level of severity and a
            /// message count. The message is written to the console using a mutex to
            /// ensure that only one thread can write to the console at a time.
            ///
            /// \param message The message to write to the console
            /// \param level The level of severity
            ///
            /// \post The count of messages for the specified level of severity is
            /// incremented.
            void Write(const std::string &message, const LoggerLevel level = LoggerLevel::INFO)
            {
                std::lock_guard<std::mutex> lock(__mutex);
                std::cout << LOGGER_IDENTIFIERS[static_cast<size_t>(level)].__color << "[" << LOGGER_IDENTIFIERS[static_cast<size_t>(level)].__identifier << " n°" << __counts[static_cast<size_t>(level)] << "] " << message << DEFAULT_COLOR << std::endl;
                __counts[static_cast<size_t>(level)]++;
                if (level != LoggerLevel::ALL)
                {
                    __counts[static_cast<size_t>(LoggerLevel::ALL)]++;
                }
            }

        private:
            mutable std::mutex                                              __mutex;
            std::array<size_t, (static_cast<size_t>(LoggerLevel::ALL) + 1)> __counts;
        };
    }    // namespace Utils
}    // namespace Library

#endif /* !LOGGER_HPP_ */
