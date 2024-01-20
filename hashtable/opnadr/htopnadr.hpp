
#ifndef HTOPNADR_HPP
#define HTOPNADR_HPP

/* ************************************************************************** */

#include "../hashtable.hpp"
#include <cmath>

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class HashTableOpnAdr : virtual public HashTable<Data> {

private:

  // ...

protected:

  enum class HashValues {Empty, Tombstone, Full};

  using HashTable<Data>::size;
  using HashTable<Data>::numElementi;
  Vector<Data> vec = Vector<Data>(pow(2,7));
  Vector<HashValues> vecval = Vector<HashValues>(pow(2,7));

public:

  // Default constructor
  HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Specific constructors
  HashTableOpnAdr(const ulong); // A hash table of a given size
  HashTableOpnAdr(const LinearContainer<Data>&); // A hash table obtained from a LinearContainer
  HashTableOpnAdr(const ulong, const LinearContainer<Data>&); // A hash table of a given size obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  HashTableOpnAdr(const HashTableOpnAdr&);

  // Move constructor
  HashTableOpnAdr(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~HashTableOpnAdr() = default;

  /* ************************************************************************ */

  // Copy assignment
  HashTableOpnAdr& operator=(const HashTableOpnAdr&);

  // Move assignment
  HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const HashTableOpnAdr&) const noexcept;
  bool operator!=(const HashTableOpnAdr&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from HashTable)

  void Resize(const ulong); // Resize the hashtable to a given size

  /* ************************************************************************ */

  // Specific member functions (inherited from DictionaryContainer)

  bool Insert(const Data&) override; // Override DictionaryContainer member (Copy of the value)
  bool Insert(Data&&) override; // Override DictionaryContainer member (Move of the value)
  bool Remove(const Data&) override; // Override DictionaryContainer member

  /* ************************************************************************ */

  ulong Size() const noexcept override;

  bool Empty() const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)

  bool Exists(const Data&) const noexcept; // Override TestableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from MappableContainer)

  using typename MappableContainer<Data>::MapFunctor;

  void Map(MapFunctor, void*); // Override MappableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from FoldableContainer)

  using typename FoldableContainer<Data>::FoldFunctor;

  void Fold(FoldFunctor, const void*, void*) const; // Override FoldableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear(); // Override Container member

public:

  // Auxiliary member functions

  ulong HashKey(const Data&, const ulong) const noexcept;
  ulong Find(const Data&) const noexcept;
  ulong FindEmpty(const Data&, const ulong, bool&);
  bool Remove(const Data&, const ulong);

};

/* ************************************************************************** */

}

#include "htopnadr.cpp"

#endif
