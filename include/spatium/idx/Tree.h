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

#ifndef SPATIUMLIB_IDX_TREE_H
#define SPATIUMLIB_IDX_TREE_H

#include "TreeNode.h"

#include <memory> // std::weak_ptr, std::shared_ptr

namespace spatium {
namespace idx {

// Forward declare iterator
template<typename G>
class TreeIterator;

/// \class Tree
/// \brief Tree with variable number of children per tree node.
template<typename G>
class Tree
{
public:

  /// Constructor.
  ///
  /// \param[in] rootNode Root node (optional)
  Tree(const std::shared_ptr<TreeNode<G>> &rootNode = std::make_shared<TreeNode<G>>())
    : m_root(rootNode)
  {
  }

  /// Constructor
  ///
  /// \param[in] rootObject Object for root node
  /// \param[in] rootNode Root node (optional)
  Tree(const G &rootObject, const std::shared_ptr<TreeNode<G>> &rootNode = std::make_shared<TreeNode<G>>())
    : m_root(rootNode)
  {
    m_root->setObject(rootObject);
  }

  /// Get the root node.
  ///
  /// \return Root node
  std::shared_ptr<TreeNode<G>> root() const
  {
    return m_root;
  }

  TreeIterator<G> begin() { return TreeIterator<G>(*this); }
  TreeIterator<G> end() { return TreeIterator<G>(*this, true); }

protected:
  const std::shared_ptr<TreeNode<G>> m_root;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_TREE_H
