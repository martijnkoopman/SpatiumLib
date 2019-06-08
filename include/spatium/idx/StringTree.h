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

#ifndef SPATIUMLIB_IDX_STRINGTREE_H
#define SPATIUMLIB_IDX_STRINGTREE_H

#include "Tree.h"

#include <string> // std::string
#include <memory> // std::weak_ptr, std::shared_ptr

namespace spatium {
namespace idx {

/// \class StringTreeNode
/// \brief A node in a string tree
class StringTreeNode : public TreeNode<std::string>
{
public:
  /// Constructor
  ///
  /// \param[in] Parent node (unset for root node)
  StringTreeNode(const std::string &str, const std::weak_ptr<StringTreeNode> &parent = std::weak_ptr<StringTreeNode>())
    : TreeNode<std::string> (str, parent, 0)
    , m_str(str)
   {
   }

  /// Add child node.
  ///
  /// \param[in] parentSharedPtr Parent node (this object) as shared pointer.
  /// \param[in] str String value
  /// \return Created child node
  std::shared_ptr<StringTreeNode> addChild(const std::shared_ptr<StringTreeNode> &parentSharedPtr, const std::string &str)
  {
    std::shared_ptr<StringTreeNode> n = std::make_shared<StringTreeNode>(str, parentSharedPtr);
    m_children.push_back(n);
    return n;
  }

  /// Set the string value.
  void setString(const std::string &str)
  {
    m_str = str;
  }

  /// Get the string value.
  std::string str() const
  {
    return m_str;
  }

protected:
  std::string m_str;
};

/// \class StringTree
/// \brief Tree structure for strings. Usefull for debugging.
class StringTree : public Tree<std::string>
{
public:

  /// Constructor
  StringTree(const std::string &str = "")
    : Tree<std::string>(str, std::make_shared<StringTreeNode>(str))
  {
  }

protected:

};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_STRINGTREE_H
