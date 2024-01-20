
#include <cmath>

namespace lasd {

/* ************************************************************************** */

template<>
class Hash<int> {
public:
  ulong operator()(const int& dato) const noexcept {
    return dato*dato;
  }
};

template<>
class Hash<double> {
public:
  ulong operator()(const double& dato) const noexcept {
    long intera = floor(dato);
    long frazionaria = (dato-intera) * pow(2,24);
    return frazionaria * intera;
  }
};

template<>
class Hash<std::string> {
public:
  ulong operator()(const std::string& dato) const noexcept {
   ulong hash = 5381;

   for(ulong i = 0; i < dato.length(); i++)
   {
      hash = ((hash << 5) + hash) + (dato[i]);
   }

   return hash;
  }
};

/* ************************************************************************** */

template <typename Data>
HashTable<Data>::HashTable() {
  size = pow(2,7);
  std::default_random_engine gen (std::random_device{}());
  std::uniform_int_distribution<int> dista (1, primo-1);
  std::uniform_int_distribution<int> distb (0, primo-1);

  a = dista(gen);
  b = distb(gen);
}

template <typename Data>
HashTable<Data>::HashTable(const HashTable& htable) {
  a = htable.a;
  b = htable.b;
  size = htable.size;
  numElementi = htable.numElementi;
}

template <typename Data>
HashTable<Data>::HashTable(HashTable&& htable) noexcept {
  std::swap(a, htable.a);
  std::swap(b, htable.b);
  std::swap(size, htable.size);
  std::swap(numElementi, htable.numElementi);
}

template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(const HashTable& htable) {
  HashTable<Data> temp (htable);
  std::swap(*this, temp);
  return *this;
}

template <typename Data>
HashTable<Data>& HashTable<Data>::operator=(HashTable&& htable) noexcept {
  std::swap(a, htable.a);
  std::swap(b, htable.b);
  std::swap(size, htable.size);
  std::swap(numElementi, htable.numElementi);
  return *this;
}

template <typename Data>
ulong HashTable<Data>::HashKey(const Data& dato) const noexcept {
  return (((a*hash(dato)+b)%primo)%size);
}

/* ************************************************************************** */

}
