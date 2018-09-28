# SpatiumLib
C++ header-only math library for mostly geometrical operations.

This library is being developed for the application [Spatium 3D ](http://spatium3d.com/).

## Content

### Check out the [Class References page](https://martijnkoopman.github.io/SpatiumLib/html/inherits.html).

Matrix classes:
* Matrix
* Matrix4x4 *- Standard matrix for 3D affine transformations*
* Vector
* Vector3 - *Euclidean vector (x, y, z)*
* Point3 - *Euclidean point (x, y, z)*
* GeoPoint3 - *Geographical point (longitude, latitude, elevation)*

Geometry classes:
* Plane
* Sphere
* Ellipsoid
* Spheroid
* OblateSpheroid - Useful for representing the earth

## Usage
Simple copy the *include* directory to your project.
Then *#include* the desired header files.

## Examples

### Construct a Matrix
Method 1: Explicit
```
Math::Matrix matrix(2, 2);
matrix1(0,0) = 1;
matrix1(0,1) = 2;
matrix1(1,0) = 3;
matrix1(1,1) = 4;
```

Method2: With initalizer list
```
Math::Matrix matrix({{1, 2}, {3, 4});
```

Method 3: With initalizer list + assignment
```
Math::Matrix matrix = {{1, 2}, {3, 4}};
```


### Implicit conversion
```
Math::Matrix matrix(4, 1);
matrix(0,0) = 1;
matrix(1,0) = 2;
matrix(2,0) = 3;

Math::Vector3 vector = matrix;
```

### Exception handling
A std::out_of_bounds exception can be thrown in many situations.
```
Math::Matrix matrix = {
  {3  , 3.2, 3},
  {3.5, 3.6, 3}
};

try {
  double val = matrix(1, 3);
}
catch(std::out_of_range e)
{
  // Column range is 0 - 2 (3 is out of bounds)
}

try {
  Matrix inv = matrix.inverse();
}
catch(std::out_of_range e)
{
  // Matrix has no inverse
}
```

### Transform a point
TODO

### Intersect a line with a sphere
TODO

This example also works with the other geometry types (plane, spheroid, etc.)

### Project a point onto a sphere
TODO

This example also works with the other geometry types (plane, spheroid, etc.)

### Solve Systems of Equations
Given the following system of equations:
```
x + y + z = 6
2y + 5z = −4
2x + 5y − z = 27
```
Calculate x, y and z
```
/// Create matrix of coefficients
Math::Matrix A =
{ {1, 1,  1},
  {0, 2,  5},
  {2, 5, -1} };

/// Create vector with right-side values
Math::Vector B = { 6, -4, 27 };

/// Calculate x, y and z
// AX = B     =>    X = inv(A) * B
Math::Vector X = A.inverse() * B;

// x = X(0) = 5
// y = X(1) = 3
// z = X(1) = -2
```

Example from: https://www.mathsisfun.com/algebra/systems-linear-equations-matrices.html

### Least Squares
Suppose we have 5 points given by X and Y coordinates:
```(2, 20), (6, 18), (20, 10), (30, 6), (40, 2)```
and want to fit a line through these points.

```Line equation: y = ax + b```

We compute the slope (a) and y-intercept (b) as follows:
```
// Create matrix with coefficients of line equation
Math::Matrix A =
{ {2,  1},
  {6,  1},
  {20, 1},
  {30, 1},
  {40, 1} };

Math::Vector b = { 20, 18, 10, 6, 2 };

// Compute x
Math::Vector x = (A.transposed() * A).inverse() * A.transposed() * b;

double slope = x(0);       // -0.48
double yIntercept = x(1);  // 20.6
```

Example from: https://ltcconline.net/greenl/courses/203/MatrixOnVectors/leastSquares.htm

## License
This library is licensed under the GNU General Public License 3.0 - see the [LICENSE.md](LICENSE.md) file for details.
