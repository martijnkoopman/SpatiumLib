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

#ifndef SPATIUMLIB_IDX_QUADTREE_H
#define SPATIUMLIB_IDX_QUADTREE_H

#include "Tree.h"
#include "Bounds.h"

#include <array> // std::array
#include <vector> // std::vector
#include <memory> // std::weak_ptr, std::shared_ptr

namespace spatium {
namespace idx {

/// \class PointQuadtreeNode
/// \brief A node in a point quadtree (a quadrant)
class PointQuadtreeNode : public TreeNode<std::vector<std::array<double,2>>>
{
public:
  /// Constructor
  ///
  /// \param[in] Parent node (unset for root node)
  PointQuadtreeNode(const std::weak_ptr<PointQuadtreeNode> &parent = std::weak_ptr<PointQuadtreeNode>())
    : TreeNode<std::vector<std::array<double, 2>>> (parent, 0)
   {
   }

  /// Create 4 children nodes.
  ///
  /// \param[in] parentSharedPtr Parent node (this object) as shared pointer
  /// \return True on success, false if children already existed.
  bool createChildren(const std::shared_ptr<PointQuadtreeNode> &parentSharedPtr)
  {
    if (hasChildren())
    {
      return false;
    }

    for (size_t i = 0; i < 4; i++)
    {
      std::shared_ptr<TreeNode<std::vector<std::array<double,2>>>> n = std::make_shared<PointQuadtreeNode>(parentSharedPtr);
      m_children.push_back(n);
    }

    return true;
  }

protected:
};

/// \class PointQuadtree
/// \brief Quadtree spatial index for 2D points
class PointQuadtree : public Tree<std::vector<std::array<double,2>>>
{
public:

  /// Constructor
  PointQuadtree(const BoundingBox<double,2> &bounds, size_t maxPointCountLeaf = 100)
    : Tree<std::vector<std::array<double,2>>>(std::make_shared<PointQuadtreeNode>())
    , m_boundingBox(bounds)
    , m_maxPointCountLeaf(maxPointCountLeaf)
  {
  }

  /// Construct quadtree from points.
  ///
  /// \param[in] points Collection of points
  /// \param[in] maxPointCountLeaf Maximum number of points in a leaf node.
  ///                              Node will be split into 4 children when
  ///                              exceeded.
  /// \return Quadtree (shared pointer)
  static PointQuadtree buildFromPoints(const std::vector<std::array<double, 2>> &points, size_t maxPointCountLeaf = 100)
  {
    if (points.size() == 0)
    {
      BoundingBox<double,2> b;
      PointQuadtree p(b);
      return p;
    }

    // Compute minimum bounding rectangle
    BoundingBox<double,2> bounds = BoundingBox<double,2>::fromPoints(points);

    // Derive minimum bounding square
    double width = bounds.diameter(0);
    double height = bounds.diameter(1);
    std::array<double, 2> min = bounds.min();
    std::array<double, 2> max = bounds.max();
    if (width > height) {
      max = { min[0] + width, min[1] + width };
    } else {
      max = { min[0] + height, min[1] + height };
    }
    bounds = BoundingBox<double,2>::fromMinMax(min, max);

    // Create inital tree
    PointQuadtree tree(bounds, maxPointCountLeaf);

    // Add points
    for(auto point : points)
    {
      tree.addPoint(point);
    }

    return tree;
  }

