/*
** EPITECH PROJECT, 2024
** Template
** File description:
** Factory
*/

/// \file Factory.hpp
/// \author PAG_Y0Z
/// \brief Factory Template Class [Thread-Safe] implementation
/// \date 02-07-2024
/// \version 1.0
///
/// This file contains the definition of a template-based Factory class
/// that ensures only one instance of the class is created in a thread-safe
/// manner.
///
/// \details The Factory class template is designed to provide a global point
/// of access to a single instance of a class. This implementation uses
/// the Singleton class template to ensure that the instance is created only
/// once, even in the presence of multiple threads. The class template prevents
/// copying and assignment to ensure that only one instance exists. The Factory
/// class template provides a way to register and create objects of a specific
/// type using a key-value pair. The key is used to identify the object type,
/// and the value is a function that creates the object.
///
/// \par Example:
/// \code
/// #include "Library.hpp"
/// #include <iostream>
///
/// #define UNUSED __attribute__((unused))
///
/// std::shared_ptr<int> ReturnOne(UNUSED const Library::DesignPatterns::FactoryParams &params)
/// {
///     return std::make_shared<int>(1);
/// }
///
/// std::shared_ptr<int> ReturnTwo(UNUSED const Library::DesignPatterns::FactoryParams &params)
/// {
///     return std::make_shared<int>(2);
/// }
///
/// int main()
/// {
///     try
///     {
///         Library::DesignPatterns::Factory<int> &factory = Library::DesignPatterns::Factory<int>::GetInstance();
///
///         std::function<std::shared_ptr<int>(const Library::DesignPatterns::FactoryParams &)> func1 = ReturnOne;
///         std::function<std::shared_ptr<int>(const Library::DesignPatterns::FactoryParams &)> func2 = ReturnTwo;
///
///         factory.Register("one", func1);
///         factory.Register("two", func2);
///
///         std::shared_ptr<int> one = factory.Create("one");
///         std::cout << "one: " << *one << std::endl;
///         std::shared_ptr<int> two = factory.Create("two");
///         std::cout << "two: " << *two << std::endl;
///         std::shared_ptr<int> three = factory.Create("three");
///         std::cout << "three: " << *three << std::endl;
///     }
///     catch (const Library::DesignPatterns::Exceptions::FactoryExceptions &except)
///     {
///         std::cerr << except.what() << std::endl;
///         return except.GetReturnValue();
///     }
///     return 0;
/// }
/// \endcode
///
/// \see Factory.hpp
/// \see Singleton.hpp
/// \see FactoryParams
///
/// ## Quotes
///
/// > Oh is fun to create a Factory class template that is thread-safe.
/// > Probably the best thing I have done in my development career.
/// > Imagine the field of possibilities that this class template can open.
/// >
/// > Who would have thought ? huh ?
/// *- PAGY0Z*

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <map>
#include <functional>
#include <memory>
#include <mutex>

#include "Utils/AException/AException.hpp"
#include "DesignPatterns/Singleton/Singleton.hpp"

namespace Library
{
    namespace DesignPatterns
    {
        namespace Exceptions
        {
            /// \brief FactoryExceptionsType Enumeration
            ///
            /// The FactoryExceptionsType enumeration defines the types of exceptions
            /// that can be thrown by the Factory class template.
            ///
            /// \note The enumeration values are as follows:
            /// \note - ALREADY_REGISTERED: The key is already registered
            /// \note - UNKNOWN_KEY_AT_CREATE: The key is unknown at create
            /// \note - UNKNOWN_ERROR_AT_REGISTER: An unknown error occurred at register
            /// \note - UNKNOWN_ERROR_AT_CREATE: An unknown error occurred at create
            /// \note - UNKNOWN_KEY_AT_UNREGISTER: The key is unknown at unregister
            /// \note - UNKNOWN_ERROR_AT_UNREGISTER: An unknown error occurred at unregister
            /// \note - UNKNOWN_ERROR_AT_CLEAR: An unknown error occurred at clear
            typedef enum FactoryExceptionsType_e
            {
                /// @brief The key is already registered
                ALREADY_REGISTERED,
                /// @brief The key is unknown at create
                UNKNOWN_KEY_AT_CREATE,
                /// @brief An unknown error occurred at register
                UNKNOWN_ERROR_AT_REGISTER,
                /// @brief An unknown error occurred at create
                UNKNOWN_ERROR_AT_CREATE,
                /// @brief The key is unknown at unregister
                UNKNOWN_KEY_AT_UNREGISTER,
                /// @brief An unknown error occurred at unregister
                UNKNOWN_ERROR_AT_UNREGISTER,
                /// @brief An unknown error occurred at clear
                UNKNOWN_ERROR_AT_CLEAR
            } FactoryExceptionsType_e;

            /// \brief FactoryExceptionsMessage Structure
            ///
            /// The FactoryExceptionsMessage structure defines the message associated
            /// with each type of exception that can be thrown by the Factory class
            /// template.
            ///
            /// \note The structure includes the following members:
            /// \note - __type: The type of exception
            /// \note - __message: The message associated with the exception
            typedef struct FactoryExceptionsMessage_s
            {
                /// @brief The type of exception
                const FactoryExceptionsType_e __type;
                /// @brief The message associated with the exception
                const std::string &__message;
            } FactoryExceptionsMessage_t;

