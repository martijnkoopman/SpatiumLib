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

#ifndef SPATIUMLIB_IDX_TREENODE_H
#define SPATIUMLIB_IDX_TREENODE_H

#include <vector> // std::vector
#include <memory> // std::weak_ptr, std::shared_ptr

namespace spatium {
namespace idx {

/// \class TreeNode
/// \brief Node in a Tree.
///
/// TreeNode is a node in a Tree. Each node can have any number of children.
/// A TreeNode is a container for a single object. The type of this object is
/// passed as template argument.
template<typename G>
class TreeNode
{
public:

  /// Constructor
  ///
  /// \param[in] parent Parent node
  /// \param[in] estimatedChildCount Estimated child count. Will allocate
  ///                                memory for the child references in
  ///                                advance to prevent later reallocation.
  TreeNode(std::weak_ptr<TreeNode<G>> parent = std::weak_ptr<TreeNode<G>>(), size_t estimatedChildCount = 0)
    : m_parent(parent)
    , m_children(0)
    , m_object()
  {
    m_children.reserve(estimatedChildCount);
  }

  /// Constructor
  ///
  /// \param[in] object Object for node
  /// \param[in] parent Parent node
  /// \param[in] estimatedChildCount Estimated child count. Will allocate
  ///                                memory for the child references in
  ///                                advance to prevent later reallocation.
  TreeNode(const G &object, std::weak_ptr<TreeNode<G>> parent = std::weak_ptr<TreeNode<G>>(), size_t estimatedChildCount = 0)
    : m_object(object)
    , m_parent(parent)
    , m_children(0)
  {
    m_children.reserve(estimatedChildCount);
  }

  /// \return True when child count > 0, otherwise false.
  bool hasChildren()
  {
    return (m_children.size() > 0);
  }

  /// Get child count.
  ///
  /// \return Child count
  size_t childCount() const
  {
    return m_children.size();
  }

  /// Get a child.
  ///
  /// \param[in] index Child index
  /// \return Child or nullptr
  std::shared_ptr<TreeNode<G>> child(size_t index) const
  {
    if (index >= m_children.size())
    {
      return nullptr;
    }
    return m_children[index];
  }

  /// Add child node.
  ///
  /// \param[in] parentSharedPtr Parent node (this object) as shared pointer.
  /// \param[in] object Object
  /// \return Created child node
  std::shared_ptr<TreeNode<G>> addChild(const std::shared_ptr<TreeNode<G>> &parentSharedPtr, const G &object)
  {
    std::shared_ptr<TreeNode<G>> node = std::make_shared<TreeNode<G>>(object, parentSharedPtr);
    m_children.push_back(node);
    return node;
  }

  /// Set the object.
  G object() const
  {
    return m_object;
  }

  /// Get the object.
  void setObject(const G &object)
  {
    m_object = object;
  }

protected:
  std::weak_ptr<TreeNode<G>> m_parent;
  std::vector<std::shared_ptr<TreeNode<G>>> m_children;
  G m_object;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_TREENODE_H
