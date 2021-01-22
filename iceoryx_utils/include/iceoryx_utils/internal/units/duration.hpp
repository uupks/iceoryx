// Copyright (c) 2019, 2021 by Robert Bosch GmbH, Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef IOX_UTILS_UNITS_DURATION_HPP
#define IOX_UTILS_UNITS_DURATION_HPP

#include "iceoryx_utils/cxx/expected.hpp"
#include "iceoryx_utils/cxx/smart_c.hpp"
#include "iceoryx_utils/platform/time.hpp" // required for QNX

#include <chrono>
#include <cmath>
#include <iostream>
#include <numeric>

namespace iox
{
namespace units
{
enum class TimeSpecReference
{
    None,
    Epoch,
    Monotonic
};

class Duration;

inline namespace duration_literals
{
/// @brief Constructs a new Duration object from nanoseconds
constexpr Duration operator"" _ns(unsigned long long int) noexcept; // PRQA S 48

/// @brief Constructs a new Duration object from microseconds
constexpr Duration operator"" _us(unsigned long long int) noexcept; // PRQA S 48

/// @brief Constructs a new Duration object from milliseconds
constexpr Duration operator"" _ms(unsigned long long int) noexcept; // PRQA S 48

/// @brief Constructs a new Duration object from seconds
constexpr Duration operator"" _s(unsigned long long int) noexcept; // PRQA S 48

/// @brief Constructs a new Duration object from minutes
constexpr Duration operator"" _m(unsigned long long int) noexcept; // PRQA S 48

/// @brief Constructs a new Duration object from hours
constexpr Duration operator"" _h(unsigned long long int) noexcept; // PRQA S 48

/// @brief Constructs a new Duration object from days
constexpr Duration operator"" _d(unsigned long long int) noexcept; // PRQA S 48
} // namespace duration_literals

/// @code
///   #include <iostream>
///   // ...
///   using namespace units;
///   using namespace units::duration_literals;
///   auto someDays = 2 * 7_d + 5_ns;
///   auto someSeconds = 42_s + 500_ms;
///   std::cout << someDays << std::endl;
///   std::cout << someDays.nanoSeconds<uint64_t>() << " ns" << std::endl;
///   std::cout << someSeconds.milliSeconds<int64_t>() << " ms" << std::endl;
/// @endcode
class Duration
{
  public:
    // BEGIN CREATION FROM STATIC FUNCTIONS

    /// @brief Constructs a new Duration object from nanoseconds
    /// @tparam T is an integer type for the value
    /// @param[in] value as nanoseconds
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration nanoseconds(const T value) noexcept;

    /// @brief Constructs a new Duration object from microseconds
    /// @tparam T is an integer type for the value
    /// @param[in] value as microseconds
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration microseconds(const T value) noexcept;

    /// @brief Constructs a new Duration object from milliseconds
    /// @tparam T is an integer type for the value
    /// @param[in] value as milliseconds
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration milliseconds(const T value) noexcept;

    /// @brief Constructs a new Duration object from seconds
    /// @tparam T is an integer type for the value
    /// @param[in] value as seconds
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration seconds(const T value) noexcept;

    /// @brief Constructs a new Duration object from minutes
    /// @tparam T is an integer type for the value
    /// @param[in] value as minutes
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration minutes(const T value) noexcept;

    /// @brief Constructs a new Duration object from hours
    /// @tparam T is an integer type for the value
    /// @param[in] value as hours
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration hours(const T value) noexcept;

    /// @brief Constructs a new Duration object from days
    /// @tparam T is an integer type for the value
    /// @param[in] value as days
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    template <typename T>
    static constexpr Duration days(const T value) noexcept;

    // END CREATION FROM STATIC FUNCTIONS

    // BEGIN CONSTRUCTORS AND ASSIGNMENT

    /// @brief Constructs a Duration from seconds and nanoseconds
    /// @param[in] seconds portion of the duration
    /// @param[in] nanoseconds portion of the duration
    constexpr Duration(const uint64_t seconds, const uint32_t nanoseconds) noexcept;

