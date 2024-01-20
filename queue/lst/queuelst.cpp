
namespace lasd {

/* ************************************************************************** */


// Copy assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& queue) {

  List<Data>::operator=(queue);
  return *this;

}

// Move assignment
template <typename Data>
QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& queue) noexcept {

  List<Data>::operator=(std::move(queue));
  return *this;

}

/* ************************************************************************ */

// Comparison operators
template <typename Data>
bool QueueLst<Data>::operator==(const QueueLst<Data>& queue) const noexcept {
  return List<Data>::operator==(queue);
}

template <typename Data>
bool QueueLst<Data>::operator!=(const QueueLst<Data>& queue) const noexcept {
  return List<Data>::operator!=(queue);
}

/* ************************************************************************ */

// Specific member functions (inherited from Queue)

template <typename Data>
const Data& QueueLst<Data>::Head() const {
  if (QueueLst::Size()==0)
    throw std::length_error("Tentato accesso a una coda vuota.");
  else return (const Data&)List<Data>::Front();
}

template <typename Data>
Data& QueueLst<Data>::Head() {
  if (QueueLst::Size()==0)
    throw std::length_error("Tentato accesso a una coda vuota.");
  else return List<Data>::Front();
}

template <typename Data>
void QueueLst<Data>::Dequeue() {
  if (QueueLst::Size()==0)
    throw std::length_error("Tentata rimozione da una coda vuota.");
  else List<Data>::RemoveFromFront();
}

template <typename Data>
Data QueueLst<Data>::HeadNDequeue() {
  if (QueueLst::Size()==0)
    throw std::length_error("Tentata rimozione da una coda vuota.");
  else return List<Data>::FrontNRemove();
}

template <typename Data>
void QueueLst<Data>::Enqueue(const Data& dato) {
  List<Data>::InsertAtBack(dato);
}

template <typename Data>
void QueueLst<Data>::Enqueue(Data&& dato) {
  List<Data>::InsertAtBack(std::move(dato));
}

/* ************************************************************************ */

// Specific member functions (inherited from Container)

template <typename Data>
void QueueLst<Data>::Clear() {
  List<Data>::Clear();
}

/* ************************************************************************** */

}
