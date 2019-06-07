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

#include "Bounds.h"

#include <array> // std::array
#include <vector> // std::vector
#include <memory> // std::weak_ptr, std::shared_ptr

namespace spatium {
namespace idx {

/// \class TreeNode
/// \brief Node in a tree.
///
/// A node in a tree has one parent (with exception of the root node) and
/// optionally children. The nodes without children are the leaf nodes.
template<typename G>
class TreeNode
{
public:
  /// Constructor
  TreeNode(std::weak_ptr<TreeNode<G>> parent = std::weak_ptr<TreeNode<G>>(), size_t estimatedChildCount = 0)
    : m_parent(parent)
    , m_children(0)
    , m_geometries()
  {
    m_children.reserve(estimatedChildCount);
  }

  bool hasChildren()
  {
    return (m_children.size() > 0);
  }

  size_t childCount() const
  {
    return m_children.size();
  }

  /// Get a child
  std::shared_ptr<TreeNode<G>> child(size_t index) const
  {
    if (index >= m_children.size())
    {
      return nullptr;
    }
    return m_children[index];
  }

  size_t geometryCount() const
  {
    return m_geometries.size();
  }

  G geometry(size_t index) const
  {
    if (index >= m_geometries.size())
    {
      return G();
    }
    return m_geometries[index];
  }

  void addGeometry(const G &geom)
  {
    m_geometries.push_back(geom);
  }

  void clearGeometries()
  {
    m_geometries.clear();
  }

//    // Set values
//    auto rowIt = array.begin();
//    auto dataIt = m_data.begin();
//    while(rowIt != array.end() && dataIt != m_data.end())
//    {
//      *dataIt = *rowIt;

//      ++rowIt;
//      ++dataIt;
//    }
//  }

protected:
  std::weak_ptr<TreeNode<G>> m_parent;
  std::vector<std::shared_ptr<TreeNode<G>>> m_children;
  std::vector<G> m_geometries;
};

// Forward declare iterator
template<typename G>
class TreeIterator;

/// \class Tree
/// \brief Tree with variable number of children per tree node.
template<typename G>
class Tree
{
public:
  Tree(const std::shared_ptr<TreeNode<G>> &root = std::make_shared<TreeNode<G>>())
    : m_root(root)
  {
  }

  std::shared_ptr<TreeNode<G>> root() const
  {
    return m_root;
  }

  TreeIterator<G> beginDepthFirst() { return TreeIterator<G>(*this); }
  TreeIterator<G> endDepthFirst() { return TreeIterator<G>(*this, true); }

protected:
  const std::shared_ptr<TreeNode<G>> m_root;
};

/// \class TreeIterator
/// \brief Iterator that traverses a tree from top to bottom depth first.
template<typename G>
class TreeIterator
{
  TreeIterator(const Tree<G> &tree, bool end = false)
    : m_tree(tree)
  {
    if (end)
    {
      // Find last node of tree depth first
      std::shared_ptr<TreeNode<G>> node = m_tree.root();
      while(node->hasChildren())
      {
        node = node->child(node->childCount() - 1);
      }
      m_currentParent = node;
      m_currentChildIndex = -1;
    }
    else
    {
      m_currentParent = m_tree.root();
    }
  }

  TreeIterator(const Tree<G> &tree, std::shared_ptr<TreeNode<G>> currentParent, long currentChildIndex)
    : m_tree(tree)
    , m_currentParent(currentParent)
    , m_currentChildIndex(currentChildIndex)
  {
  }

  bool operator== (const TreeIterator<G> &other)
  {
      return (m_tree== other.m_tree &&
              m_currentParent== other.m_currentParent &&
              m_currentChildIndex== other.m_currentChildIndex);
  }

  bool operator!= (const TreeIterator<G> &other)
  {
      return !(*this == other);
  }

  TreeIterator<G>& operator++()
  {
    // TODO: Update m_currentParent and  m_currentChildIndex

    if (m_currentChildIndex == -1)
    {
      if (m_currentParent->hasChildren())
      {

      }
    }

    return *this;
  }

  std::shared_ptr<TreeNode<G>> operator*() const // Return reference? const reference?
  {
    if (m_currentChildIndex < 0)
    {
      return m_currentParent;
    }
    else
    {
      return m_currentParent->child(m_currentChildIndex); // TODO Cast to size_t
    }
  }

protected:
  Tree<G> m_tree;

  std::shared_ptr<TreeNode<G>> m_currentParent;
  long m_currentChildIndex;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_TREE_H
