
namespace lasd {

/* ************************************************************************** */

//Move constructor

template<typename Data>
StackVec<Data>::StackVec(StackVec<Data>&& stack) noexcept : Vector<Data>(std::move(stack)) {

  std::swap(head, stack.head);

}

/* ************************************************************************** */

// Copy assignment
template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(const StackVec& stack) {

  Vector<Data>::operator=(stack);
  head = stack.head;
  return *this;

}

// Move assignment
template<typename Data>
StackVec<Data>& StackVec<Data>::operator=(StackVec&& stack) noexcept {

  Vector<Data>::operator=(std::move(stack));
  std::swap(head, stack.head);
  return *this;

}

/* ************************************************************************** */

//Comparison operators
template<typename Data>
bool StackVec<Data>::operator==(const StackVec& stack) const noexcept {

  if (head == stack.head) {

    for (ulong i = 0; i < head; i++)
      if (Elements[i] != stack.Elements[i]) return false;

    return true;

  }

  else return false;

}

template<typename Data>
bool StackVec<Data>::operator!=(const StackVec& stack) const noexcept {
  return !(*this == stack);
}

/* ************************************************************************** */

// Specific member functions (inherited from Stack)

template<typename Data>
const Data& StackVec<Data>::Top() const {

  if (head == 0) throw std::length_error("Tentato accesso a uno stack vuoto!");
  else return (const Data&) Elements[head-1];

}

template<typename Data>
Data& StackVec<Data>::Top() {

  if (head == 0) throw std::length_error("Tentato accesso a uno stack vuoto!");
  else return Elements[head-1];

}

template<typename Data>
void StackVec<Data>::Pop()  {

  if (head == 0) throw std::length_error("Tentato accesso a uno stack vuoto!");
  else {

    head--;
    Reduce();

  }

}

template<typename Data>
Data StackVec<Data>::TopNPop()  {

  if (head == 0) throw std::length_error("Tentato accesso a uno stack vuoto!");
  else {

    Data elem = Top();
    Pop();

    return elem;

  }

}

template<typename Data>
void StackVec<Data>::Push(const Data& dato) {

  Expand();
  Elements[head++] = dato;

}

template<typename Data>
void StackVec<Data>::Push(Data&& dato) {

  Expand();
  std::swap(Elements[head++], dato);

}

/* ************************************************************************** */

// Specific member functions (inherited from Container)

template<typename Data>
bool StackVec<Data>::Empty() const noexcept {
  return head==0;
}

template<typename Data>
ulong StackVec<Data>::Size() const noexcept {
  return head;
}

template<typename Data>
void StackVec<Data>::Clear(){
  while (head!=0) Pop();
}

/* ************************************************************************** */

// Auxiliary member functions

template<typename Data>
void StackVec<Data>::Reduce() {
  if (head<=size/4 && size>1) Vector<Data>::Resize(size/2);
}

template<typename Data>
void StackVec<Data>::Expand() {
  if (head==size) Vector<Data>::Resize(2*size);
}

/* ************************************************************************** */

}
