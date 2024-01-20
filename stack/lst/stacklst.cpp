
namespace lasd {

/* ************************************************************************** */

// Copy assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stack) {
  List<Data>::operator=(stack);
  return *this;
}

// Move assignment
template <typename Data>
StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stack) noexcept {
  List<Data>::operator=(std::move(stack));
  return *this;
}

/* ************************************************************************** */

// Comparison operators
template<typename Data>
bool StackLst<Data>::operator==(const StackLst<Data>& stack) const noexcept {
  return List<Data>::operator==(stack);
}

template<typename Data>
bool StackLst<Data>::operator!=(const StackLst<Data>& stack) const noexcept {
  return !(operator==(stack));
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template<typename Data>
const Data& StackLst<Data>::Top() const {
  if (StackLst::Size()==0)
    throw std::length_error("Tentato accesso a uno stack vuoto.");
  else return (const Data&) List<Data>::Front();
}

template<typename Data>
Data& StackLst<Data>::Top() {
  if (StackLst::Size()==0)
    throw std::length_error("Tentato accesso a uno stack vuoto.");
  else return List<Data>::Front();
}

template<typename Data>
void StackLst<Data>::Pop() {
  if (StackLst::Size()==0)
    throw std::length_error("Tentata rimozione da uno stack vuoto.");
  else List<Data>::RemoveFromFront();
}

template<typename Data>
Data StackLst<Data>::TopNPop() {
  if (StackLst::Size()==0)
    throw std::length_error("Tentata rimozione da uno stack vuoto.");
  else return List<Data>::FrontNRemove();
}

template<typename Data>
void StackLst<Data>::Push(const Data& dato) {
  List<Data>::InsertAtFront(dato);
}

template<typename Data>
void StackLst<Data>::Push(Data&& dato) {
  List<Data>::InsertAtFront(std::move(dato));
}

/* ************************************************************************** */

// Specific member functions (inherited from Container)
template<typename Data>
void StackLst<Data>::Clear() {
  List<Data>::Clear();
}


/* ************************************************************************** */

}
