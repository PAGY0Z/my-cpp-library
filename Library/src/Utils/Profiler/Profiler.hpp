/*
** EPITECH PROJECT, 2024
** B-CPP-500-RUN-5-1-rtype-romain.nacaouele
** File description:
** Profiler
*/

/// \file Profiler.hpp
/// \author PAG_Y0Z
/// \brief Profiler Class implementation
/// \date 19-09-2024
/// \version 1.0
///
/// This file contains the definition of a Profiler class that provides a way to
/// measure the performance of code by tracking the time taken to execute specific
/// sections of code. The Profiler class uses the high-resolution clock provided
/// by the C++ standard library to measure the time taken to execute code. The
/// Profiler class allows developers to start and stop the timer at specific points
/// in the code and provides methods to dump the results for analysis.
///
/// \details The Profiler class is a useful tool for measuring the performance of
/// code and identifying bottlenecks in the application. By tracking the time taken
/// to execute specific sections of code, developers can identify areas of the code
/// that are slow and optimize them for better performance. The Profiler class is
/// designed to be easy to use and provides a simple interface for starting and
/// stopping the timer and dumping the results. The Profiler class
/// is not thread-safe and should be used with caution in multi-threaded applications.
///
/// \par Example:
/// \code
/// #include "Library.hpp"
///
/// int main()
/// {
///    Profiler::GetInstance().Start("main");
///    for (int i = 0; i < 1000000; i++)
///    {
///        std::cout << i << std::endl;
///    }
///    Profiler::GetInstance().Stop("main");
///    Profiler::GetInstance().Dump();
///    return 0;
/// }
/// \endcode
///
/// \see Profiler.hpp
/// \see Singleton.hpp
/// \see Logger.hpp
///
/// ## Quotes
///
/// > FINALLYYYYYYY ! I now have the final gemstone of code analysis !
/// > The Profiler class is the best, the greatest, the most powerful tool in my arsenal !
/// > I can now measure the performance of my code and optimize it to the max !
/// > I am the king of code optimization !
/// >
/// > Could this be the end of my development journey ?
/// *- PAGY0Z*

#ifndef PROFILER_HPP_
#define PROFILER_HPP_

#include "DesignPatterns/Singleton/Singleton.hpp"
#include "Utils/Logger/Logger.hpp"

#include <unordered_map>

namespace Library
{
    namespace Utils
    {
        /// \brief Profiler Class
        ///
        /// The Profiler class provides a way to measure the performance of code by tracking
        /// the time taken to execute specific sections of code. The Profiler class uses the
        /// high-resolution clock provided by the C++ standard library to measure the time
        /// taken to execute code. The Profiler class allows developers to start and stop the
        /// timer at specific points in the code and provides methods to dump the results for
        /// analysis.
        ///
        /// \details The Profiler class is a useful tool for measuring the performance of code
        /// and identifying bottlenecks in the application. By tracking the time taken to execute
        /// specific sections of code, developers can identify areas of the code that are slow
        /// and optimize them for better performance. The Profiler class is designed
        /// to be easy to use and provides a simple interface for starting and stopping the timer
        /// and dumping the results. The Profiler class is not thread-safe and should be used
        /// with caution in multi-threaded applications.
        ///
        /// \invariant The Profiler class is a Singleton class and can only be instantiated once.
        class Profiler : public Library::DesignPatterns::Singleton<Profiler>
        {
            friend class Library::DesignPatterns::Singleton<Profiler>;

        public:
            /// \brief Profiler Data Structure
            ///
            /// The ProfilerData structure represents the data collected by the Profiler class
            /// for a specific section of code. The structure contains the start time of the
            /// section, the duration of the section, and the number of times the section has
            /// been called.
            struct ProfilerData
            {
                /// \brief The start time of the section
                std::chrono::high_resolution_clock::time_point start;
                /// \brief The duration of the section
                std::chrono::duration<double> duration;
                /// \brief The number of times the section has been called
                std::size_t calls;
            };

        public:
            /// \brief Start the Profiler
            ///
            /// This method starts the Profiler for the given section of code. The method
            /// records the start time of the section and increments the number of calls
            /// to the section.
            ///
            /// \param name The name of the section of code to profile
            void Start(const std::string &name)
            {
                __profiler_data[name].start = std::chrono::high_resolution_clock::now();
                __profiler_data[name].calls++;
            }

            /// \brief Stop the Profiler
            ///
            /// This method stops the Profiler for the given section of code. The method
            /// records the duration of the section by subtracting the start time from
            /// the current time.
            ///
            /// \param name The name of the section of code to profile
            void Stop(const std::string &name)
            {
                if (__profiler_data.find(name) == __profiler_data.end())
                    return;
                __profiler_data[name].duration += std::chrono::high_resolution_clock::now() - __profiler_data[name].start;
            }

            /// \brief Dump the Profiler Data
            ///
            /// This method dumps the Profiler data to the console for analysis. The method
            /// prints the name of each section of code, the total duration of the section,
            /// the number of calls to the section, and the average duration per call.
            void Dump()
            {
                for (const auto &data : __profiler_data)
                {
                    Library::Utils::Logger::GetInstance().WriteInfo(data.first + ": " + std::to_string(data.second.duration.count()) + "s");
                    Library::Utils::Logger::GetInstance().WriteInfo(data.first + ": " + std::to_string(data.second.calls) + " calls");
                    Library::Utils::Logger::GetInstance().WriteInfo(data.first + ": " + std::to_string(data.second.duration.count() / data.second.calls) + "s per call");
                }
            }

        private:
            /// \brief Profiler Constructor
            ///
            /// This constructor creates a new Profiler instance.
            Profiler()
                : Library::DesignPatterns::Singleton<Profiler>() {}

            /// \brief Profile data map that stores the data for each section of code
            std::unordered_map<std::string, ProfilerData> __profiler_data;
        };
    }    // namespace Utils
}    // namespace Library

#endif /* !PROFILER_HPP_ */
