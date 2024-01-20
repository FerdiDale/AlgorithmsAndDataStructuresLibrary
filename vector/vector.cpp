
namespace lasd {

/* ************************************************************************** */

  // Costruttori specifici

  template <typename Data>
  Vector<Data>::Vector(const ulong lunghezza){
    Elements = new Data[lunghezza]{};
    size = lunghezza;
  }

  template <typename Data>
  Vector<Data>::Vector(const LinearContainer<Data>& containerIniziale){

    size = containerIniziale.Size();
    Elements = new Data[size]{};
    for (ulong i = 0; i < size; i++){
      Elements[i] = containerIniziale[i];
    }

  }


/* ************************************************************************** */

  // Copy constructor

  template <typename Data>
  Vector<Data>::Vector(const Vector& vettore){

    size = vettore.size;
    Elements = new Data[size]{};
    std::copy(vettore.Elements, vettore.Elements + size, Elements);

  }

  // Move constructor

  template <typename Data>
  Vector<Data>::Vector(Vector&& vettore) noexcept {

    std::swap(Elements, vettore.Elements);
    std::swap(size, vettore.size);

  }

/* ************************************************************************** */

  // Distruttore

  template <typename Data>
  Vector<Data>::~Vector(){

    delete[] Elements;

  }

/* ************************************************************************** */

  // Copy assignment

  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(const Vector<Data>& vettore) {

    Vector<Data>* temp = new Vector<Data>(vettore);
    std::swap(*temp, *this);
    delete temp;
    return *this;

  }

  // Move assignment

  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(Vector<Data>&& vettore) noexcept {

    std::swap(Elements, vettore.Elements);
    std::swap(size, vettore.size);
    return *this;

  }

/* ************************************************************************** */

  // Operatori di confronto

  template <typename Data>
  bool Vector<Data>::operator==(const Vector<Data>& vettore) const noexcept {

      if (size==vettore.size) {

          for (ulong i = 0; i < size; i++) {

            if (Elements[i] != vettore.Elements[i]) return false;

          }

          return true;

      }

      else return false;

  }

  template <typename Data>
  bool Vector<Data>::operator!=(const Vector<Data>& vettore) const noexcept{

    return !(*this == vettore);

  }

/* ************************************************************************** */

  // Specific member functions

  template <typename Data>
  void Vector<Data>::Resize (const ulong newsize) {

    if (newsize == 0) Clear();

    else {

      Data* temp = new Data[newsize]{};

      ulong limite = (size < newsize) ? size : newsize;

      for (uint i = 0; i < limite; i++)
        std::swap(temp[i], Elements[i]);

      std::swap (temp, Elements);

      size = newsize;

      delete[] temp;

    }

  }

/* ************************************************************************** */

  // Specific member functions (inherited from Container)

  template <typename Data>
  void Vector<Data>::Clear() {

    delete[] Elements;
    Elements = nullptr;
    size = 0;

  }


/* ************************************************************************** */

  // Specific member functions (inherited from LinearContainer)

  template <typename Data>
  Data& Vector<Data>::operator[](const ulong indice) const {

    if (indice >= size) throw std::out_of_range ("Tentato accesso all'indice " +
    std::to_string(indice) + "; taglia del vettore: " + std::to_string(size));

    else {

      return Elements[indice];

    }

  }

/* ************************************************************************** */

// Specific member functions (inherited from MappableContainer)

  template <typename Data>
  void Vector<Data>::Map(MapFunctor funzioneAux, void* parametro) {

    MapPreOrder(funzioneAux, parametro);

}

/* ************************************************************************** */

// Specific member functions (inherited from PreOrderMappableContainer)

  template <typename Data>
  void Vector<Data>::MapPreOrder(MapFunctor funzioneAux, void* parametro) {

    for (ulong i = 0; i < size; i++)
      funzioneAux(Elements[i], parametro);

}

/* ************************************************************************** */

// Specific member functions (inherited from PostOrderMappableContainer)

  template <typename Data>
  void Vector<Data>::MapPostOrder(MapFunctor funzioneAux, void* parametro) {

    ulong i = size;
    while (i>0){
      i--;
      funzioneAux(Elements[i], parametro);
    }


}

/* ************************************************************************** */

// Specific member functions (inherited from FoldableContainer)

  template <typename Data>
  void Vector<Data>::Fold(FoldFunctor funzioneAux, const void* parametro, void* accumulatore) const {

    FoldPreOrder(funzioneAux, parametro, accumulatore);

  }

/* ************************************************************************** */

// Specific member functions (inherited from PreOrderFoldableContainer)

  template <typename Data>
  void Vector<Data>::FoldPreOrder(FoldFunctor funzioneAux, const void* parametro, void* accumulatore) const {

    for (ulong i = 0; i < size; i++)
      funzioneAux(Elements[i], parametro, accumulatore);

  }

/* ************************************************************************** */

// Specific member functions (inherited from PostOrderFoldableContainer)

  template <typename Data>
  void Vector<Data>::FoldPostOrder(FoldFunctor funzioneAux, const void* parametro, void* accumulatore) const {

    ulong i = size;

    while (i>0){
      i--;
      funzioneAux(Elements[i], parametro, accumulatore);
    }

  }

}
