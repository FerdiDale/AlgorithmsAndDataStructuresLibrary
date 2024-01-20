#include <iostream>

namespace lasd {

/* ************************************************************************** */

//Node

template <typename Data>
Data& BinaryTree<Data>::Node::Element() noexcept {
  return element;
}

template <typename Data>
const Data& BinaryTree<Data>::Node::Element() const noexcept {
  return (const Data&) element;
}

template <typename Data>
bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
  return !HasLeftChild()&&!HasRightChild();
}

template <typename Data>
bool BinaryTree<Data>::Node::operator==(const Node& nodo) const noexcept {

  bool acc = true;

  if (IsLeaf() && nodo.IsLeaf()) return Element()==nodo.Element();
  else {

    if (HasLeftChild() && nodo.HasLeftChild()) acc = (acc && (LeftChild()==nodo.LeftChild()));
    else if (HasLeftChild() || nodo.HasLeftChild()) return false;

    if (HasRightChild() && nodo.HasRightChild()) acc = (acc && (RightChild()==nodo.RightChild()));
    else if (HasRightChild() || nodo.HasRightChild()) return false;

    return acc;
  }

}

template <typename Data>
bool BinaryTree<Data>::Node::operator!=(const Node& nodo) const noexcept {
  return !(*this==nodo);
}

/* ************************************************************************** */

//BinaryTree

template <typename Data>
bool BinaryTree<Data>::operator==(const BinaryTree& tree) const noexcept {

  if (Container::Empty() && tree.Container::Empty()) return true;
  else {
    if (!Container::Empty() && !tree.Container::Empty()) return (Root()==tree.Root());
    else return false;
  }

}

template <typename Data>
bool BinaryTree<Data>::operator!=(const BinaryTree& tree) const noexcept {
  return !(*this==tree);
}

//Map e Fold

template <typename Data>
void BinaryTree<Data>::Map(MapFunctor funct, void* parametro) {
  MapPreOrder(funct, parametro);
}

template <typename Data>
void BinaryTree<Data>::Fold(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  FoldPreOrder(funct, parametro, accumulatore);
}

