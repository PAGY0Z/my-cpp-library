/*
** EPITECH PROJECT, 2024
** B-CPP-500-RUN-5-1-rtype-romain.nacaouele
** File description:
** Clock
*/

/// \file Clock.hpp
/// \author PAG_Y0Z
/// \brief Clock Class definition
/// \date 27-09-2024
/// \version 1.0
///
/// This file contains the definition of a Clock class that provides a way to
/// measure the elapsed time between two points in a program.
///
/// \details The Clock class is a utility class that provides a way to measure
/// the elapsed time between two points in a program. The class uses the
/// std::chrono library to measure the time elapsed between two points in a
/// program. The class provides methods to start, restart, and get the elapsed
/// time in milliseconds.
///
/// \par Example:
/// \code
/// #include "Clock.hpp"
///
/// int main()
/// {
///     Library::Utils::Clock clock;
///
///     clock.Start();
///     // Do something
///     double elapsed_time = clock.GetElapsedTimeInMillisecondsAndRestart();
///     std::cout << "Elapsed time: " << elapsed_time << " milliseconds" << std::endl;
///
///     return 0;
/// }
/// \endcode
///
/// \see Clock.hpp
///
/// ## Quotes
///
/// > I'm late, I'm late, for a very important date !
/// > No time to say "Hello, Goodbye".
/// >
/// > I'm late, I'm late, I'm late !
/// *- Rabbit from Alice in Wonderland*

#ifndef CLOCK_HPP_
#define CLOCK_HPP_

namespace Library
{
    namespace Utils
    {
        /// \brief Clock Class
        ///
        /// The Clock class is a utility class that provides a way to measure the
        /// elapsed time between two points in a program. The class uses the std::chrono
        /// library to measure the time elapsed between two points in a program. The
        /// class provides methods to start, restart, and get the elapsed time in
        /// milliseconds.
        class Clock
        {
        public:
            /// \brief Constructor of the Clock class (default)
            Clock() = default;

            /// \brief Destructor of the Clock class (default)
            ~Clock() = default;

        public:
            /// \brief Start the clock
            ///
            /// This method starts the clock by setting the start time to the current
            /// time.
            ///
            /// \return 0
            double Start()
            {
                __start = std::chrono::high_resolution_clock::now();
                return 0;
            }

            /// \brief Get the elapsed time in milliseconds
            ///
            /// This method gets the elapsed time in milliseconds since the clock was
            /// started.
            ///
            /// \return The elapsed time in milliseconds
            double GetElapsedTimeInMillisecondsAndRestart()
            {
                auto                                      now     = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double, std::milli> elapsed = now - __start;
                __start                                           = now;
                return elapsed.count();
            }

        private:
            /// \brief Start time of the clock
            std::chrono::time_point<std::chrono::high_resolution_clock> __start;
        };
    }    // namespace Utils
}    // namespace Library

#endif /* !CLOCK_HPP_ */
