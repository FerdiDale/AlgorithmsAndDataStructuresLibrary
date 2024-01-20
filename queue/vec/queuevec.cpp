
#include <cmath>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
QueueVec<Data>::QueueVec(const LinearContainer<Data>& container) {

  size = container.Size()+1;
  Elements = new Data[size]{};
  for (ulong i = 0; i < size-1; i++){
    Elements[i] = container[i];
  }
  tail = size-1;

}

// Move constructor
template <typename Data>
QueueVec<Data>::QueueVec(QueueVec<Data>&& queue) noexcept : Vector<Data>(std::move(queue)) {

  std::swap(head, queue.head);
  std::swap(tail, queue.tail);

}

/* ************************************************************************** */

//Copy assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& queue) {

  Vector<Data>::operator=(queue);
  head = queue.head;
  tail = queue.tail;
  return *this;

}


//Move assignment
template <typename Data>
QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& queue) noexcept {

  Vector<Data>::operator=(std::move(queue));
  std::swap(head, queue.head);
  std::swap(tail, queue.tail);
  return *this;

}

/* ************************************************************************** */

//Comparison operators

template <typename Data>
bool QueueVec<Data>::operator==(const QueueVec<Data>& queue) const noexcept {

  if (Size() == queue.Size()) {

    ulong j = queue.head;

    for (ulong i = head; i != tail; i = (i+1)%size){

      if (Elements[i] != queue.Elements[j]) return false;

      j = (j+1)%queue.size;

    }

    return true;

  }

  else return false;

}

template <typename Data>
bool QueueVec<Data>::operator!=(const QueueVec<Data>& queue) const noexcept {
  return !(*this==queue);
}

/* ************************************************************************** */

// Specific member functions (inherited from Queue)

template <typename Data>
const Data& QueueVec<Data>::Head() const {

  if (Size() == 0)
    throw std::length_error("Tentato accesso a una coda vuota");
  else
    return (const Data&) Elements[head];

}

template <typename Data>
Data& QueueVec<Data>::Head() {

  if (Size() == 0)
    throw std::length_error("Tentato accesso a una coda vuota");
  else
    return Elements[head];

}

template <typename Data>
void QueueVec<Data>::Dequeue() {

  if (Size() == 0)
    throw std::length_error("Tentata rimozione da una coda vuota");
  else {

    head = (head+1)%size;
    QueueVec<Data>::Reduce();

  }

}

template <typename Data>
Data QueueVec<Data>::HeadNDequeue() {

  if (Size() == 0)
    throw std::length_error("Tentata rimozione da una coda vuota");
  else {

    Data elem = Elements[head];
    head = (head+1)%size;
    QueueVec<Data>::Reduce();

    return elem;

  }

}

template <typename Data>
void QueueVec<Data>::Enqueue(const Data& dato) {

  QueueVec<Data>::Expand();
  Elements[tail] = dato;
  tail = (tail+1)%size;

}

template <typename Data>
void QueueVec<Data>::Enqueue(Data&& dato) {

  QueueVec<Data>::Expand();
  std::swap(Elements[tail], dato);
  tail = (tail+1)%size;

}


/* ************************************************************************** */

// Specific member functions (inherited from Container)


template <typename Data>
bool QueueVec<Data>::Empty() const noexcept{
  return Size()==0;
}

template <typename Data>
ulong QueueVec<Data>::Size() const noexcept{

  ulong diff = abs(head-tail);

  if (tail < head) return (size-diff);
  else return diff;

}

template <typename Data>
void QueueVec<Data>::Clear() {

  while (head!=tail) Dequeue();

}
/* ************************************************************************** */

//Funzioni ausiliarie

template <typename Data>
void QueueVec<Data>::Expand() {

  if (Size() == size-1) {

    Data* newElem = new Data[2*size]{};

    QueueVec<Data>::SwapVectors(newElem);

    size = 2*size;

  }

}

template <typename Data>
void QueueVec<Data>::Reduce() {

  if (Size() <= size/4 && size>1) {

    Data* newElem = new Data[size/2]{};

    QueueVec<Data>::SwapVectors(newElem);

    size = size/2;

  }

}

template <typename Data>
void QueueVec<Data>::SwapVectors(Data* newElem) noexcept {

  ulong j = 0;

  for (ulong i = head; i != tail; i = (i+1)%size){

    std::swap(newElem[j], Elements[i]);

    j++;

  }

  std::swap(Elements, newElem);

  delete[] newElem;

  tail = Size();
  head = 0;

}

/* ************************************************************************** */

}
