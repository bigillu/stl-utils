/**
 * @file Printer.h
 * @author Bigillu
 * @brief Generic Printer Library
 * @version 0.1
 * @date 2019-06-08
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <experimental/source_location>
#include <iostream>

namespace ab {
/**
 * @brief print() specialization for integral types
 *
 */
template <typename T, typename = typename std::enable_if<
                          std::is_integral<T>::value ||
                          std::is_floating_point<T>::value>::type>
void print(std::ostream& stream, const T value) {
  stream << value << " ";
}

/**
 * @brief print() specialization for non-integral types (ex, std::string)
 * passing a std::string by reference is cheaper than passing by value
 */
template <typename T, typename = typename std::enable_if<
                          not(std::is_integral<T>::value ||
                              std::is_floating_point<T>::value)>::type>
void print(std::ostream& stream, const T& value) {
  stream << value << " ";
}

/**
 * @brief print() specialization for STL containers
 * Both sequential and associative containers are taken into
 * account
 */

template <typename T, typename _ = void>
struct is_container : std::false_type {};

template <typename... Ts>
struct is_container_helper {};

template <typename T>
struct is_container<
    T, std::conditional_t<
           false,
           is_container_helper<typename T::value_type, typename T::size_type,
                               typename T::allocator_type, typename T::iterator,
                               typename T::const_iterator,
                               decltype(std::declval<T>().size()),
                               decltype(std::declval<T>().begin()),
                               decltype(std::declval<T>().end()),
                               decltype(std::declval<T>().cbegin()),
                               decltype(std::declval<T>().cend())>,
           void>> : public std::true_type {};

template <typename T>
auto print(std::ostream& stream, const T& value) ->
    typename std::enable_if<is_container<T>::value>::type {
  for (typename T::const_iterator it = value.begin(); it != value.end(); ++it) {
    stream << *it << " ";
  }
  stream << '\n';
}

/**
 * @brief Called when the parameter pack is empty
 *
 * @tparam Function function object to be called.
 */
template <typename Function>
void printArgs(Function f) {
  // Parameter pack is empty.
}

/**
 * @brief Generic recursive printer function
 *
 * @tparam Function function object to be called
 * @tparam First First argument of the pack
 * @tparam Rest The remaining arguments of the pack
 */
template <typename Function, typename FirstArg, typename... Rest>
void printArgs(Function f, FirstArg first, Rest... rest) {
  f(first);
  printArgs(f, rest...);
}

/**
 * @brief Generic printer function
 *
 * @tparam Args list of arguments
 * @param stream Ostream object reference
 * @param location current location of the file
 * @param args list of args of different types
 */
template <class... Args>
void printer(std::ostream& stream,
             const std::experimental::source_location& location, Args... args) {
  stream << location.file_name() << "::" << location.function_name() << "("
         << location.line() << ") - ";
  printArgs([&](auto arg) { print(stream, arg); }, args...);
  stream << '\n';
}

}  // namespace ab