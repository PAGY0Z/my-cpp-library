/*
** EPITECH PROJECT, 2024
** Raytracer
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
/// #include "Factory.hpp"
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

#ifndef FACTORY_HPP_
#define FACTORY_HPP_

#include <map>
#include <functional>
#include <memory>
#include <mutex>

#include "AException.hpp"
#include "Singleton.hpp"

namespace Library
{
    namespace DesignPatterns
    {
        namespace Exceptions
        {
            /// \brief FactoryExceptionsType Enumeration
            ///
            /// The FactoryExceptionsType enumeration defines the types of exceptions
            /// that can be thrown by the Factory class template. The enumeration
            /// includes the following types of exceptions:
            ///
            /// - ALREADY_REGISTERED: The key is already registered
            /// - UNKNOWN_KEY_AT_CREATE: The key is unknown at create
            typedef enum FactoryExceptionsType_e
            {
                ALREADY_REGISTERED,
                UNKNOWN_KEY_AT_CREATE,
            } FactoryExceptionsType_e;

            /// \brief FactoryExceptionsMessage Structure
            ///
            /// The FactoryExceptionsMessage structure defines the message associated
            /// with each type of exception that can be thrown by the Factory class
            /// template. The structure includes the following members:
            ///
            /// - __type: The type of exception
            /// - __message: The message associated with the exception
            typedef struct FactoryExceptionsMessage_s
            {
                FactoryExceptionsType_e __type;
                const std::string &__message;
            } FactoryExceptionsMessage_t;

            /// \brief FactoryExceptions Error Messages
            static const FactoryExceptionsMessage_t FACTORY_EXCEPTIONS_ERROR_MESSAGES[] = {
                {FactoryExceptionsType_e::ALREADY_REGISTERED, "The key is already registered"},
                {FactoryExceptionsType_e::UNKNOWN_KEY_AT_CREATE, "The key is unknown at create"}};

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
            /// by the key. The creator function may be a lambda function or a function
            /// pointer that takes a FactoryParams object as a parameter and returns a
            /// shared pointer to the object.
            ///
            /// \param key The key used to identify the object type
            /// \param creator The creator function for the object type
            void Register(const TypeKeyValue &key, std::function<std::shared_ptr<TypeFactoryObject>(const FactoryParams &)> &creator)
            {
                std::lock_guard<std::mutex> lock(__mutex);
                if (__creators.find(static_cast<TypeKeyValue>(key)) != __creators.end())
                    throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::ALREADY_REGISTERED, FILE_DATA);
                __creators[static_cast<TypeKeyValue>(key)] = creator;
            }

            /// \brief Create an object of the specified type
            ///
            /// This method creates an object of the specified type using the key-value
            /// pair. If the key is not found in the map of creators, the method returns
            /// a null pointer.
            ///
            /// \param key The key used to identify the object type
            /// \param params The FactoryParams object passed to the creator function
            /// \return A shared pointer to the object
            [[nodiscard]] std::shared_ptr<TypeFactoryObject> Create(const TypeKeyValue &key, const FactoryParams &params = FactoryParams()) const
            {
                std::lock_guard<std::mutex> lock(__mutex);
                if (__creators.find(key) == __creators.end())
                    throw Exceptions::FactoryExceptions(Exceptions::FactoryExceptionsType_e::UNKNOWN_KEY_AT_CREATE, FILE_DATA);
                return __creators.at(static_cast<TypeKeyValue>(key))(params);
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
