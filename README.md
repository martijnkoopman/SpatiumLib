# SpatiumLib
C++ header-only library for 2D/3D computer graphics, image processing and mathematics (linear algebra and statistics).

**Looking for examples? Go directly to the [Examples page](https://github.com/martijnkoopman/SpatiumLib/wiki).**

## About
SpatiumLib has the following key points:

**Applicability**

* Header-only. No platform dependent library linking.
* Written in C++11.
* No dependencies except C++ Standard Library. QtTest for unit testing.

**Education**

* Code readability more important than optimizations.
* Documentation through comments in code.
* Doxygen documentation ([read the docs](https://martijnkoopman.github.io/SpatiumLib/html/annotated.html)).
* Examples on the Wiki ([read the wiki](https://github.com/martijnkoopman/SpatiumLib/wiki)).

Performance is not a key point of SpatiumLib. There is no GPU acceleration or multithreading. This may be quite important, especially for 3D graphics.

## Content
**Looking for class references? Go directly to the [Class References page](https://martijnkoopman.github.io/SpatiumLib/html/inherits.html).**

SpatiumLib is a collection of header files (*.h) distributed over several directories. Each of these directories represents a namespace with identical name. These namespaces and their dependencies are shown in the dependency graph.

TODO: Insert namespace dependency graph 

### Namespace: spatium
Global namespace including base [Matrix](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1_matrix.html), [Vector](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1_vector.html) and [Image](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1_image.html). Also contains mathematical functions.

### Namespace: geom3d
`#include <spatium/geom3d.h>`

3D geometry namespace including classes [Matrix4x4](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1geom3d_1_1_matrix4x4.html), [Point3](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1geom3d_1_1_point3.html), [Ellipsoid](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1geom3d_1_1_ellipsoid.html) and more...

### Namespace: gfx3d
`#include <spatium/gfx3d.h>`

3D graphics namespace including classes [Mesh](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1gfx3d_1_1_mesh.html), [Camera](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1gfx3d_1_1_camera.html), [Scene](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1gfx3d_1_1_scene.html), [Renderer](https://martijnkoopman.github.io/SpatiumLib/html/classspatium_1_1gfx3d_1_1_renderer.html) and more...

### Namespace: gfx2d
`#include <spatium/gfx2d.h>`

2D graphics namespace including draw functions for lines, circles, rectangles and Bezier curves.

### Namespace: imgproc
`#include <spatium/imgproc.h>`

Image processing namespace including classes and functions for image convolution (thresholding, blurring, etc.) and feature extraction (corners, edges). 

## Usage
1. Clone or download this repository.
```
git clone https://github.com/martijnkoopman/SpatiumLib.git
```

2. Copy directory `spatium` from `include` into your project. 

This directory has the following subdirectories, each being a namespace:

* `geom3d`
* `gfx2d`
* `gfx3d`
* `imgproc`

3. Include the required files.

For example: `#include <spatium/Matrix.h>`

You can include individual files (classes) or whole namespaces. You can also delete namespaces (directories) that you don't need as long as it isn't a dependecny for other namespaces you're using. See the dependency graph.

### Unit testing...
TODO

## Background
TODO

## License
This library is licensed under the GNU General Public License 3.0 - see the [LICENSE.md](LICENSE.md) file for details.
