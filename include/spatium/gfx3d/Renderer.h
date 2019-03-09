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
#include <spatium/Image.h>

#include <vector>

namespace spatium {
namespace gfx3d {

/// \class Renderer
/// \brief Abstract base class for renderers
class Renderer
{
public:
  /// Destructor
  virtual ~Renderer() = default;

  /// Render an image.
  ///
  /// \param[in] scene Scene to render
  /// \param[in,out] image Image
  /// \return True on success, false otherwise
  virtual bool render(const Scene &scene, Image<unsigned char, 3> &image) = 0;

private:
};

} // namespace gfx3d
} // namespace spatium

#endif // SPATIUMLIB_GFX3D_RENDERER_H
