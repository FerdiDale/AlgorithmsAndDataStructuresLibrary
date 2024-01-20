
namespace lasd {

/* ************************************************************************** */

template <typename Data>
void ExistsFunctCls(const Data& dato, const void* parametro, void* accumulatore) {
  if (!((*((HashTableClsAdr<Data> *) parametro)).Exists(dato)))
    (*(bool*) accumulatore) = false;
}

template <typename Data>
void InsertFunctCls(const Data& dato, const void* parametro, void* accumulatore) {
  (*((HashTableClsAdr<Data> *)parametro)).Insert(dato);
}

//Costruttori

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong size) {
  if (size!=0){
    vec.Resize(size);
    this->size = vec.Size();
  }
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const LinearContainer<Data>& lc) {
  DictionaryContainer<Data>::Insert(lc);
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const ulong size, const LinearContainer<Data>& lc) {
  if (size!=0){
    vec.Resize(size);
    this->size = vec.Size();
  }
  DictionaryContainer<Data>::Insert(lc);
}

//Copy e Move constructor

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr& htable) : HashTable<Data>(htable) {
  vec = htable.vec;
}

template <typename Data>
HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr&& htable) noexcept : HashTable<Data>(std::move(htable)){
  std::swap(vec, htable.vec);
}

//Copy e Move assignment

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr& htable) {
  HashTableClsAdr temp (htable);
  std::swap(*this, temp);
  return *this;
}

template <typename Data>
HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr&& htable) noexcept {
  HashTable<Data>::operator=(std::move(htable));
  std::swap(vec, htable.vec);
  return *this;
}

//Confronti

template <typename Data>
bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr& htable) const noexcept {
  bool acc1 = true;
  bool acc2 = true;
  htable.Fold(&ExistsFunctCls<Data>, this, &acc1);
  Fold(&ExistsFunctCls<Data>, &htable, &acc2);
  return acc1&&acc2;
}

template <typename Data>
bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr& htable) const noexcept {
  return !(*this==htable);
}

//Funzioni membro

template <typename Data>
void HashTableClsAdr<Data>::Resize(const ulong newsize) {
  if (newsize == 0) vec.Resize(std::pow(2,7));
  HashTableClsAdr<Data> newtable (newsize);
  Fold(InsertFunctCls<Data>, &newtable, nullptr);
  std::swap(*this, newtable);
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(const Data& dato) {
  if (vec[HashTable<Data>::HashKey(dato)].Insert(dato)){
    numElementi++;
    return true;
  }
  else return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Insert(Data&& dato) {
  if (vec[HashTable<Data>::HashKey(dato)].Insert(std::move(dato))){
    numElementi++;
    return true;
  }
  else return false;
}

template <typename Data>
bool HashTableClsAdr<Data>::Remove(const Data& dato) {
  if (vec[HashTable<Data>::HashKey(dato)].Remove(dato)){
    numElementi--;
    return true;
  }
  else return false;
}

template <typename Data>
ulong HashTableClsAdr<Data>::Size() const noexcept {
  return numElementi;
}

template <typename Data>
bool HashTableClsAdr<Data>::Empty() const noexcept {
  return numElementi==0;
}

template <typename Data>
bool HashTableClsAdr<Data>::Exists(const Data& dato) const noexcept {
  return vec[HashTable<Data>::HashKey(dato)].Exists(dato);
}

template <typename Data>
void HashTableClsAdr<Data>::Map(MapFunctor funct, void* parametro) {
  for (ulong i = 0; i < size; i++) {
    vec[i].Map(funct, parametro);
  }
}

template <typename Data>
void HashTableClsAdr<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  for (ulong i = 0; i < size; i++) {
    vec[i].Fold(funct, parametro, accumulatore);
  }
}

template <typename Data>
void HashTableClsAdr<Data>::Clear() {
  vec.Clear();
  vec.Resize(std::pow(2,7));
  numElementi = 0;
  size = vec.Size();
}

/* ************************************************************************** */

}
