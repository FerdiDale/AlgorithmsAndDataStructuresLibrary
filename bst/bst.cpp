
#include <iostream>

namespace lasd {

/* ************************************************************************** */

template <typename Data>
BST<Data>::BST(const LinearContainer<Data>& container) {
  for (ulong i = 0; i < container.Size(); i++) {
    Insert(container[i]);
  }
}

template <typename Data>
BST<Data>& BST<Data>::operator=(const BST<Data>& tree) {
  BST<Data> temp (tree);
  std::swap(*this, temp);
  return *this;
}

template <typename Data>
BST<Data>& BST<Data>::operator=(BST<Data>&& tree) noexcept {
  std::swap (root, tree.root);
  std::swap (size, tree.size);
  return *this;
}

template <typename Data>
bool BST<Data>::operator==(const BST<Data>& tree) const noexcept {

  if (Container::Size() == tree.Container::Size()) {

    BTInOrderIterator<Data> it1 (*this);
    BTInOrderIterator<Data> it2 (tree);

    while (!it1.Terminated()) {
      if (*it1 != *it2) return false;
      it1.operator++();
      it2.operator++();
    }

    return true;

  }
  else return false;

}

template <typename Data>
bool BST<Data>::operator!=(const BST<Data>& tree) const noexcept {
  return !(*this == tree);
}

template <typename Data>
const Data& BST<Data>::Min() const {
  if (!Empty()) return (FindPointerToMin(root))->Element();
  else throw std::length_error ("L'albero è vuoto!");
}

template <typename Data>
Data BST<Data>::MinNRemove() {
  if (!Empty()) return (DataNDelete(DetachMin(root)));
  else throw std::length_error ("L'albero è vuoto!");
}

template <typename Data>
void BST<Data>::RemoveMin() {
  if (!Empty()) delete DetachMin(root);
  else throw std::length_error ("L'albero è vuoto!");
}

template <typename Data>
const Data& BST<Data>::Max() const {
  if (!Empty()) return (FindPointerToMax(root))->Element();
  else throw std::length_error ("L'albero è vuoto!");
}

template <typename Data>
Data BST<Data>::MaxNRemove() {
  if (!Empty()) return (DataNDelete(DetachMax(root)));
  else throw std::length_error ("L'albero è vuoto!");
}

template <typename Data>
void BST<Data>::RemoveMax() {
  if (!Empty()) delete DetachMax(root);
  else throw std::length_error ("L'albero è vuoto!");
}

template <typename Data>
const Data& BST<Data>::Predecessor(const Data& dato) const {
  struct BinaryTreeLnk<Data>::NodeLnk* const * temp = FindPointerToPredecessor(root, dato);
  if (temp!=nullptr) return (*temp)->Element();
  else throw std::length_error ("Il predecessore è assente!");
}

template <typename Data>
Data BST<Data>::PredecessorNRemove(const Data& dato) {
  struct BinaryTreeLnk<Data>::NodeLnk** temp = FindPointerToPredecessor(root, dato);
  if (temp!=nullptr) return DataNDelete(Detach(*temp));
  else throw std::length_error ("Il predecessore è assente!");
}

template <typename Data>
void BST<Data>::RemovePredecessor(const Data& dato) {
  struct BinaryTreeLnk<Data>::NodeLnk** temp = FindPointerToPredecessor(root, dato);
  if (temp!=nullptr) delete (Detach(*temp));
  else throw std::length_error ("Il predecessore è assente!");
}

template <typename Data>
const Data& BST<Data>::Successor(const Data& dato) const {
  struct BinaryTreeLnk<Data>::NodeLnk* const * temp = FindPointerToSuccessor(root, dato);
  if (temp!=nullptr) return (*temp)->Element();
  else throw std::length_error ("Il successore è assente!");
}

template <typename Data>
Data BST<Data>::SuccessorNRemove(const Data& dato) {
  struct BinaryTreeLnk<Data>::NodeLnk** temp = FindPointerToSuccessor(root, dato);
  if (temp!=nullptr) return DataNDelete(Detach(*temp));
  else throw std::length_error ("Il successore è assente!");
}

template <typename Data>
void BST<Data>::RemoveSuccessor(const Data& dato) {
  struct BinaryTreeLnk<Data>::NodeLnk** temp = FindPointerToSuccessor(root, dato);
  if (temp!=nullptr) delete (Detach(*temp));
  else throw std::length_error ("Il successore è assente!");
}

template <typename Data>
bool BST<Data>::Insert(const Data& dato) {
    struct BinaryTreeLnk<Data>::NodeLnk** temp = &FindPointerTo(root, dato);
    if (*temp == nullptr) {
      *temp = new NodeLnk(dato);
      size++;
      return true;
    }
    else return false;
}

template <typename Data>
bool BST<Data>::Insert(Data&& dato) {
    struct BinaryTreeLnk<Data>::NodeLnk** temp = &FindPointerTo(root, dato);
    if (*temp == nullptr) {
      *temp = new NodeLnk(std::move(dato));
      size++;
      return true;
    }
    else return false;
}

template <typename Data>
bool BST<Data>::Remove(const Data& dato) {
  if (!Empty()) {
    struct BinaryTreeLnk<Data>::NodeLnk** temp = &FindPointerTo(root, dato);
    bool ret = (*temp!=nullptr);
    delete Detach(*temp);
    return ret;
  }
  else return false;
}

template <typename Data>
bool BST<Data>::Exists(const Data& dato) const noexcept {
  return (FindPointerTo(root, dato) != nullptr);
}

// Funzioni ausiliarie

template <typename Data>
Data BST<Data>::DataNDelete(struct BinaryTreeLnk<Data>::NodeLnk* nodo) {

  Data temp = nodo->Element();
  nodo->sx = nullptr;
  nodo->dx = nullptr;
  delete nodo;
  return temp;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Detach(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {

  if (nodo != nullptr) {
    if (nodo->HasLeftChild() && nodo->HasRightChild()) {
      struct BinaryTreeLnk<Data>::NodeLnk* temp = (DetachMin(nodo->dx));
      std::swap(nodo->Element(), temp->Element());
      return temp;
    }
    else {
      if (nodo->HasLeftChild()){
        return Skip2Left(nodo);
      }
      else return Skip2Right(nodo);
    }
  }
  else return nodo;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DetachMax(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {
    return Skip2Left(FindPointerToMax(nodo));
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BST<Data>::DetachMin(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {
    return Skip2Right(FindPointerToMin(nodo));
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Left(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {

  struct BinaryTreeLnk<Data>::NodeLnk* temp = nullptr;
  if (nodo!=nullptr){
    std::swap(nodo->sx, temp);
    std::swap(nodo, temp);
    size--;
  }
  return temp;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* BST<Data>::Skip2Right(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {

  struct BinaryTreeLnk<Data>::NodeLnk* temp = nullptr;
  if (nodo!=nullptr){
    std::swap(nodo->dx, temp);
    std::swap(nodo, temp);
    size--;
  }
  return temp;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerToMin(struct BinaryTreeLnk<Data>::NodeLnk* const & nodo) const noexcept {

   if (nodo != nullptr){

      struct BinaryTreeLnk<Data>::NodeLnk* curr = nodo;
      struct BinaryTreeLnk<Data>::NodeLnk* const * currptr = &nodo;

      while (curr->HasLeftChild()){
        currptr = &curr->sx;
        curr = curr->sx;
      }
      return *currptr;
  }
  else return nodo;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMin(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {
  return const_cast<struct BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMin(nodo));}


template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerToMax(struct BinaryTreeLnk<Data>::NodeLnk* const & nodo) const noexcept {

   if (nodo != nullptr){

     struct BinaryTreeLnk<Data>::NodeLnk* curr = nodo;
     struct BinaryTreeLnk<Data>::NodeLnk* const * currptr = &nodo;

     while (curr->HasRightChild()) {
       currptr = &curr->dx;
       curr = curr->dx;
     }

     return *currptr;
  }
  else return nodo;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerToMax(struct BinaryTreeLnk<Data>::NodeLnk*& nodo) noexcept {
  return const_cast<struct BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerToMax(nodo));}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* const & BST<Data>::FindPointerTo(struct BinaryTreeLnk<Data>::NodeLnk* const & nodo, const Data& dato) const noexcept {

   if (nodo != nullptr){

    struct BinaryTreeLnk<Data>::NodeLnk* curr = nodo;
    struct BinaryTreeLnk<Data>::NodeLnk* const * currptr = &nodo;

    while (curr != nullptr && curr->Element()!=dato){

      if (curr->Element() < dato){
        currptr = &(curr->dx);
        curr = curr->dx;
      }
      else {
        if (curr->Element() > dato){
          currptr = &(curr->sx);
           curr = curr->sx;
         }
      }

    }

    return *currptr;

  }
  else return nodo;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk*& BST<Data>::FindPointerTo(struct BinaryTreeLnk<Data>::NodeLnk*& nodo, const Data& dato) noexcept {
  return const_cast<struct BinaryTreeLnk<Data>::NodeLnk*&>(static_cast<const BST<Data> *>(this)->FindPointerTo(nodo, dato));
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* const * BST<Data>::FindPointerToPredecessor(struct BinaryTreeLnk<Data>::NodeLnk* const & nodo, const Data& dato) const noexcept {

  if (nodo != nullptr){

   struct BinaryTreeLnk<Data>::NodeLnk* curr = nodo;
   struct BinaryTreeLnk<Data>::NodeLnk* const * currptr = &nodo;
   struct BinaryTreeLnk<Data>::NodeLnk* const * ret = nullptr;

   while (curr != nullptr){

     if (curr->Element() < dato){
       ret = currptr;
       currptr = &(curr->dx);
       curr = curr->dx;
     }
     else {
       if (curr->Element() > dato){
         currptr = &(curr->sx);
         curr = curr->sx;
        }
        else {
          if (curr->HasLeftChild()) ret = &FindPointerToMax(curr->sx);
          break;
        }
     }

   }

   return ret;

 }
 else return nullptr;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk** BST<Data>::FindPointerToPredecessor(struct BinaryTreeLnk<Data>::NodeLnk*& nodo, const Data& dato) noexcept {
  return const_cast<struct BinaryTreeLnk<Data>::NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToPredecessor(nodo, dato));
}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk* const * BST<Data>::FindPointerToSuccessor(struct BinaryTreeLnk<Data>::NodeLnk* const & nodo, const Data& dato) const noexcept {

  if (nodo != nullptr){

   struct BinaryTreeLnk<Data>::NodeLnk* curr = nodo;
   struct BinaryTreeLnk<Data>::NodeLnk* const * currptr = &nodo;
   struct BinaryTreeLnk<Data>::NodeLnk* const * ret = nullptr;

   while (curr != nullptr){

     if (curr->Element() < dato){
       currptr = &(curr->dx);
       curr = curr->dx;
     }
     else {
       if (curr->Element() > dato){
         ret = currptr;
         currptr = &(curr->sx);
         curr = curr->sx;
        }
        else {
          if (curr->HasRightChild()) ret = &FindPointerToMin(curr->dx);
          break;
        }
     }

   }

   return ret;

 }
 else return nullptr;

}

template <typename Data>
struct BinaryTreeLnk<Data>::NodeLnk** BST<Data>::FindPointerToSuccessor(struct BinaryTreeLnk<Data>::NodeLnk*& nodo, const Data& dato) noexcept {
  return const_cast<struct BinaryTreeLnk<Data>::NodeLnk**>(static_cast<const BST<Data> *>(this)->FindPointerToSuccessor(nodo, dato));
}

/* ************************************************************************** */

}
