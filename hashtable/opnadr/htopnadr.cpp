
namespace lasd {

/* ************************************************************************** */

template <typename Data>
void ExistsFunctOpn(const Data& dato, const void* parametro, void* accumulatore) {
  if (!((*((HashTableOpnAdr<Data> *) parametro)).Exists(dato)))
    (*(bool*) accumulatore) = false;
}

template <typename Data>
void InsertFunctOpn(const Data& dato, const void* parametro, void* accumulatore) {
  (*((HashTableOpnAdr<Data> *)parametro)).Insert(dato);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size) {

  if (size!=0){
    vec.Resize(std::pow(2,std::ceil(std::log2(size))));
    vecval.Resize(std::pow(2,std::ceil(std::log2(size))));
    this->size = vec.Size();
  }
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const LinearContainer<Data>& lc) {
  if (lc.Size()>=size/2) {
    vec.Resize(std::pow(2, std::ceil(std::log2(lc.Size()))+2));
    vecval.Resize(std::pow(2, std::ceil(std::log2(lc.Size()))+2));
    this->size = vec.Size();
  }
  DictionaryContainer<Data>::Insert(lc);
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const ulong size, const LinearContainer<Data>& lc) {
  if (size!=0){
    if (lc.Size()<size/2) {
      vec.Resize(std::pow(2,std::ceil(std::log2(size))));
      vecval.Resize(std::pow(2,std::ceil(std::log2(size))));
    }
    else {
      ulong temp = std::ceil(std::log2(lc.Size()));
      vec.Resize(std::pow(2, std::ceil(std::log2(lc.Size()))+2));
      vecval.Resize(std::pow(2, std::ceil(std::log2(lc.Size()))+2));
    }
    this->size = vec.Size();
  }
  DictionaryContainer<Data>::Insert(lc);
}

//Copy e Move constructor

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr& htable) : HashTable<Data>(htable) {
  vec = htable.vec;
  vecval = htable.vecval;
}

template <typename Data>
HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr&& htable) noexcept : HashTable<Data>(std::move(htable)){
  std::swap(vec, htable.vec);
  std::swap(vecval, htable.vecval);
}

//Copy e Move assignment

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr& htable) {
  HashTableOpnAdr temp (htable);
  std::swap(*this, temp);
  return *this;
}

template <typename Data>
HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr&& htable) noexcept {
  HashTable<Data>::operator=(std::move(htable));
  std::swap(vec, htable.vec);
  std::swap(vecval, htable.vecval);
  return *this;
}

//Confronti

template <typename Data>
bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr& htable) const noexcept {
  bool acc1 = true;
  bool acc2 = true;
  htable.Fold(&ExistsFunctOpn<Data>, this, &acc1);
  Fold(&ExistsFunctOpn<Data>, &htable, &acc2);
  return acc1&&acc2;
}

template <typename Data>
bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr& htable) const noexcept {
  return !(*this==htable);
}

//Funzioni membro

template <typename Data>
void HashTableOpnAdr<Data>::Resize(const ulong newsize) {
  ulong sizeEffettiva = newsize;
  if (newsize == 0) vec.Resize(std::pow(2,7));
  else {
    if (numElementi >= newsize/2) sizeEffettiva = (std::pow(2, std::ceil(std::log2(numElementi))+2));

    HashTableOpnAdr<Data> newtable (sizeEffettiva);
    Fold(InsertFunctOpn<Data>, &newtable, nullptr);
    std::swap(*this, newtable);
  }
}

template <typename Data>
ulong HashTableOpnAdr<Data>::Size() const noexcept {
  return numElementi;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Empty() const noexcept {
  return numElementi==0;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Exists(const Data& dato) const noexcept {
  return (Find(dato)!=size);
}

template <typename Data>
void HashTableOpnAdr<Data>::Map(MapFunctor funct, void* parametro) {
  for (ulong i = 0; i < size; i++) {
    if (vecval[i]==HashValues::Full) funct(vec[i], parametro);
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  for (ulong i = 0; i < size; i++) {
    if (vecval[i]==HashValues::Full) funct(vec[i], parametro, accumulatore);
  }
}

template <typename Data>
void HashTableOpnAdr<Data>::Clear() {
  vec.Clear();
  vecval.Clear();
  vec.Resize(std::pow(2,7));
  vecval.Resize(std::pow(2,7));
  numElementi = 0;
  size = vec.Size();
}

//Funzioni membro

template <typename Data>
bool HashTableOpnAdr<Data>::Insert(const Data& dato) {
  if (numElementi >= size/2) Resize(size*2);
  bool eliminazione = false;
  ulong temp = FindEmpty(dato, 0, eliminazione);
  if (temp != size) {
    vec[temp] = dato;
    vecval[temp] = HashValues::Full;
    numElementi++;
    return !eliminazione;
  }
  else return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Insert (Data&& dato) {
  if (numElementi >= size/2) Resize(size*2);
  bool eliminazione = false;
  ulong temp = FindEmpty(dato, 0, eliminazione);
  if (temp != size) {
    std::swap(vec[temp], dato);
    vecval[temp] = HashValues::Full;
    numElementi++;
    return !eliminazione;
  }
  else return false;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dato) {
  if (numElementi<size/8) Resize(size/2);
  return Remove(dato, 0);
}
//Funzioni ausiliarie

template <typename Data>
ulong HashTableOpnAdr<Data>::HashKey(const Data& dato, const ulong i) const noexcept {
  return ((HashTable<Data>::HashKey(dato)+((i*i+i)/2))%size);
}

template <typename Data>
ulong HashTableOpnAdr<Data>::Find(const Data& dato) const noexcept {
  ulong i = 0;
  while (vecval[HashKey(dato, i)] != HashValues::Empty && i < size/2) {
    if (vecval[HashKey(dato, i)] == HashValues::Full && vec[HashKey(dato, i)] == dato) return HashKey(dato, i);
    else i++;
  }
  return size;
}

template <typename Data>
ulong HashTableOpnAdr<Data>::FindEmpty(const Data& dato, const ulong indpartenza, bool& eliminazione) {
  ulong i = indpartenza;
  while (vecval[HashKey(dato, i)] == HashValues::Full && i < size/2) {
    if (vec[HashKey(dato, i)]==dato) return size;
    else i++;
  }
  if (i < size/2) {
    ulong ret = i;
    if (vecval[HashKey(dato, i)] == HashValues::Tombstone) eliminazione = Remove(dato, i+1);
    return HashKey(dato, ret);
  }
  else return size;
}

template <typename Data>
bool HashTableOpnAdr<Data>::Remove(const Data& dato, const ulong indpartenza) {
  ulong i = indpartenza;
  while (vecval[HashKey(dato, i)] != HashValues::Empty && i < size/2) {
    if (vecval[HashKey(dato, i)] == HashValues::Full && vec[HashKey(dato, i)] == dato) {
      vecval[HashKey(dato, i)] = HashValues::Tombstone;
      numElementi--;
      return true;
    }
    else i++;
  }
  return false;
}

/* ************************************************************************** */

}
