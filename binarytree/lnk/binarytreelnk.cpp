
#include "../../queue/queue.hpp"
#include "../../queue/vec/queuevec.hpp"

namespace lasd {

/* ************************************************************************** */

//NodeLnk

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& dato) {
  element = dato;
}

template <typename Data>
BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() {
  if (HasLeftChild()) delete sx;
  if (HasRightChild()) delete dx;
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(const NodeLnk& nodo) {
  element = nodo.element;
  if (nodo.sx == nullptr) delete sx;
  else {
    if (sx == nullptr) sx = new NodeLnk();
    *sx = *(nodo.sx);
  }
  if (nodo.dx == nullptr) delete dx;
  else {
    if (dx == nullptr) dx = new NodeLnk();
    *dx = *(nodo.dx);
  }
  return *this;
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::operator=(NodeLnk&& nodo) noexcept {
  std::swap(element, nodo.element);
  std::swap(sx, nodo.sx);
  std::swap(dx, nodo.dx);
  return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept {
  return (sx!=nullptr);
}

template <typename Data>
bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept {
  return (dx!=nullptr);
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() {
  if (HasLeftChild())
    return *sx;
  else
    throw std::length_error ("Il nodo non ha figlio sinistro!");
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() {
  if (HasRightChild())
    return *dx;
  else
    throw std::length_error ("Il nodo non ha figlio destro!");
}

template <typename Data>
const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const {
  if (HasLeftChild())
    return *sx;
  else
    throw std::length_error ("Il nodo non ha figlio sinistro!");
}

template <typename Data>
const struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const {
  if (HasRightChild())
    return *dx;
  else
    throw std::length_error ("Il nodo non ha figlio destro!");
}

/* ************************************************************************** */

//BinaryTreeLnk

//Costruttori

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const LinearContainer<Data>& container) {

  QueueVec<BinaryTreeLnk<Data>::NodeLnk*> coda;

  if (!container.Empty()) {
    root = new NodeLnk();
    coda.Enqueue(root);
  }

  for (ulong i = 0; i < container.Size(); i++) {
    NodeLnk* curr = coda.HeadNDequeue();
    curr->Element() = container[i];

    if (2*i+1 < container.Size()){
      curr->sx = new NodeLnk();
      coda.Enqueue(curr->sx);
    }

    if (2*(i+1) < container.Size()){
      curr->dx = new NodeLnk();
      coda.Enqueue(curr->dx);
    }

  }

  size = container.Size();

}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk& tree) {
  if (!tree.Empty()) {
    root = new NodeLnk();
    *root = *(tree.root);
    size = tree.size;
  }
}

template <typename Data>
BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk&& tree) noexcept {
  std::swap(tree.root, root);
  std::swap(size, tree.size);
}

template <typename Data>
BinaryTreeLnk<Data>::~BinaryTreeLnk() {
  delete root;
}

//Operatori
template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk& tree) {
  Clear();
  if (!tree.Empty()) {
    root = new NodeLnk();
    *root = *(tree.root);
    size = tree.size;
  }
  return *this;
}

template <typename Data>
BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk&& tree) noexcept {
  std::swap(tree.root, root);
  std::swap(size, tree.size);
  return *this;
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk& tree) const noexcept {
  return BinaryTree<Data>::operator==(tree);
}

template <typename Data>
bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk& tree) const noexcept {
  return !(*this==tree);
}



template <typename Data>
void BinaryTreeLnk<Data>::Clear() {

  delete root;
  root = nullptr;
  size = 0;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const {

  if (!Container::Empty())
    return *root;
  else
    throw std::length_error ("L'albero è vuoto!");
}

/* ************************************************************************** */

}
