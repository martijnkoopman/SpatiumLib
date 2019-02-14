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

#ifndef SPATIUMLIB_GFX3D_WIREFRAMERENDERER_H
#define SPATIUMLIB_GFX3D_WIREFRAMERENDERER_H

#include "Renderer.h"

namespace spatium {
namespace gfx3d {

/// \class WireframeRenderer
/// \brief Wireframe renderer for meshes
///
/// WireframeRender is a renderer that renders only edges and optionally 
/// vertices, no faces. Also, the edges and vertices are not shaded, i.e.,
/// light in the scene have no effect on the rendering. The color of the
/// wireframe is determined by the object's material.
class WireframeRenderer : public Renderer
{
public:

  /// \param[in] edgeThickness Edge thickness in pixels
  /// \param[in] renderVertices Wether or not vertices should be rendered.
  ///                           Vertices are rendered as squares.
  /// \param[in] vertexSize Size of the vertex square (diameter)
  WireframeRenderer(int edgeThickness = 1, bool renderVertices = false,
                    int vertexSize = 2)
  : Renderer()
  {}

  /// Render 2D image from 3D scene.
  /// object-order rendering.
  void render(const Scene &scene, const imgproc::Image<> &image) override
  {
    // Iterate objects in scene
    for (auto renderObject : scene.renderObjects())
    {
      // Transform object to camera space
      //geom3d::Matrix4x4 relativeTransform = ...;

      // Project all edges
    }
  }

private:
  int m_edgeThickness;
  bool m_renderVertices;
  int m_vertexSize;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_WIREFRAMERENDERER_H
