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

#ifndef SPATIUMLIB_GFX3D_SCENE_H
#define SPATIUMLIB_GFX3D_SCENE_H

#include "Camera.h"
#include "Light.h"
#include "RenderObject.h"

#include <memory> // std::shared_ptr
#include <vector> // std::vector

namespace spatium {
namespace gfx3d {

/// \class Scene
/// \brief 3D scene
///
/// A scene is a collection of:
/// - one camera
/// - zero or more lights
/// - zero or more render objects
class Scene
{
public:
  /// Constructor
  Scene() = default;

  /// Copy constructor
  /// The references to the scene objects will be copied. As a result objects
  /// will be references from multiple scenes.
  Scene(const Scene &scene) = default;

  ///\todo Rule of 5. std::move

  /// Destructor
  virtual ~Scene() = default;

  /// Set the camera
  ///
  /// \param[in] camera The camera
  void setCamera(std::shared_ptr<Camera> camera)
  {
    // Use std::swap?
    m_camera = camera;
  }

  /// Get the camera
  ///
  /// \return The camera
  std::shared_ptr<Camera> camera() const
  {
    return m_camera;
  }

  /// Add a light
  ///
  /// \param[in] light Light
  void addLight(std::shared_ptr<Light> light)
  {
    m_lights.push_back(light);
  }

  /// Get all lights
  ///
  /// \return All lights
  std::vector<std::shared_ptr<Light>> lights() const
  {
    return m_lights;
  }

  /// Add a render object
  ///
  /// \param[in] renderObject Render object
  void addRenderObject(std::shared_ptr<RenderObject> renderObject)
  {
    m_renderObjects.push_back(renderObject);
  }

  /// Get all render objects
  ///
  /// \return All render objects
  std::vector<std::shared_ptr<RenderObject>> renderObjects() const
  {
    return m_renderObjects;
  }

private:
  std::shared_ptr<Camera> m_camera; // TODO: Assign nullptr?
  std::vector<std::shared_ptr<Light>> m_lights;
  std::vector<std::shared_ptr<RenderObject>> m_renderObjects;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_SCENE_H
