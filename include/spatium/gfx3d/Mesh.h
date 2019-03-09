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

#ifndef SPATIUMLIB_GFX3D_MESH_H
#define SPATIUMLIB_GFX3D_MESH_H

#include "RenderObject.h"
#include "spatium/geom3d/Point3.h"

#include <vector>
#include <array>

namespace spatium {
namespace gfx3d {

/// \class Mesh
/// \brief Mesh object in a scene
///
/// A mesh is a collection of vertices connected by edges.
class Mesh : public RenderObject
{
public:
  /// Constructor
  ///
  /// \param[in] vertices List of vertex coordinates
  /// \param[in] edges List of edges.
  ///                  An edge is a tuple of two vertex indices (v1, v2).
  Mesh(const std::vector<geom3d::Point3> &vertices, const std::vector<std::array<int, 2>> &edges)
  : RenderObject ()
  , m_vertices(vertices)
  , m_edges(edges)
  {
    updateBounds();
  }

  /// Get all vertices
  ///
  /// \return Vertices
  std::vector<geom3d::Point3> vertices() const
  {
    return m_vertices;
  }

  /// Get a vertex by index.
  ///
  /// \param[in] index Index of the vertex
  /// \return Vertex coordinates
  geom3d::Point3 vertex(size_t index) const
  {
    ///\todo Bounds checking
    return m_vertices[index];
  }

  /// Get all edges
  ///
  /// \return Edges
  std::vector<std::array<int, 2>> edges() const
  {
    return m_edges;
  }

  /// Get an edge by index.
  /// An edge is a tuple of two vertex indices (v1, v2).
  ///
  /// \param[in] index Index of the edge
  /// \return The edge (v1, v2)
  std::array<int, 2> edge(size_t index) const
  {
      return m_edges[index];
  }

  /// Construct a cube mesh
  ///
  /// \param[in] diameter Diameter of the cube (width, height, length)
  /// \return Cube mesh
  static Mesh cube(double diameter=1)
  {
    const double radius = diameter/2;

    // Vertices
    std::vector<geom3d::Point3> vertices;
    // Bottom square
    vertices.push_back({-radius, -radius, -radius});
    vertices.push_back({ radius, -radius, -radius});
    vertices.push_back({ radius,  radius, -radius});
    vertices.push_back({-radius,  radius, -radius});
    // Top square
    vertices.push_back({-radius, -radius,  radius});
    vertices.push_back({ radius, -radius,  radius});
    vertices.push_back({ radius,  radius,  radius});
    vertices.push_back({-radius,  radius,  radius});

    // Edges
    std::vector<std::array<int, 2>> edges;
    // Bottom square
    edges.push_back({0,1});
    edges.push_back({1,2});
    edges.push_back({2,3});
    edges.push_back({3,0});
    // Top square
    edges.push_back({4,5});
    edges.push_back({5,6});
    edges.push_back({6,7});
    edges.push_back({7,4});
    // Intermediate
    edges.push_back({0,4});
    edges.push_back({1,5});
    edges.push_back({2,6});
    edges.push_back({3,7});

    return Mesh(vertices, edges);
  }

protected:
  void updateBounds() override
  {
    m_bounds = {0};

    for(geom3d::Point3 vertex : m_vertices)
    {
      // Update Xmin, Xmax
      double x = vertex.x();
      if (x < m_bounds[0])
      {
          m_bounds[0] = x;
      }
      if (x > m_bounds[1])
      {
          m_bounds[1] = x;
      }

      // Update Ymin, Ymax
      double y = vertex.y();
      if (y < m_bounds[2])
      {
          m_bounds[2] = y;
      }
      if (y > m_bounds[3])
      {
          m_bounds[3] = y;
      }

      // Update Zmin, Zmax
      double z = vertex.z();
      if (z < m_bounds[4])
      {
          m_bounds[4] = z;
      }
      if (z > m_bounds[5])
      {
          m_bounds[5] = z;
      }
    }

    ///\todo Update these bounds based on m_transformation. Will that work?
  }


  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Mesh &mesh)
  {
    os << "Mesh" << std::endl;
    os << "vertices: ";
    for(size_t i = 0; i < mesh.m_vertices.size(); i++)
    {
      auto vertex = mesh.m_vertices[i];
      os << i << " (" << vertex.x() << ", " << vertex.y() << ", " << vertex.z() << ") ";
    }
    os << std::endl << "edges: ";
    for(auto edge : mesh.m_edges)
    {
      os << "(" << edge[0] << ", " << edge[1] << ") ";
    }
    return os;
  }

private:
  std::vector<geom3d::Point3> m_vertices;
  std::vector<std::array<int, 2>> m_edges;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_MESH_H
