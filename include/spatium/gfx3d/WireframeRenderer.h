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
#include "Mesh.h"
#include "OrthographicCamera.h"
#include "spatium/gfx2d/Drawing.h"

#include <iostream>

namespace spatium {
namespace gfx3d {

/// \class WireframeRenderer
/// \brief Wireframe renderer for meshes
///
/// WireframeRender is a renderer that renders only edges. Also, the edges
/// and vertices are not shaded, i.e., lights in the scene have no effect on
/// the rendering. The color of the wireframe is determined by the object's
/// material.
class WireframeRenderer : public Renderer
{
public:

  /// Constructor
  ///
  /// \param[in] thickness Wire thickness in pixels
  WireframeRenderer(int thickness = 1)
    : Renderer()
    , m_edgeThickness(thickness)
  {}

  ~WireframeRenderer() override = default;

  /// Render 3D scene as 2D image
  ///
  /// \return True on success, false otherwise
  bool render(const Scene &scene, Image<unsigned char, 3> &image) override
  {
    // Check for camera in scene
    auto camera = scene.camera();
    if (camera == nullptr)
    {
      return false;
    }

    // For now only support orthographic projection
    std::shared_ptr<OrthographicCamera> cameraOrtho = std::dynamic_pointer_cast<OrthographicCamera>(camera);
    if (cameraOrtho == nullptr)
    {
      return false;
    }

    // 1. Construct view port matrix based on image resolution.
    double w = static_cast<double>(image.width());
    double h = static_cast<double>(image.height());

    geom3d::Matrix4x4 matrixViewport({ { w/2,  0 , 0, (w-1)/2 },
                                       {  0 , h/2, 0, (h-1)/2 },
                                       {  0 ,  0 , 1,     0   },
                                       {  0 ,  0 , 0,     1   } });


    // 2. Construct orthographic projection matrix based on canonical view volume.
    const double n = -cameraOrtho->near();
    const  double f = -cameraOrtho->far();
    const  double r = cameraOrtho->size() * 0.5 * w/h; // w/h = aspect ratio
    const  double l = -r; /// \TODO Loose declaration of l and b
    const  double t = cameraOrtho->size() * 0.5;
    const  double b = -t;

    geom3d::Matrix4x4 matrixOrtho({ { 2/(r-l),    0   ,    0   , -(r+l)/(r-l) },
                                    {    0   , 2/(t-b),    0   , -(t+b)/(t-b) },
                                    {    0   ,    0   , 2/(n-f), -(n+f)/(n-f) },
                                    {    0   ,    0   ,    0   ,       1      } });

    // Iterate objects in scene
    for (auto renderObject : scene.renderObjects())
    {
      // For now only support meshes
      std::shared_ptr<Mesh> mesh = std::dynamic_pointer_cast<Mesh>(renderObject);
      if (mesh)
      {
        // 3. Construct camera transformation matrix (World space -> Camera space)
        geom3d::Matrix4x4 matrixCamera = cameraOrtho->transform().matrix().inverse();

        // 4. Construct world transformation matrix (object space -> world space)
        geom3d::Matrix4x4 matrixObject = mesh->transform().matrix();

        // Combine matrices to form a matrix that projects a point from local
        // object space to screen space.
        geom3d::Matrix4x4 matrixPipeline = matrixViewport * matrixOrtho *
                                           matrixCamera * matrixObject;

        // Iterate edges in object
        for (auto edge : mesh->edges())
        {
          // Get vertices of edge
          geom3d::Point3 v1 = mesh->vertex(edge[0]);
          geom3d::Point3 v2 = mesh->vertex(edge[1]);

          // Project vertices to screen space
          geom3d::Point3 v1Proj = matrixPipeline * v1;
          geom3d::Point3 v2Proj = matrixPipeline * v2;

          std::cout << v1 << " to " << v1Proj << std::endl;
          std::cout << v2 << " to " << v2Proj << std::endl;

          int x1 = static_cast<int>(v1Proj.x());
          int y1 = static_cast<int>(v1Proj.y());
          int x2 = static_cast<int>(v2Proj.x());
          int y2 = static_cast<int>(v2Proj.y());

          // TODO: clipping of lines. Infinit loop in drawLine() otherwise!!

          gfx2d::Drawing::drawLine<unsigned char, 3>(image, {x1, y1}, {x2, y2}, mesh->color());
        }
      }
    }

    return true;
  }

private:
  int m_edgeThickness;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_WIREFRAMERENDERER_H
