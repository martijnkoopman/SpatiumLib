# SpatiumLib
C++ header-only library for 2D/3D computer graphics, image processing and mathematics (linear algebra and statistics).

**Looking for examples? Go directly to the [Examples page](https://github.com/martijnkoopman/SpatiumLib/wiki).**

## About
SpatiumLib has the following key points:

**Applicability**

* Header-only. No platform dependent library linking.
* Written in C++11
* No dependencies except C++ Standard Library. QtTest for unit testing.

**Education**

* Readability of code more important than optimizations
* Documentation through comments in code
* Doxygen documentation ([read the docs](https://martijnkoopman.github.io/SpatiumLib/html/inherits.html))
* Examples on the Wiki ([read the wiki](https://github.com/martijnkoopman/SpatiumLib/wiki))

Performance is not a key point of SpatiumLib. There is no GPU acceleration or multithreading. This may be quite important, especially for 3D graphics.

## Content
**Looking for class references? Go directly to the [Class References page](https://martijnkoopman.github.io/SpatiumLib/html/inherits.html).**

SpatiumLib is a collection of header files (*.h) distributed over several directories. Each of these directories represents a namespace with identical name. These namespaces and their dependencies are shown in the dependency graph.

TODO: Insert namespace dependency graph 

### Namespace: spatium
Global namespace including base classes Matrix, Vector and Image. Also contains mathematical functions.

### Namespace: geom3d
`#include <spatium/geom3d.h>`

3D geometry namespace including classes Matrix4x4, Point3, Ellipsoid and more...

### Namespace: gfx3d
`#include <spatium/geom3d.h>`

3D graphics namespace including classes Mesh, Camera, Scene, Renderer and more...

### Namespace: gfx2d
`#include <spatium/geom3d.h>`

2D graphics namespace including draw functions for lines, circles, rectangles and Bezier curves.

### Namespace: imgproc
`#include <spatium/geom3d.h>`

Image processing namespace including classes and functions for image convolution (thresholding, blurring, etc.) and feature extraction (corners, edges). 

## Usage
Copy folder `spatium` in `include` to your project. Include the required files. You can include individual files (classes) or whole namespaces. You can also delete namescpaces that you don need as long as it isn'ta dependecny for other namespaces. See the dependency graph above.

### Unit testing...
TODO

## Background
TODO

## License
This library is licensed under the GNU General Public License 3.0 - see the [LICENSE.md](LICENSE.md) file for details.
