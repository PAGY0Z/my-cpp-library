/*
** EPITECH PROJECT, 2024
** Library
** File description:
** Singleton
*/

/// \file Singleton.hpp
/// \author PAG_Y0Z
/// \brief Singleton Template Class [Thread-Safe] implementation
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of a template-based Singleton class
/// that ensures only one instance of the class is created in a thread-safe
/// manner.
///
/// \details The Singleton class template is designed to provide a global point
/// of access to a single instance of a class. This implementation uses
/// `std::call_once` and `std::unique_ptr` to ensure that the instance is
/// created only once, even in the presence of multiple threads. The class
/// template prevents copying and assignment to ensure that only one instance
/// exists.
///
/// \par Example:
/// \code
/// #include "Singleton.hpp"
///
/// class Params : public Library::DesignPatterns::Singleton<Params>
/// {
///     friend class Library::DesignPatterns::Singleton<Params>;
///
/// public:
///     [[nodiscard]] static Params &GetInstance(const int argc = 0, const char *const *argv = nullptr) { return Library::DesignPatterns::Singleton<Params>::GetInstance(argc, argv); }
///
///     [[nodiscard]] int GetArgc() const { return __argc; }
///     [[nodiscard]] const char *const *GetArgv() const { return __argv; }
///
/// private:
///     Params(const int argc = 0, const char *const *argv = nullptr) : Library::DesignPatterns::Singleton<Params>(), __argc(argc), __argv(argv) {}
///
///     const int __argc;
///     const char *const *__argv;
/// };
/// \endcode
///
/// \see Singleton.hpp
/// \see std::call_once
/// \see std::once_flag
/// \see std::unique_ptr

#ifndef SINGLETON_HPP_
#define SINGLETON_HPP_

#include <memory>
#include <mutex>

namespace Library
{
    namespace DesignPatterns
    {
        /// \brief Singleton Template Class
        ///
        /// This class template is designed to provide a global point of access to a
        /// single instance of a class. The Singleton class template ensures that only
        /// one instance of the class is created in a thread-safe manner.
        ///
        /// \tparam Type The type of the class that will be a Singleton
        template <typename Type>
        class Singleton
        {
        public:
            /// \brief Deleted copy constructor
            Singleton(const Singleton &) = delete;

            /// \brief Deleted copy assignment operator
            Singleton &operator=(const Singleton &) = delete;

            /// \brief Retrieves the single instance of the class, creating it if necessary.
            /// \tparam Args Variadic template parameter pack for constructor arguments.
            /// \param args Arguments to be forwarded to the class constructor.
            /// \return Reference to the single instance of the class.
            template <typename... Args>
            [[nodiscard]] static Type &GetInstance(Args &&...args)
            {
                std::call_once(__initInstanceFlag, &Singleton::InitSingleton<Args...>, std::forward<Args>(args)...);
                return *__instance;
            }

        protected:
            /// \brief Default constructor
            Singleton() = default;

            /// \brief Virtual destructor
            virtual ~Singleton() = default;

        private:
            /// \brief Initializes the Singleton instance.
            /// \tparam Args Variadic template parameter pack for constructor arguments.
            /// \param args Arguments to be forwarded to the class constructor.
            template <typename... Args>
            static void InitSingleton(Args &&...args)
            {
                __instance.reset(new Type(std::forward<Args>(args)...));
            }

            /// \brief Unique pointer to hold the single instance of the class.
            inline static std::unique_ptr<Type> __instance;

            /// \brief Flag to ensure that the instance is initialized only once.
            inline static std::once_flag __initInstanceFlag;
        };
    } // namespace DesignPatterns
} // namespace Library

#endif /* !SINGLETON_HPP_ */