    /// @brief Construct a Duration object from timeval
    /// @param[in] value as timeval
    constexpr explicit Duration(const struct timeval& value) noexcept;

    /// @brief Construct a Duration object from timespec
    /// @param[in] value as timespec
    constexpr explicit Duration(const struct timespec& value) noexcept;

    /// @brief Construct a Duration object from itimerspec
    /// @param[in] value as itimerspec
    /// @note only it_interval from the itimerspec is used
    constexpr explicit Duration(const struct itimerspec& value) noexcept;

    /// @brief Construct a Duration object from std::chrono::milliseconds
    /// @param[in] value as milliseconds
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    constexpr explicit Duration(const std::chrono::milliseconds& value) noexcept;

    /// @brief Construct a Duration object from std::chrono::nanoseconds
    /// @param[in] value as nanoseconds
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    constexpr explicit Duration(const std::chrono::nanoseconds& value) noexcept;

    /// @brief Assigns a std::chrono::milliseconds to an duration object
    /// @param[in] rhs is the right hand side of the assignment
    /// @return a reference to the Duration object with the assigned millisecond value
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    Duration& operator=(const std::chrono::milliseconds& rhs) noexcept;

    // END CONSTRUCTORS AND ASSIGNMENT

    // BEGIN COMPARISON

    /// @brief Equal to operator
    /// @param[in] rhs is the right hand side of the comparison
    /// @return true if duration equal to rhs
    constexpr bool operator==(const Duration& rhs) const noexcept;

    /// @brief Not equal to operator
    /// @param[in] rhs is the right hand side of the comparison
    /// @return true if duration not equal to rhs
    constexpr bool operator!=(const Duration& rhs) const noexcept;

    /// @brief Less than operator
    /// @param[in] rhs is the right hand side of the comparison
    /// @return true if duration is less than rhs
    constexpr bool operator<(const Duration& rhs) const noexcept;

    /// @brief Less than or equal to operator
    /// @param[in] rhs is the right hand side of the comparison
    /// @return true if duration is less than or equal to rhs
    constexpr bool operator<=(const Duration& rhs) const noexcept;

    /// @brief Greater than operator
    /// @param[in] rhs is the right hand side of the comparison
    /// @return true if duration is greater than rhs
    constexpr bool operator>(const Duration& rhs) const noexcept;

    /// @brief Greater than or equal to operator
    /// @param[in] rhs is the right hand side of the comparison
    /// @return true if duration is greater than or equal to rhs
    constexpr bool operator>=(const Duration& rhs) const noexcept;

    // END COMPARISON

    // BEGIN ARITHMETIC

    /// @brief Creates Duration object by addition
    /// @param[in] rhs is the second summand
    /// @return a new Duration object
    constexpr Duration operator+(const Duration& rhs) const noexcept;

    /// @brief Creates Duration object by subtraction
    /// @param[in] rhs is the subtrahend
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    constexpr Duration operator-(const Duration& rhs) const noexcept;

    /// @brief Creates Duration object by multiplication
    /// @tparam T is an arithmetic type for the multiplicator
    /// @param[in] rhs is the multiplicator
    /// @return a new Duration object
    /// @attention since negative durations are not allowed, the duration will be capped to 0
    /// @note There is no explicit division operator! This can be achieved by multiplication with the inverse of the
    /// divisor.
    template <typename T>
    constexpr Duration operator*(const T& rhs) const noexcept;

    // END ARITHMETIC

    // BEGIN CONVERSION

    /// @brief returns the duration in nanoseconds
    constexpr uint64_t nanoSeconds() const noexcept;

    /// @brief returns the duration in microseconds
    constexpr uint64_t microSeconds() const noexcept;

    /// @brief returns the duration in milliseconds
    constexpr uint64_t milliSeconds() const noexcept;

    /// @brief returns the duration in seconds
    constexpr uint64_t seconds() const noexcept;

    /// @brief returns the duration in minutes
    constexpr uint64_t minutes() const noexcept;

    /// @brief returns the duration in hours
    constexpr uint64_t hours() const noexcept;