template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* parametro) {
  if (!Container::Empty()) MapPreOrder(funct, parametro, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  if (!Container::Empty()) FoldPreOrder(funct, parametro, accumulatore, Root());
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* parametro) {
  if (!Container::Empty()) MapInOrder(funct, parametro, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  if (!Container::Empty()) FoldInOrder(funct, parametro, accumulatore, Root());
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* parametro) {
  if (!Container::Empty()) MapPostOrder(funct, parametro, Root());
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  if (!Container::Empty()) FoldPostOrder(funct, parametro, accumulatore, Root());
}

template <typename Data>
void BinaryTree<Data>::MapBreadth(MapFunctor funct, void* parametro) {
  BTBreadthIterator<Data> iteratore (*this);
  while (!iteratore.Terminated()) {
    funct(*iteratore, parametro);
    iteratore.operator++();
  }
}

template <typename Data>
void BinaryTree<Data>::FoldBreadth(FoldFunctor funct, const void* parametro, void* accumulatore) const {
  BTBreadthIterator<Data> iteratore (*this);
  while (!iteratore.Terminated()) {
    funct(*iteratore, parametro, accumulatore);
    iteratore.operator++();
  }
}

// Funzioni ausiliarie

template <typename Data>
void BinaryTree<Data>::MapPreOrder(MapFunctor funct, void* parametro, Node& nodo) {
    funct(nodo.Element(), parametro);
    if (nodo.HasLeftChild()) MapPreOrder(funct, parametro, nodo.LeftChild());
    if (nodo.HasRightChild()) MapPreOrder(funct, parametro, nodo.RightChild());
}

template <typename Data>
void BinaryTree<Data>::FoldPreOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const {
    funct(nodo.Element(), parametro, accumulatore);
    if (nodo.HasLeftChild()) FoldPreOrder(funct, parametro, accumulatore, nodo.LeftChild());
    if (nodo.HasRightChild()) FoldPreOrder(funct, parametro, accumulatore, nodo.RightChild());
}

template <typename Data>
void BinaryTree<Data>::MapInOrder(MapFunctor funct, void* parametro, Node& nodo) {
    if (nodo.HasLeftChild()) MapInOrder(funct, parametro, nodo.LeftChild());
    funct(nodo.Element(), parametro);
    if (nodo.HasRightChild()) MapInOrder(funct, parametro, nodo.RightChild());
}

template <typename Data>
void BinaryTree<Data>::FoldInOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const {
    if (nodo.HasLeftChild()) FoldInOrder(funct, parametro, accumulatore, nodo.LeftChild());
    funct(nodo.Element(), parametro, accumulatore);
    if (nodo.HasRightChild()) FoldInOrder(funct, parametro, accumulatore, nodo.RightChild());
}

template <typename Data>
void BinaryTree<Data>::MapPostOrder(MapFunctor funct, void* parametro, Node& nodo) {
    if (nodo.HasLeftChild()) MapPostOrder(funct, parametro, nodo.LeftChild());
    if (nodo.HasRightChild()) MapPostOrder(funct, parametro, nodo.RightChild());
    funct(nodo.Element(), parametro);
}

template <typename Data>
void BinaryTree<Data>::FoldPostOrder(FoldFunctor funct, const void* parametro, void* accumulatore, Node& nodo) const {
    if (nodo.HasLeftChild()) FoldPostOrder(funct, parametro, accumulatore, nodo.LeftChild());
    if (nodo.HasRightChild()) FoldPostOrder(funct, parametro, accumulatore, nodo.RightChild());
    funct(nodo.Element(), parametro, accumulatore);
}

//Iteratori

//BTPreOrderIterator

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree) {
  if (!tree.Empty()) {
    root = &(tree.Root());
    curr = root;
  }
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(const BTPreOrderIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  stack = StackVec<struct BinaryTree<Data>::Node*>(iterator.stack);
}

template <typename Data>
BTPreOrderIterator<Data>::BTPreOrderIterator(BTPreOrderIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(stack, iterator.stack);
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(const BTPreOrderIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  stack = iterator.stack;
  return *this;
}

template <typename Data>
BTPreOrderIterator<Data>& BTPreOrderIterator<Data>::operator=(BTPreOrderIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(stack, iterator.stack);
  return *this;
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator& iterator) const noexcept {
  return (root==iterator.root && curr==iterator.curr && stack==iterator.stack);
}

template <typename Data>
bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator& iterator) const noexcept {
  return !(*this==iterator);
}

template <typename Data>
Data& BTPreOrderIterator<Data>::operator*() const {
  if (!Terminated()) return curr->Element();
  else throw std::out_of_range ("L'iteratore è terminato!");
}

template <typename Data>
bool BTPreOrderIterator<Data>::Terminated() const noexcept {
  return (curr == nullptr);
}

template <typename Data>
void BTPreOrderIterator<Data>::operator++() {
  if (Terminated()) throw std::out_of_range ("L'iteratore è terminato!");
  else {

    if (curr->IsLeaf()) {

      if (stack.Empty()) curr = nullptr;
      else curr = stack.TopNPop();

    }
    else {

      if (curr->HasLeftChild()) {

        if (curr->HasRightChild()) stack.Push(&(curr->RightChild()));
        curr = &(curr->LeftChild());

      }
      else curr = &(curr->RightChild());

    }

  }
}

template <typename Data>
void BTPreOrderIterator<Data>::Reset() noexcept {
  curr = root;
  stack.Clear();
}

//BTPostOrderIterator

template <typename Data>
struct BinaryTree<Data>::Node* BTPostOrderIterator<Data>::MinLeaf(struct BinaryTree<Data>::Node* nodo) noexcept {

  if (nodo != nullptr) {

    if (nodo->IsLeaf()) return nodo;
    else {

      if (nodo->HasLeftChild()) {
        stack.Push(nodo);
        return MinLeaf(&(nodo->LeftChild()));
      }
      else {
        stack.Push(nodo);
        return MinLeaf(&(nodo->RightChild()));
      }

    }

  }

  return nullptr;

}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree) {
  if (!tree.Empty()) {
    root = &(tree.Root());
    curr = MinLeaf(&(tree.Root()));
  }
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(const BTPostOrderIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  stack = StackVec<struct BinaryTree<Data>::Node*>(iterator.stack);
}

template <typename Data>
BTPostOrderIterator<Data>::BTPostOrderIterator(BTPostOrderIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(stack, iterator.stack);
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(const BTPostOrderIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  stack = iterator.stack;
  return *this;
}

template <typename Data>
BTPostOrderIterator<Data>& BTPostOrderIterator<Data>::operator=(BTPostOrderIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(stack, iterator.stack);
  return *this;
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator& iterator) const noexcept {
  return (root==iterator.root && curr==iterator.curr && stack==iterator.stack);
}

template <typename Data>
bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator& iterator) const noexcept {
  return !(*this==iterator);
}

template <typename Data>
Data& BTPostOrderIterator<Data>::operator*() const {
  if (!Terminated()) return curr->Element();
  else throw std::out_of_range ("L'iteratore è terminato!");
}

template <typename Data>
bool BTPostOrderIterator<Data>::Terminated() const noexcept{
  return (curr == nullptr);
}

template <typename Data>
void BTPostOrderIterator<Data>::operator++() {

  if (Terminated()) throw std::out_of_range ("L'iteratore è terminato!");
  else {

    if (stack.Empty()) curr = nullptr;

    else {

        if (stack.Top()->HasLeftChild()) {

        if (curr == &(stack.Top()->LeftChild())) {

          if (stack.Top()->HasRightChild()) curr = MinLeaf(&(stack.Top()->RightChild()));
          else curr = stack.TopNPop();

        }
        else curr = stack.TopNPop();

      }

    }

  }

}

template <typename Data>
void BTPostOrderIterator<Data>::Reset() noexcept {
  stack.Clear();
  curr = MinLeaf(root);
}

//BTInOrderIterator

template <typename Data>
struct BinaryTree<Data>::Node* BTInOrderIterator<Data>::Min(struct BinaryTree<Data>::Node* nodo) noexcept {

  if (nodo != nullptr) {

    if (nodo->HasLeftChild()) {
      stack.Push(nodo);
      return Min(&(nodo->LeftChild()));
    }
    else return nodo;

  }

  return nullptr;

}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& tree) {
  if (!tree.Empty()) {
    root = &(tree.Root());
    curr = Min(&(tree.Root()));
  }
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(const BTInOrderIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  stack = StackVec<struct BinaryTree<Data>::Node*>(iterator.stack);
}

template <typename Data>
BTInOrderIterator<Data>::BTInOrderIterator(BTInOrderIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(stack, iterator.stack);
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(const BTInOrderIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  stack = iterator.stack;
  return *this;
}

template <typename Data>
BTInOrderIterator<Data>& BTInOrderIterator<Data>::operator=(BTInOrderIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(stack, iterator.stack);
  return *this;
}

template <typename Data>
bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator& iterator) const noexcept {
  return (root==iterator.root && curr==iterator.curr && stack==iterator.stack);
}

template <typename Data>
bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator& iterator) const noexcept {
  return !(*this==iterator);
}

template <typename Data>
Data& BTInOrderIterator<Data>::operator*() const {
  if (!Terminated()) return curr->Element();
  else throw std::out_of_range ("L'iteratore è terminato!");
}

template <typename Data>
bool BTInOrderIterator<Data>::Terminated() const noexcept{
  return (curr == nullptr);
}

template <typename Data>
void BTInOrderIterator<Data>::operator++() {

  if (Terminated()) throw std::out_of_range ("L'iteratore è terminato!");
  else {

    if (!curr->HasRightChild() && stack.Empty()) curr = nullptr;

    else {

      if (curr->HasRightChild()) curr = Min(&(curr->RightChild()));
      else curr = stack.TopNPop();

    }

  }

}

template <typename Data>
void BTInOrderIterator<Data>::Reset() noexcept {
  stack.Clear();
  curr = Min(root);
}

//BTBreadthIterator

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& tree) {
  if (!tree.Empty()) {
    root = &(tree.Root());
    curr = root;
  }
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(const BTBreadthIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  queue = QueueVec<struct BinaryTree<Data>::Node*>(iterator.queue);
}

template <typename Data>
BTBreadthIterator<Data>::BTBreadthIterator(BTBreadthIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(queue, iterator.queue);
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(const BTBreadthIterator& iterator) {
  root = iterator.root;
  curr = iterator.curr;
  queue = iterator.queue;
  return *this;
}

template <typename Data>
BTBreadthIterator<Data>& BTBreadthIterator<Data>::operator=(BTBreadthIterator&& iterator) noexcept {
  std::swap(root, iterator.root);
  std::swap(curr, iterator.curr);
  std::swap(queue, iterator.queue);
  return *this;
}

template <typename Data>
bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator& iterator) const noexcept {
  return (root==iterator.root && curr==iterator.curr && queue==iterator.queue);
}

template <typename Data>
bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator& iterator) const noexcept {
  return !(*this==iterator);
}

template <typename Data>
Data& BTBreadthIterator<Data>::operator*() const {
  if (!Terminated()) return curr->Element();
  else throw std::out_of_range ("L'iteratore è terminato!");
}

template <typename Data>
bool BTBreadthIterator<Data>::Terminated() const noexcept{
  return (curr == nullptr);
}

template <typename Data>
void BTBreadthIterator<Data>::operator++() {

  if (Terminated()) throw std::out_of_range ("L'iteratore è terminato!");
  else {

    if (curr->IsLeaf() && queue.Empty()) curr = nullptr;

    else {

      if (curr->HasLeftChild()) queue.Enqueue(&(curr->LeftChild()));
      if (curr->HasRightChild()) queue.Enqueue(&(curr->RightChild()));
      curr = queue.HeadNDequeue();

    }

  }

}

template <typename Data>
void BTBreadthIterator<Data>::Reset() noexcept {
  curr = root;
  queue.Clear();
}

}
