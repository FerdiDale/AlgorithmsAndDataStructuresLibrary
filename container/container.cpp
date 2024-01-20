
namespace lasd {

/* ************************************************************************** */

// Container


/* ************************************************************************** */

// LinearContainer

template <typename Data>
bool LinearContainer<Data>::operator==(const LinearContainer& otherContainer) const noexcept {

    if (size == otherContainer.size) {

        for (ulong i = 0; i < size; i++){
          if (operator[](i) != otherContainer[i]) return false;
        }

        return true;
    }
    else return false;

}

template <typename Data>
bool LinearContainer<Data>::operator!=(const LinearContainer& otherContainer) const noexcept {

  return !(*this == otherContainer);

}

template <typename Data>
Data& LinearContainer<Data>::Front() const {

  if (size == 0) throw std::length_error("Tentato accesso a un container vuoto.");

  else return operator[](0);

}

template <typename Data>
Data& LinearContainer<Data>::Back() const {

  if (size == 0) throw std::length_error("Tentato accesso a un container vuoto.");

  else return operator[](size-1);

}

/* ************************************************************************** */

template <typename Data>
void DictionaryContainer<Data>::Insert(const LinearContainer<Data>& lc) {
  for (ulong i = 0; i < lc.Size(); i++) {
    Insert(lc[i]);
  }
}

template <typename Data>
void DictionaryContainer<Data>::Insert(LinearContainer<Data>&& lc) {
  for (ulong i = 0; i < lc.Size(); i++) {
    Insert(std::move(lc[i]));
  }
}

template <typename Data>
void DictionaryContainer<Data>::Remove(const LinearContainer<Data>& lc) {
  for (ulong i = 0; i < lc.Size(); i++) {
    Remove(lc[i]);
  }
}

/* ************************************************************************** */

// FoldableContainer

template <typename Data>
void FunControllo (const Data& datoCorrente, const void* datoConfronto, void* esiste) {

  if (datoCorrente==(*(Data*) datoConfronto))
    (*(bool*) esiste) = true;

}

template <typename Data>
bool FoldableContainer<Data>::Exists(const Data& dato) const noexcept {

  bool esiste = false;
  Fold(&FunControllo<Data>, &dato, &esiste);
  return esiste;

}

/* ************************************************************************** */

// PreOrderMappableContainer

template <typename Data>
void PreOrderMappableContainer<Data>::Map(MapFunctor funAusiliaria, void* parametro) {

  MapPreOrder(funAusiliaria, parametro);

}

/* ************************************************************************** */

// PreOrderFoldableContainer

template <typename Data>
void PreOrderFoldableContainer<Data>::Fold(FoldFunctor funAusiliaria, const void* parametro, void* accumulatore) const {

  FoldPreOrder(funAusiliaria, parametro, accumulatore);

}

/* ************************************************************************** */

// PostOrderMappableContainer

template <typename Data>
void PostOrderMappableContainer<Data>::Map(MapFunctor funAusiliaria, void* parametro) {

  MapPostOrder(funAusiliaria, parametro);

}

/* ************************************************************************** */

// PostOrderFoldableContainer

template <typename Data>
void PostOrderFoldableContainer<Data>::Fold(FoldFunctor funAusiliaria, const void* parametro, void* accumulatore) const {

  FoldPostOrder(funAusiliaria, parametro, accumulatore);

}

/* ************************************************************************** */

// InOrderMappableContainer

template <typename Data>
void InOrderMappableContainer<Data>::Map(MapFunctor funAusiliaria, void* parametro) {

  MapInOrder(funAusiliaria, parametro);

}

/* ************************************************************************** */

// PreOrderFoldableContainer

template <typename Data>
void InOrderFoldableContainer<Data>::Fold(FoldFunctor funAusiliaria, const void* parametro, void* accumulatore) const {

  FoldInOrder(funAusiliaria, parametro, accumulatore);

}

/* ************************************************************************** */

// PostOrderMappableContainer

template <typename Data>
void BreadthMappableContainer<Data>::Map(MapFunctor funAusiliaria, void* parametro) {

  MapBreadth(funAusiliaria, parametro);

}

/* ************************************************************************** */

// PostOrderFoldableContainer

template <typename Data>
void BreadthFoldableContainer<Data>::Fold(FoldFunctor funAusiliaria, const void* parametro, void* accumulatore) const {

  FoldBreadth(funAusiliaria, parametro, accumulatore);

}

}
