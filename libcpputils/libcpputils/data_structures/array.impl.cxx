module;
//#include <iostream>
//#include <algorithm>
//#include <stdexcept> // std::out_of_range() exception
//#include <utility>   // for std::as_const() for making const and exchange()
module data_structures.array;
// import<algorithm>;
import<iostream>;
import<stdexcept>;
import<utility>;

namespace mal {
  template<typename T>
  Array<T>::Array(size_t arraySize)
      : m_elements{arraySize != 0U ? new T[arraySize] : nullptr}
      , m_size{arraySize} {
    std::cout << "Array(size_t ) called \n";
  }
  // copy constructor
  template<typename T>
  Array<T>::Array(const Array<T> &array)
      : Array{array.m_size} {
    //    Use copy Algorithms in preference to a for loop
    std::copy(array.m_elements, array.m_elements + array.m_size, m_elements);
    std::cout << " Array(const Array&) called \n";
  }
  // move constructor
  template<typename T>
  Array<T>::Array(Array<T> &&array) noexcept {
    // std::exchange(obj,new_value) exchanges
    // obj with the rvalue new_value and
    // returns the old obj , that is stored in the lhs obj this
    m_elements = std::exchange(array.m_elements, nullptr);
    std::cout << "\n the first value of m_element is " << *m_elements;
    m_size = std::exchange(array.m_size, 0);
    std::cout << "\n the value of size is " << m_size;
    std::cout << "\n Array(Array&& ) called \n";
  }

  template<typename T>
  auto
  Array<T>::operator[](size_t index) -> T & {
    // We Impliment the non-const overload in terms of the const overload
    // return m_elEMENTS[Index];
    // This return type uses the const and back again idiom
    // First we cast the this pointer to const using ethier
    // static_cast<const Array<T>&>() or std::as_const() utility
    // Then apply our operator[] on the result ,and to prevent
    // Breaking const correctness I cas back to T& which is the return type
    return const_cast<T &>(std::as_const(*this)[index]);
    // return const_cast<T &>(static_cast<const Array<T> &>(*this).operator[]
    // (index));
  }
  template<typename T>
  auto
  Array<T>::operator[](size_t index) const -> const T & {
    if (index >= m_size) {
      std::cout << "\n index is " << index << " and m_size is " << m_size
                << '\n';
      throw std::out_of_range{" Array index out of bound at  " +
                              std::to_string(index)};
    }
    return m_elements[index];
  }

  /*
   *template <typename T>
   *Array<T>& Array<T>::operator=(const Array<T>& rhs)
   *{
   *    if (this != &rhs)
   *    {
   *        if (m_size >= rhs.m_size)
   *        {
   *            for (const auto& copy : rhs)
   *            {
   *                if (size_t index{}; index >= rhs.m_size && index < m_size)
   *                {
   *                    m_elements[index++] = 0;
   *                }
   *                else
   *                {
   *                    m_elements[index++] = copy;
   *                }
   *            }
   *        }
   *        else
   *        {
   *            delete[] m_elements;
   *            m_elements = nullptr;
   *            m_elements = {new T[rhs.m_size]};
   *            {
   *                size_t index{};
   *                for (const auto& copy : rhs)
   *                {
   *                    m_elements[index++] = copy;
   *                }
   *            }
   *        }
   *    }
   *    return *this;
   *}
   */

  // A move assigment constructor and a copy assignment operator in one
  // Using pass by value causes a move or a copy depending on the argument
  // of the operator=() function , it ie. covers const Array<T>&'s and
  // Array<T>&&'s operator=() function
  template<typename T>
  auto
  Array<T>::operator=(const Array<T> &rhsCopy) -> Array<T> & {
    std::cout << "\n operator=(const Array&) called\n";
    if (this != &rhsCopy) {
      auto copy{rhsCopy};
      (*this).swap(copy);
    }
    return *this;
  }

  // Move assignment operator
  template<typename T>
  auto
  Array<T>::operator=(Array &&rhsMove) noexcept -> Array<T> & {
    std::cout << "\n operator=(Array&&) called\n";
    auto &&rhs_moved{std::move(rhsMove)};
    (*this).swap(rhs_moved);
    return *this;
  }

  template<typename T>
  auto
  Array<T>::swap(Array &rhs) noexcept -> void {
    using std::swap;
    swap(m_elements, rhs.m_elements);
    std::cout << "\nArray<T>::swap(Array<T>& rhs) called\n";
    swap(m_size, rhs.m_size);
  }

  template<typename T>
  void
  swap(Array<T> &lhs, Array<T> &rhs) noexcept {
    std::cout << " \n swapp(Array& ,Array &) called \n";
    lhs.swap(rhs);
  }

  template<typename T>
  Array<T>::~Array() {
    delete[] m_elements;
  }
} // namespace mal
