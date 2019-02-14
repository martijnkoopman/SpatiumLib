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

#ifndef SPATIUMLIB_GFX3D_RENDERER_H
#define SPATIUMLIB_GFX3D_RENDERER_H

#include "Scene.h"
#include <spatium/imgproc/Image.h>

#include <vector>

namespace spatium {
namespace gfx3d {

/// \class Renderer
/// \brief Abstract base class for renderers
class Renderer
{
public:

  virtual void render(const Scene &scene, const imgproc::Image<> &image) = 0;

private:
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_RENDERER_H