            /// \brief FactoryExceptions Error Messages
            static const FactoryExceptionsMessage_t FACTORY_EXCEPTIONS_ERROR_MESSAGES[] = {
                {FactoryExceptionsType_e::ALREADY_REGISTERED, "The key is already registered"},
                {FactoryExceptionsType_e::UNKNOWN_KEY_AT_CREATE, "The key is unknown at create"},
                {FactoryExceptionsType_e::UNKNOWN_ERROR_AT_REGISTER, "An unknown error occurred at register"},
                {FactoryExceptionsType_e::UNKNOWN_ERROR_AT_CREATE, "An unknown error occurred at create"},
                {FactoryExceptionsType_e::UNKNOWN_KEY_AT_UNREGISTER, "The key is unknown at unregister"},
                {FactoryExceptionsType_e::UNKNOWN_ERROR_AT_UNREGISTER, "An unknown error occurred at unregister"},
                {FactoryExceptionsType_e::UNKNOWN_ERROR_AT_CLEAR, "An unknown error occurred at clear"}};

            /// \brief FactoryExceptions Class
            ///
            /// The FactoryExceptions class is a custom exception class that inherits
            /// from the `AException` class. The class provides a way to create custom
            /// exception messages that include additional information such as the file
            /// name, line number, and function name where the exception occurred. The
            /// class provides a constructor that takes a message, additional message, and
            /// file data as arguments and constructs an error message that includes all
            /// of this information. The class also provides a method to retrieve the
            /// return value associated with the exception.
            class FactoryExceptions : public Library::Utils::AException
            {
            public:
                FactoryExceptions(FactoryExceptionsType_e type, const std::string &file_data) : Library::Utils::AException("FactoryExceptions", FACTORY_EXCEPTIONS_ERROR_MESSAGES[type].__message, file_data) {}
                virtual ~FactoryExceptions() = default;
            };
        } // namespace Exceptions

        class FactoryParams;

        /// \brief Factory Template Class
        ///
        /// The Factory class template is designed to provide a global point of
        /// access to a single instance of a class. This implementation uses
        /// the Singleton class template to ensure that the instance is created only
        /// once, even in the presence of multiple threads. The class template prevents
        /// copying and assignment to ensure that only one instance exists. The Factory
        /// class template provides a way to register and create objects of a specific
        /// type using a key-value pair. The key is used to identify the object type,
        /// and the value is a function that creates the object.
        ///
        /// \invariant The Factory class maintains the invariant that each key is
        /// associated with at most one creator function.
        ///
        /// \post After registration, the Factory class will be able to create objects
        /// of the specified type using the provided key.
        ///
        /// \todo
        /// - Changing the Factory class to use a different way to receive the parameters for the creator functions.
        ///
        /// \remark This implementation uses a thread-safe Singleton pattern to ensure
        /// that only one instance of the Factory class is created.
        ///
        /// \tparam TypeFactoryObject The type of the object that will be created by the Factory
        /// \tparam TypeKeyValue The type of the key used to identify the object type
        template <typename TypeFactoryObject, typename TypeKeyValue = std::string>
        class Factory : public Singleton<Factory<TypeFactoryObject, TypeKeyValue>>
        {
            friend class Singleton<Factory<TypeFactoryObject, TypeKeyValue>>;

        public:
            /// \brief Get the Factory instance
            ///
            /// This method returns the Factory instance. If the instance does not
            /// exist, it is created.
            ///
            /// \return The Factory instance
            [[nodiscard]] static Factory<TypeFactoryObject, TypeKeyValue> &GetInstance() { return Singleton<Factory<TypeFactoryObject, TypeKeyValue>>::GetInstance(); }

            /// \brief Register a creator function for the object type
            ///
            /// This method registers a creator function for the object type identified
            /// by the key. If a creator for the specified key is already registered,
            /// this method throws an ALREADY_REGISTERED exception. The creator function
            /// may be a lambda function or a function pointer that takes a FactoryParams
            /// object as a parameter and returns a shared pointer to the object.
            ///
            /// \param key The key used to uniquely identify the object type. This key
            /// must not already be registered; otherwise, an exception is thrown.
            /// \param creator The creator function for the object type, which takes
            /// a FactoryParams object and returns a shared pointer to the newly created
            /// object.
            /// \throws Exceptions::FactoryExceptions If the key is already registered.
            /// \throws Exceptions::FactoryExceptions If an unknown error occurs during registration.
            /// \throws Library::Utils::AException If a deeper error occurs during registration.
            void Register(const TypeKeyValue &key, std::function<std::shared_ptr<TypeFactoryObject>(const FactoryParams &)> &creator)
            {
                try
                {
                    std::lock_guard<std::mutex> lock(__mutex);
                    if (__creators.find(static_cast<TypeKeyValue>(key)) != __creators.end())
                        throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::ALREADY_REGISTERED, FILE_DATA);
                    __creators[static_cast<TypeKeyValue>(key)] = creator;
                }
                catch (const Exceptions::FactoryExceptions &except)
                {
                    throw;
                }
                catch (const Library::Utils::AException &except)
                {
                    throw;
                }
                catch (...)
                {
                    throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_ERROR_AT_REGISTER, FILE_DATA);
                }
            }