    /// @brief returns the duration in days
    constexpr uint64_t days() const noexcept;

    /// @brief converts duration in a timespec c struct
    struct timespec timespec(const TimeSpecReference& reference = TimeSpecReference::None) const noexcept;

    /// @brief converts duration in a timeval c struct
    ///     timeval::tv_sec = seconds since the Epoch (01.01.1970)
    ///     timeval::tv_usec = microseconds
    constexpr operator struct timeval() const noexcept;

    // END CONVERSION

    friend constexpr Duration duration_literals::operator"" _ns(unsigned long long int) noexcept; // PRQA S 48
    friend constexpr Duration duration_literals::operator"" _us(unsigned long long int) noexcept; // PRQA S 48
    friend constexpr Duration duration_literals::operator"" _ms(unsigned long long int) noexcept; // PRQA S 48
    friend constexpr Duration duration_literals::operator"" _s(unsigned long long int) noexcept;  // PRQA S 48
    friend constexpr Duration duration_literals::operator"" _m(unsigned long long int) noexcept;  // PRQA S 48
    friend constexpr Duration duration_literals::operator"" _h(unsigned long long int) noexcept;  // PRQA S 48
    friend constexpr Duration duration_literals::operator"" _d(unsigned long long int) noexcept;  // PRQA S 48

    template <typename T>
    friend constexpr Duration operator*(const T& lhs, const Duration& rhs) noexcept;

    friend std::ostream& operator<<(std::ostream& stream, const Duration& t) noexcept;

  private:
    template <typename T>
    inline constexpr Duration
    multiplySeconds(const uint64_t seconds,
                    const std::enable_if_t<!std::is_floating_point<T>::value, T>& rhs) const noexcept;
    template <typename T>
    inline constexpr Duration
    multiplySeconds(const uint64_t seconds,
                    const std::enable_if_t<std::is_floating_point<T>::value, T>& rhs) const noexcept;
    template <typename T>
    inline constexpr Duration
    multiplyNanoseconds(const uint32_t nanoseconds,
                        const std::enable_if_t<!std::is_floating_point<T>::value, T>& rhs) const noexcept;
    template <typename T>
    inline constexpr Duration
    multiplyNanoseconds(const uint32_t nanoseconds,
                        const std::enable_if_t<std::is_floating_point<T>::value, T>& rhs) const noexcept;

    static constexpr uint32_t SECS_PER_MINUTE{60U};
    static constexpr uint32_t SECS_PER_HOUR{3600U};
    static constexpr uint32_t HOURS_PER_DAY{24U};

    static constexpr uint32_t MILLISECS_PER_SEC{1000U};
    static constexpr uint32_t MICROSECS_PER_SEC{MILLISECS_PER_SEC * 1000U};

    static constexpr uint32_t NANOSECS_PER_MICROSEC{1000U};
    static constexpr uint32_t NANOSECS_PER_MILLISEC{NANOSECS_PER_MICROSEC * 1000U};
    static constexpr uint32_t NANOSECS_PER_SEC{NANOSECS_PER_MILLISEC * 1000U};

    static_assert(NANOSECS_PER_SEC == 1000U * MICROSECS_PER_SEC, "Mismatch in calculation for conversion constants!");

  private:
    uint64_t m_seconds{0U};
    uint32_t m_nanoseconds{0U};
};

/// @brief creates Duration object by multiplying object T with a duration
/// @tparam T is an arithmetic type for the multiplicator
/// @param[in] lhs is the multiplicator
/// @param[in] rhs is the multiplicant
/// @return a new Duration object
/// @attention since negative durations are not allowed, the duration will be capped to 0
template <typename T>
constexpr Duration operator*(const T& lhs, const Duration& rhs) noexcept;

/// @brief stream operator for the Duration class
std::ostream& operator<<(std::ostream& stream, const Duration& t) noexcept;

} // namespace units
} // namespace iox

#include "iceoryx_utils/internal/units/duration.inl"

#endif // IOX_UTILS_UNITS_DURATION_HPP
