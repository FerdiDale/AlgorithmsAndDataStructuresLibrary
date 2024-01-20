
#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

/* ************************************************************************** */

#include <random>

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Hash {

public:

  ulong operator()(const Data&) const noexcept; // (concrete function should not throw exceptions)

};

/* ************************************************************************** */

template <typename Data>
class HashTable :
virtual public DictionaryContainer<Data>,
virtual public MappableContainer<Data>,
virtual public FoldableContainer<Data> {

private:

  // ...

protected:

  using DictionaryContainer<Data>::size;

  Hash<Data> hash {};

  const ulong primo = 65537;

  ulong a;

  ulong b;

  ulong numElementi = 0;

public:

  HashTable();

  // Destructor
  virtual ~HashTable() = default;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTable&) const noexcept = delete;
  bool operator!=(const HashTable&) const noexcept = delete;

  /* ************************************************************************ */

  // Specific member function

  virtual void Resize(const ulong) = 0; // Resize the hashtable to a given size

protected:

  // Auxiliary member functions

  ulong HashKey(const Data&) const noexcept;

  HashTable(const HashTable&);

  HashTable(HashTable&&) noexcept;

  // Copy assignment
  HashTable& operator=(const HashTable&); // Copy assignment of abstract types should not be possible.

  // Move assignment
  HashTable& operator=(HashTable&&) noexcept; // Move assignment of abstract types should not be possible.

};

/* ************************************************************************** */

}

#include "hashtable.cpp"

#endif
