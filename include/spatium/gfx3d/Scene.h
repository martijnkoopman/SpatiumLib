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
#include "SceneObject.h"

#include <vector>

namespace spatium {
namespace gfx3d {

/// \class Scene
/// \brief 3D scene
///
/// A scene is a collection of one Camera, one Light and one or more
/// SceneObjects.
class Scene
{
public:
  // TODO: Rule of 5

private:
  Camera m_camera;
  Light m_light;
  std::vector<SceneObject> m_sceneObjects;
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_SCENE_H