            /// \brief Unregister a creator function for the object type
            ///
            /// This method unregisters the creator function for the object type identified
            /// by the key. If no creator is registered for the specified key, this method
            /// throws an UNKNOWN_KEY_AT_UNREGISTER exception. The key must match one that
            /// has been previously registered with a corresponding creator.
            ///
            /// \param key The key used to uniquely identify the object type. This key
            /// must match one that has been previously registered; otherwise, an exception
            /// is thrown.
            /// \throws Exceptions::FactoryExceptions If the key is unknown at unregister.
            /// \throws Exceptions::FactoryExceptions If an unknown error occurs during unregistration.
            /// \throws Library::Utils::AException If a deeper error occurs during unregistration.
            void Unregister(const TypeKeyValue &key)
            {
                try
                {
                    std::lock_guard<std::mutex> lock(__mutex);
                    if (__creators.find(static_cast<TypeKeyValue>(key)) == __creators.end())
                        throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_KEY_AT_UNREGISTER, FILE_DATA);
                    __creators.erase(static_cast<TypeKeyValue>(key));
                }
                catch (const Exceptions::FactoryExceptions &except)
                {
                    throw;
                }
                catch (const Library::Utils::AException &except)
                {
                    throw;
                }
                catch (...)
                {
                    throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_ERROR_AT_UNREGISTER, FILE_DATA);
                }
            }

            /// \brief Clear all registered creators
            ///
            /// This method clears all registered creators from the Factory. After calling
            /// this method, the Factory will have no registered creators.
            ///
            /// \throws Exceptions::FactoryExceptions If an unknown error occurs during clearing.
            /// \throws Library::Utils::AException If a deeper error occurs during clearing.
            void Clear()
            {
                try
                {
                    std::lock_guard<std::mutex> lock(__mutex);
                    __creators.clear();
                }
                catch (const Exceptions::FactoryExceptions &except)
                {
                    throw;
                }
                catch (const Library::Utils::AException &except)
                {
                    throw;
                }
                catch (...)
                {
                    throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_ERROR_AT_CLEAR, FILE_DATA);
                }
            }

            /// \brief Create an object of the specified type
            ///
            /// This method creates an object of the specified type using the key to locate
            /// the corresponding creator function. If no creator is registered for the key,
            /// this method throws a UNKNOWN_KEY_AT_CREATE exception. The params object can
            /// be used to pass additional parameters to the creator function if necessary.
            ///
            /// \param key The key used to identify the object type. This key should match
            /// one that has been previously registered with a corresponding creator.
            /// \param params An optional FactoryParams object that may be required by
            /// the creator function to create the object.
            /// \return A shared pointer to the newly created object of type TypeFactoryObject.
            /// \throws Exceptions::FactoryExceptions If no creator is registered for the given key.
            /// \throws Exceptions::FactoryExceptions If an unknown error occurs during object creation.
            /// \throws Library::Utils::AException If a deeper error occurs during object creation.
            [[nodiscard]] std::shared_ptr<TypeFactoryObject> Create(const TypeKeyValue &key, const FactoryParams &params = FactoryParams()) const
            {
                try
                {
                    std::lock_guard<std::mutex> lock(__mutex);
                    if (__creators.find(key) == __creators.end())
                        throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_KEY_AT_CREATE, FILE_DATA);
                    return __creators.at(static_cast<TypeKeyValue>(key))(params);
                }
                catch (const Exceptions::FactoryExceptions &except)
                {
                    throw;
                }
                catch (const Library::Utils::AException &except)
                {
                    throw;
                }
                catch (...)
                {
                    throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_ERROR_AT_CREATE, FILE_DATA);
                }
            }

        private:
            /// \brief Constructor
            ///
            /// The constructor of the Factory class. This constructor is private to
            /// ensure that only one instance of the class is created.
            Factory() : Singleton<Factory<TypeFactoryObject, TypeKeyValue>>() {}

            /// \brief Creator map to store the key-value pairs of object types and creator functions
            std::map<const TypeKeyValue, std::function<std::shared_ptr<TypeFactoryObject>(const FactoryParams &)>> __creators;

            /// \brief Mutex to ensure thread safety
            mutable std::mutex __mutex;
        };

        /// \brief FactoryParams Class
        ///
        /// The FactoryParams class is a placeholder class that can be used to pass
        /// parameters to the creator functions of the Factory class. This class is
        /// empty and does not contain any data members. It is used as a Base class
        /// for any derived class that needs to pass parameters to the creator functions.
        class FactoryParams
        {
        public:
            /// \brief Default constructor
            FactoryParams() = default;

            /// \brief Virtual destructor
            virtual ~FactoryParams() = default;
        };
    } // namespace DesignPatterns
} // namespace Library

#endif /* !FACTORY_HPP_ */
