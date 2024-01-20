#include <iostream>

namespace lasd {

/* ************************************************************************** */

// NodeVec

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<struct BinaryTreeVec<Data>::NodeVec*>& vector) {
  vecrif = &vector;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::NodeVec(Vector<struct BinaryTreeVec<Data>::NodeVec*>& vector, Data& dato, ulong i) {
  vecrif = &vector;
  index = i;
  element = dato;
}

template <typename Data>
BinaryTreeVec<Data>::NodeVec::~NodeVec() {
  if (HasLeftChild()) delete &LeftChild();
  if (HasRightChild()) delete &RightChild();
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept {
   if (vecrif != nullptr) return ((index*2+1 < vecrif->Size()) && ((*vecrif)[index*2+1]!= nullptr));
   else return false;
}

template <typename Data>
bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept {
  if (vecrif != nullptr) return ((index*2+2 < vecrif->Size()) && ((*vecrif)[index*2+2]!= nullptr));
  else return false;
}

template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() {
  if (HasLeftChild()) return *((*vecrif)[index*2+1]);
  else throw std::length_error ("Il nodo non ha figlio sinistro!");
}

template <typename Data>
const struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const {
  if (HasLeftChild()) return *((*vecrif)[index*2+1]);
  else throw std::length_error ("Il nodo non ha figlio sinistro!");
}

template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() {
  if (HasRightChild()) return *((*vecrif)[index*2+2]);
  else throw std::length_error ("Il nodo non ha figlio destro!");
}

template <typename Data>
const struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const {
  if (HasRightChild()) return *((*vecrif)[index*2+2]);
  else throw std::length_error ("Il nodo non ha figlio destro!");
}

//BinaryTree

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const LinearContainer<Data>& container) {

  vector = Vector<struct BinaryTreeVec<Data>::NodeVec*>(container.Size());
  size = container.Size();
  for (ulong i = 0; i < container.Size(); i++) {
    NodeVec* nodo = new NodeVec(vector, container[i], i);
    vector[i] = nodo;
  }

}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec& tree) {
  vector = Vector<struct BinaryTreeVec<Data>::NodeVec*>(tree.vector.Size());
  size = vector.Size();
  for (ulong i = 0; i < size; i++) {
    if (((tree.vector)[i]) != nullptr) {
      NodeVec* nodo = new NodeVec(vector, ((tree.vector)[i])->Element(), i);
      vector[i] = nodo;
    }
  }

}

template <typename Data>
BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec&& tree) noexcept {
  std::swap(vector, tree.vector);
  std::swap(size, tree.size);
  for (ulong i = 0; i < vector.Size(); i++) {
    if (vector[i]!=nullptr) {
      vector[i]->vecrif = &vector;
    }
  }
  for (ulong i = 0; i < tree.vector.Size(); i++) {
    if ((tree.vector[i])!=nullptr) {
      (tree.vector[i])->vecrif = &(tree.vector);
    }
  }
}

template <typename Data>
BinaryTreeVec<Data>::~BinaryTreeVec() {
  if (!Container::Empty()) delete &(Root());
}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec& tree) {

  BinaryTreeVec<Data>* temp = new BinaryTreeVec(tree);
  std::swap(*this, *temp);
  delete temp;
  return *this;

}

template <typename Data>
BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& tree) noexcept {
  std::swap(vector, tree.vector);
  std::swap(size, tree.size);
  for (ulong i = 0; i < vector.Size(); i++) {
    if (vector[i]!=nullptr) {
      vector[i]->vecrif = &vector;
    }
  }
  for (ulong i = 0; i < tree.vector.Size(); i++) {
    if ((tree.vector[i])!=nullptr) {
      (tree.vector[i])->vecrif = &(tree.vector);
    }
  }
  return *this;
}

template <typename Data>
bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec& tree) const noexcept {
  return BinaryTree<Data>::operator==(tree);
}

template <typename Data>
bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec& tree) const noexcept {
  return !(*this==tree);
}

template <typename Data>
struct BinaryTree<Data>::Node& BinaryTreeVec<Data>::Root() const {
  if (Container::Empty()) throw std::length_error ("L'albero è vuoto!");
  else return (*(vector[0]));
}

template <typename Data>
void BinaryTreeVec<Data>::Clear() {
  if (!Container::Empty()) delete &(Root());
  vector.Clear();
  size = 0;
}

template <typename Data>
void BinaryTreeVec<Data>::MapBreadth(MapFunctor funct, void* parametro) {
  for (ulong i = 0; i < size; i++) {
    funct((vector[i])->Element(), parametro);
  }
}

template <typename Data>
void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor funct,const void* parametro, void* accumulatore) const {
  for (ulong i = 0; i < size; i++) {
    funct((vector[i])->Element(), parametro, accumulatore);
  }
}
/* ************************************************************************** */

}
