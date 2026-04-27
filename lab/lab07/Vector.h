
#ifndef LAB8_VECTOR_H
#define LAB8_VECTOR_H

#include <memory>
#include <iostream>
#include <cassert>
#include <vector>
#include <cmath>


template <typename T>
struct vector_traits {
  using param_type = const T&;
  using return_type = const T&;
  using scalar_type = const T&;
  static T zero() { return T{}; }
  static T multiply(const T& scalar, const T& element) {
    return scalar * element;
  }
};

template <>
struct vector_traits<int> {
    using param_type  = int;  
    using return_type = int;

    using scalar_type = int;

    static int zero() { return 0; }

    static int multiply(int scalar, int element) {
        return scalar * element;
    }
};
template <>
struct vector_traits<double> {
    using param_type  = double;  
    using return_type = double;

    using scalar_type = double;

    static double zero() { return 0.0; }

    static double multiply(double scalar, double element) {
        return scalar * element;
    }
};

template <>
struct vector_traits<std::string> {
    using param_type  = const std::string&;  
    using return_type = const std::string&;

    using scalar_type = int;

    static std::string zero() { return ""; }

    static std::string multiply(int scalar, const std::string& element) {
      std::string result;
      for (int i = 0; i < scalar; ++i)
          result += element;
      return result;
  }
};

struct InitPolicy {
  template <typename T, size_t N>
  static void init(T (&data)[N]) {
      for (size_t i = 0; i < N; ++i)
          data[i] = vector_traits<T>::zero();
  }
};

struct NoInitPolicy {
  template <typename T, size_t N>
  static void init(T (&data)[N]) {
      // do nothing
  }
};

struct CheckPolicy {
  static void check(size_t index, size_t size) {
      if (index >= size)
          throw std::out_of_range(
              "Index " + std::to_string(index) +
              " out of range [0, " + std::to_string(size) + ")"
          );
  }
};

struct NoCheckPolicy {
  static void check(size_t index, size_t size) {
      // do nothing
  }
};

template <typename InitP, typename CheckP>
struct Policy : public InitP, public CheckP {
    using init_policy  = InitP;
    using check_policy = CheckP;
};

using SafePolicy = Policy<InitPolicy,   CheckPolicy>;  
using FastPolicy = Policy<NoInitPolicy, NoCheckPolicy>;  

using InitFastPolicy = Policy<InitPolicy, NoCheckPolicy>;


template <typename T, size_t N, typename P = SafePolicy>
class Vector {
  T data[N];

  using traits = vector_traits<T>;

 public:
  typedef T value_type;
  typedef std::size_t  size_type;
  typedef T* pointer;
  typedef T& reference;
  typedef const T& const_reference;
  using param_type  = typename traits::param_type;
    using return_type = typename traits::return_type;
    using scalar_type = typename traits::scalar_type;

  Vector() {
    for (size_t i = 0; i < N; ++i)
    P::init(data); 
}
  Vector(const Vector & v) = default;
  Vector &operator=(const Vector & m) = default;

  Vector(const std::initializer_list<T> &list){
	std::copy(list.begin(), list.end(), data);
  }
  size_type size() const {
	return N;
  }

  return_type get(size_type index) const {
    P::check(index, N);
    return data[index];
}

  void set(size_type index, const_reference value) {
    P::check(index, N);
	data[index] = value;
  }

  friend Vector operator*(scalar_type x, const Vector& v) {
    Vector result;
    for (size_t i = 0; i < v.size(); ++i)
        result.set(i, traits::multiply(x, v.get(i)));
    return result;
}

  friend std::ostream &operator<<(std::ostream &out, const Vector & v) {
	for(int i=0; i < v.size(); ++i){
	  out << v.get(i) << " ";
	}
	return out;
  }

  friend std::istream &operator>>(std::istream &in, Vector & v) {
	Vector::value_type value;
	for(int i=0; i < v.size(); ++i){
	  in >> value;
	  if(in)
		v.set(i, value);
	}
	return in;
  }

};

#endif // LAB8_VECTOR_H