  /// Add a point to the quadtree.
  ///
  /// This will traverse the tree topdown from root into its children untill
  /// the right leaf node is found. The leaf node will be split into 4 when the
  /// maximum point count for a leaf node is exceeded.
  ///
  /// \param[in] point Point
  /// \return True if added, false if point is outside bounding box of
  ///         quadtree.
  bool addPoint(const std::array<double, 2> &point)
  {
    if (!m_boundingBox.isInside(point))
    {
      return false;
    }

    //std::shared_ptr<TreeNode<std::vector<std::array<double,2>>>> n = this->m_root;

    std::shared_ptr<PointQuadtreeNode> node = std::static_pointer_cast<PointQuadtreeNode>(this->m_root);
    BoundingBox<double,2> bounds = m_boundingBox;
    while(node != nullptr)
    {
      // Check: Is leaf node?
      if (node->hasChildren())
      {
        // No leaf node. Pass to one of children.
        // Determine child and traverse into
        size_t childIndex = PointQuadtree::determineChild(bounds, point, bounds);
        node = std::static_pointer_cast<PointQuadtreeNode>(node->child(childIndex));
      }
      else
      {
        // Leaf node. Add point. May need splitting child.
        if (node->object().size() + 1 > m_maxPointCountLeaf)
        {
          // Split node. Create 4 children.
          node->createChildren(node);

          // Distribute points of current node over 4 new children
          for (size_t i = 0; i < node->object().size(); i++)
          {
            std::array<double, 2> childPoint = node->object()[i];

            BoundingBox<double,2> curBounds;
            size_t curChildIndex = PointQuadtree::determineChild(bounds, childPoint, curBounds);
            std::shared_ptr<PointQuadtreeNode> curChild = std::static_pointer_cast<PointQuadtreeNode>(node->child(curChildIndex));
            curChild->object().push_back(childPoint);
          }
          node->object().clear();

          // Determine next child and traverse into
          size_t childIndex = PointQuadtree::determineChild(bounds, point, bounds);
          node = std::static_pointer_cast<PointQuadtreeNode>(node->child(childIndex));
        }
        else
        {
          // Simply add point
          node->object().push_back(point);

          // Stop tree traversal
          node = nullptr;
         }
      }
    }

    return true;
  }

  /// Determine index of child (0 - 3) depening on bounding box of parent and positon of a point.
  /// Also outputs the bounding box of this child.
  ///
  /// \param[in] boundsParent Bounding box of parent
  /// \param[in] point Point positon (must be within bounding box)
  /// \param[out] boundsChild Bounding box of child
  /// \return Child index (0 = topleft, 1 = topright, 2 = bottom right, 3 = bottom left)
  static size_t determineChild(const BoundingBox<double,2> &boundsParent, const std::array<double, 2> &point, BoundingBox<double,2> &boundsChild)
  {
    std::array<double, 2> min = boundsParent.min();
    std::array<double, 2> max = boundsParent.max();
    std::array<double, 2> center = boundsParent.center();
    if (point[0] < center[0])
    {
      // Left half
      if (point[1] < center[1])
      {
        // Bottom
        boundsChild = BoundingBox<double,2>::fromMinMax(min, center);
        return 0;
      }
      else
      {
        // Top
        boundsChild = BoundingBox<double,2>::fromMinMax({ min[0], center[1] }, { center[0], max[1] });
        return 2;
      }
    }
    else
    {
      // Right half
      if (point[1] < center[1])
      {
        // Top
        boundsChild = BoundingBox<double,2>::fromMinMax({ center[0], min[1] }, { max[0], center[1] });
        return 1;
      }
      else
      {
        // Bottom
        boundsChild = BoundingBox<double,2>::fromMinMax(center, max);
        return 3;
      }
    }
  }

//  static int computeDepth(const std::shared_ptr<QuadtreeNode> &node) const
//  {
//    int depth = 1;
//    node.parent()

//    return depth;
//  }


  BoundingBox<double,2> bounds() const
  {
    return m_boundingBox;
  }

  /// Get the maximum point count in a leaf node.
  ///
  /// A node is split when it exceeds this number.
  size_t maxPointCountLeaf() const
  {
    return m_maxPointCountLeaf;
  }

protected:
  const BoundingBox<double,2> m_boundingBox;
  const size_t m_maxPointCountLeaf;
};

} // namespace idx
} // namespace spatium

#endif // SPATIUMLIB_IDX_QUADTREE_H
