/*
 * Program: Spatium Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMLIB_IDX_TREEITERATOR_H
#define SPATIUMLIB_IDX_TREEITERATOR_H

#include "Tree.h"

#include <memory> // std::weak_ptr, std::shared_ptr
#include <stack> // std::stack

namespace spatium {
namespace idx {

/// \class TreeIterator
/// \brief Iterator that traverses a tree from top to bottom depth first.
template<typename G>
class TreeIterator
{
public:
  TreeIterator(const Tree<G> &tree, bool end = false)
    : m_tree(tree)// Copies tree. Reference prefered?
    , m_end(end)
    , m_stack()
  {
    if (end)
    {
      // Find last node according to depth first search
      std::shared_ptr<TreeNode<G>> node = m_tree.root();
      while(node->hasChildren())
      {
        node = node->child(node->childCount() - 1);
      }
      m_stack.push(node);
    }
    else
    {
      m_stack.push(m_tree.root());
    }
  }

  bool operator==(const TreeIterator<G> &other) const
  {
    return (m_tree.root() == other.m_tree.root() &&
            m_stack.top() == other.m_stack.top() &&
            m_end == other.m_end);
  }

  bool operator!= (const TreeIterator<G> &other) const
  {
    return !(*this == other);
  }

  TreeIterator<G>& operator++() // Return const?
  {
    if (m_stack.size() == 1 && !m_stack.top()->hasChildren())
    {
      // Last node is already reached
      m_end = true;
      return *this;
    }

    // Pop node from stack
    std::shared_ptr<TreeNode<G>> node = m_stack.top();
    m_stack.pop();

    // Iterate children
    if (node->hasChildren())
    {
      for (size_t i = 0; i < node->childCount(); i++)
      {
        // Push child on stack
        auto n = std::static_pointer_cast<TreeNode<G>>(node->child(node->childCount()-1-i));
        m_stack.push(n);
      }
    }

    return *this;
  }

  std::shared_ptr<TreeNode<G>> operator*() const // Return reference? const reference?
  {
    return m_stack.top();
  }

protected:
  Tree<G> m_tree;
  bool m_end;
  std::stack<std::shared_ptr<TreeNode<G>>> m_stack;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_TREEITERATOR_H
