#pragma once
/**
 * @brief: Super Sayyan Vector
 *
 * @author: bigillu
 */

#include <algorithm>
#include <functional>
#include <iostream>
#include <random>
#include <vector>

/**
 * @brief Overloaded << operator to print the contents of a std::vector
 *
 * @tparam U type of the vector
 * @param os ostream reference
 * @param v vector to be displayed
 * @return std::ostream&
 */
template <typename U>
std::ostream &operator<<(std::ostream &os, const std::vector<U> &v) {
  os << "[ ";
  for (const auto &itr : v) {
    os << itr << " ";
  }
  os << "] " << std::endl;
  return os;
}

/**
 * @brief Wrapper around std::vector with powerful functionalities
 *
 * @tparam T type of the vector values
 */
template <typename T>
class Vector {
 public:
  /**
   *
   *
   */
  Vector() { std::fill(std::begin(mVector), std::end(mVector), 0); }

  /**
   * @brief Parameterized Constructor of Vector
   *
   * @param size size of the vector
   */
  Vector(std::size_t size) : mSize(size) { mVector.resize(mSize); }

  /**
   * @brief Get the const Vector object
   *
   * @return const std::vector<T>&
   */
  const std::vector<T> &GetVector() const { return mVector; }

  /**
   * @brief Get the non const Vector object
   *
   * @return std::vector<T>&
   */
  std::vector<T> &GetVector() { return mVector; }
  /**
   * @brief
   *
   */
  class Iterator {
   public:
    typedef Iterator self_type;
    typedef T value_type;
    typedef T &reference;
    typedef T *pointer;
    /**
     * @brief Construct a new Iterator object
     *
     * @param ptr
     */
    Iterator(reference ptr) : mPtr(ptr) {}
    /**
     * @brief
     *
     * @return const reference
     */
    const reference operator*() { return *mPtr; }
    /**
     * @brief
     *
     * @return const pointer
     */
    const pointer operator->() { return mPtr; }
    /**
     * @brief prefix operator
     *
     * @return self_type
     */
    self_type operator++() {
      mPtr++;
      return *this;
    }
    /**
     * @brief post-fix operator
     *
     * @return self_type
     */
    self_type operator++(int) {
      self_type i = *this;
      mPtr++;
      return i;
    }
    /**
     * @brief
     *
     * @param rhs
     * @return self_type
     */
    self_type operator=(const self_type &rhs) {
      mPtr = rhs.mPtr;
      return *this;
    }
    /**
     * @brief
     *
     * @param rhs
     * @return true
     * @return false
     */
    bool operator==(const self_type &rhs) { return mPtr == rhs.mPtr; }
    /**
     * @brief
     *
     * @param rhs
     * @return true
     * @return false
     */
    bool operator!=(const self_type &rhs) { return mPtr != rhs.mPtr; }

   private:
    pointer mPtr;
  };

  Iterator Begin() { return Iterator(mVector.begin()); }

  Iterator End() { return Iterator(mVector.end()); }

  /**
   * @brief Wrapper around std::fill
   *
   * @param value Value to be filled with
   */
  inline void Fill(T value) {
    std::fill(std::begin(mVector), std::end(mVector), value);
  }
  /**
   * @brief Wrapper arounf std::fill_n
   *
   * @param count The count till which the value has to be filled
   * @param value value to be filled
   */
  inline void Fill(std::size_t count, T value) {
    std::fill_n(std::begin(mVector), count, value);
  }

  /**
   * @brief Wrapper around std::iota
   *
   * @param startingValue Starting value of the sequence
   *
   */
  inline void FillwithSequentialValues(T startingValue) {
    std::iota(std::begin(mVector), std::end(mVector), startingValue);
  }

  /**
   * @brief Wrapper around std::generate with a random generator
   * std::function provided
   *
   * @param func Random function genrator object, default = RandomGenerator()
   */
  inline void FillwithRandomGeneratedValues(
      std::function<T(void)> func = std::bind(RandomGenerator)) {
    std::generate(std::begin(mVector), std::end(mVector), func);
  }

  /**
   * @brief Wrapper around std::generate with a random generator
   * std::function provided
   *
   * @param count The count till which the value has to be filled
   * @param func Random function genrator object, default = RandomGenerator()
   */
  inline void FillwithRandomGeneratedValues(
      std::size_t count, std::function<T(void)> func = RandomGenerator) {
    std::generate_n(std::begin(mVector), count, func);
  }

  inline void ReplaceValues(T valueOne, T valueTwo) {
    std::replace(std::begin(mVector), std::end(mVector), valueOne, valueTwo);
  }

 private:
  static T RandomGenerator() {
    std::random_device device;
    auto value = device();
    return value;
  }
  std::vector<T> mVector;
  std::size_t mSize;
};