#include <iostream>

template<typename T>
struct MyClass;

// partial specialization for arrays of known bounds
template<typename T, std::size_t SZ>
struct MyClass<T[SZ]> {
  static void print() {
    std::cout << "print() for T[" << SZ << "]\n";
  }
};

// partial specialization for references to arrays of known bounds
template<typename T, std::size_t SZ>
struct MyClass<T(&)[SZ]> {
  static void print() {
    std::cout << "print() for T(&)[" << SZ << "]\n";
  }
};

// paritial specialization for arrays of unknown bounds
template<typename T>
struct MyClass<T[]> {
  static void print() {
    std::cout << "print() for T[]\n";
  }
};

// paritial specialization for arrays of unknown bounds
template<typename T>
struct MyClass<T(&)[]> {
  static void print() {
    std::cout << "print() for T(&)[]\n";
  }
};

template<typename T>
struct MyClass<T*> {
  static void print() {
    std::cout << "print() for T*\n";
  }
};
