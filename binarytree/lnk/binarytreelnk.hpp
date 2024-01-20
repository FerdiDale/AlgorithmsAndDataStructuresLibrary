
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../bst/bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST;

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> {

private:

  // ...

protected:

  using BinaryTree<Data>::size;

  // ...

  struct NodeLnk : virtual public BinaryTree<Data>::Node {

  private:

    // ...

  protected:

    friend class BinaryTreeLnk<Data>;
    friend class BST<Data>;

    using BinaryTree<Data>::Node::element;

    NodeLnk* sx = nullptr;
    NodeLnk* dx = nullptr;

  public:

    NodeLnk() = default;

    NodeLnk(const Data&);

    virtual ~NodeLnk();

    NodeLnk& operator=(const NodeLnk&);

    NodeLnk& operator=(NodeLnk&&) noexcept;

    bool HasLeftChild() const noexcept override;
    bool HasRightChild() const noexcept override;

    struct BinaryTreeLnk<Data>::NodeLnk& LeftChild() override;
    struct BinaryTreeLnk<Data>::NodeLnk& RightChild() override;
    const struct BinaryTreeLnk<Data>::NodeLnk& LeftChild() const override;
    const struct BinaryTreeLnk<Data>::NodeLnk& RightChild() const override;

  };

  NodeLnk* root = nullptr;

public:

  // Default constructor
  BinaryTreeLnk() = default;

  /* ************************************************************************ */

  // Specific constructors
  BinaryTreeLnk(const LinearContainer<Data>&); // A binary tree obtained from a LinearContainer

  /* ************************************************************************ */

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BinaryTreeLnk&) const noexcept;
  bool operator!=(const BinaryTreeLnk&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  struct BinaryTreeLnk<Data>::NodeLnk& Root() const override; // Override BinaryTree member (throw std::length_error when empty)

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)

  void Clear() override; // Override Container member

};

/* ************************************************************************** */

}

#include "binarytreelnk.cpp"

#endif
