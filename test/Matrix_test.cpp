#include <QtTest>

#include <SpatiumLib/Math/Math.h>
#include <SpatiumLib/Math/Matrix.h>
#include <SpatiumLib/Math/Vector.h>
#include <SpatiumLib/Math/Geometry/Vector3.h>
#include <SpatiumLib/Math/Geometry/Point3.h>
#include <SpatiumLib/Math/Geometry/GeoPoint3.h>

class Matrix_test : public QObject
{
  Q_OBJECT

public:
  Matrix_test();
  ~Matrix_test();

private slots:

  // Constructors
  void test_constructorRowsCols();
  void test_constructorInitializerList();
  void test_constructorInitializerListEmpty1();
  void test_constructorInitializerListEmpty2();
  void test_constructorInitializerListUnequal();
  void test_copyConstructorMatrix();
  void test_copyConstructorVector();
  void test_copyConstructorVector3();
  void test_copyConstructorPoint3();
  void test_copyConstructorGeoPoint3();

  // Operators
  void test_assignInitializerList();
  void test_assignVector();
  void test_assignPoint3();
  void test_compareEqual();
  void test_compareUnequal();
  void test_add();
  void test_subtract();
  void test_multiply();
  void test_multiplyScalar();
  void test_divideScalar();

  // Construct
  void test_constructIdentity();

  // Calculate
  void test_transposed();
  void test_determinant();
  void test_determinantNonSquare();
  void test_inverse();
  void test_inverseNonSquare();
  void test_inverseSingular();

  // Integration
  void test_solveSystemOfEquations();
  void test_leastSquares();
  void test_eigenDecomposition2d();

private:
  static bool approximatelyEqualDoubles(double d1, double d2);
};

Matrix_test::Matrix_test()
{

}

Matrix_test::~Matrix_test()
{

}

// Constructors

void Matrix_test::test_constructorRowsCols()
{
  Math::Matrix matrix(5, 3);

  QCOMPARE(matrix.rows(), 5);
  QCOMPARE(matrix.cols(), 3);
  QCOMPARE(matrix.data().size(), 5*3);
}

void Matrix_test::test_constructorInitializerList()
{
  Math::Matrix matrix(
    {{1,   2,  3},
     {4,   5,  6},
     {7,   8,  9},
     {10, 11, 12}});

  QCOMPARE(matrix.rows(), 4);
  QCOMPARE(matrix.cols(), 3);
  QCOMPARE(matrix.data().size(), 3*4);

  QCOMPARE(matrix(0,0), 1);
  QCOMPARE(matrix(0,1), 2);
  QCOMPARE(matrix(0,2), 3);
  QCOMPARE(matrix(1,0), 4);
  QCOMPARE(matrix(1,1), 5);
  QCOMPARE(matrix(1,2), 6);
  QCOMPARE(matrix(2,0), 7);
  QCOMPARE(matrix(2,1), 8);
  QCOMPARE(matrix(2,2), 9);
  QCOMPARE(matrix(3,0), 10);
  QCOMPARE(matrix(3,1), 11);
  QCOMPARE(matrix(3,2), 12);
}

void Matrix_test::test_constructorInitializerListEmpty1()
{
  Math::Matrix matrix({});

  QCOMPARE(matrix.rows(), 0);
  QCOMPARE(matrix.cols(), 0);
  QCOMPARE(matrix.data().size(), 0);
}

void Matrix_test::test_constructorInitializerListEmpty2()
{
  Math::Matrix matrix({{}});

  QCOMPARE(matrix.rows(), 0);
  QCOMPARE(matrix.cols(), 0);
  QCOMPARE(matrix.data().size(), 0);
}

void Matrix_test::test_constructorInitializerListUnequal()
{
  Math::Matrix matrix(
  {{1,  2},
   {3,  4, 5},
   {6}});

  QCOMPARE(matrix.rows(), 3);
  QCOMPARE(matrix.cols(), 2);
  QCOMPARE(matrix.data().size(), 2*3);
  QCOMPARE(matrix(0,0), 1);
  QCOMPARE(matrix(0,1), 2);
  QCOMPARE(matrix(1,0), 3);
  QCOMPARE(matrix(1,1), 4);
  QCOMPARE(matrix(2,0), 6);
  QCOMPARE(matrix(2,1), 0);
}

void Matrix_test::test_copyConstructorMatrix()
{
  Math::Matrix matrix1(3, 2);
  matrix1(0,0) = 9;
  matrix1(2,1) = 6;

  Math::Matrix matrix2(matrix1);
  QCOMPARE(matrix2.rows(), 3);
  QCOMPARE(matrix2.cols(), 2);
  QCOMPARE(matrix2(0,0), 9);
  QCOMPARE(matrix2(0,1), 0);
  QCOMPARE(matrix2(2,1), 6);
  QCOMPARE(matrix2(2,0), 0);
}

void Matrix_test::test_copyConstructorVector()
{
  Math::Vector vector(5);
  vector(0) = 1;
  vector(1) = 2;
  vector(4) = 5;
  Math::Matrix matrix(vector);

  QCOMPARE(matrix.rows(), 5);
  QCOMPARE(matrix.cols(), 1);
  QCOMPARE(matrix(0,0), 1);
  QCOMPARE(matrix(1,0), 2);
  QCOMPARE(matrix(2,0), 0);
  QCOMPARE(matrix(3,0), 0);
  QCOMPARE(matrix(4,0), 5);
}

void Matrix_test::test_copyConstructorVector3()
{
  Math::Geometry::Vector3 vector;
  vector.x(3);
  vector.y(2);
  vector.z(1);
  Math::Matrix matrix(vector);

  QCOMPARE(matrix.rows(), 4);
  QCOMPARE(matrix.cols(), 1);
  QCOMPARE(matrix(0,0), 3);
  QCOMPARE(matrix(1,0), 2);
  QCOMPARE(matrix(2,0), 1);
  QCOMPARE(matrix(3,0), 0); // 0 for vector
}

void Matrix_test::test_copyConstructorPoint3()
{
  Math::Geometry::Point3 point;
  point.x(3);
  point.y(2);
  point.z(1);
  Math::Matrix matrix(point);

  QCOMPARE(matrix.rows(), 4);
  QCOMPARE(matrix.cols(), 1);
  QCOMPARE(matrix(0,0), 3);
  QCOMPARE(matrix(1,0), 2);
  QCOMPARE(matrix(2,0), 1);
  QCOMPARE(matrix(3,0), 1); // 1 for point
}

void Matrix_test::test_copyConstructorGeoPoint3()
{
  Math::Geometry::GeoPoint3 geoPoint;
  geoPoint.longitude(3);
  geoPoint.latitude(2);
  geoPoint.elevation(1);
  Math::Matrix matrix(geoPoint);

  QCOMPARE(matrix.rows(), 4);
  QCOMPARE(matrix.cols(), 1);
  QCOMPARE(matrix(0,0), 3);
  QCOMPARE(matrix(1,0), 2);
  QCOMPARE(matrix(2,0), 1);
  QCOMPARE(matrix(3,0), 1); // 1 for point
}

// Operators

void Matrix_test::test_assignInitializerList()
{
  Math::Matrix matrix = { {1, 2, 3},
                          {4, 5, 6} };

  QCOMPARE(matrix.rows(), 2);
  QCOMPARE(matrix.cols(), 3);
  QCOMPARE(matrix(0,0), 1);
  QCOMPARE(matrix(1,2), 6);
}

void Matrix_test::test_assignVector()
{
  Math::Vector vector(5);
  vector(0) = 1;
  vector(1) = 2;
  vector(4) = 5;
  Math::Matrix matrix = vector;

  QCOMPARE(matrix.rows(), 5);
  QCOMPARE(matrix.cols(), 1);
  QCOMPARE(matrix(0,0), 1);
  QCOMPARE(matrix(1,0), 2);
  QCOMPARE(matrix(2,0), 0);
  QCOMPARE(matrix(3,0), 0);
  QCOMPARE(matrix(4,0), 5);
}

void Matrix_test::test_assignPoint3()
{
  Math::Geometry::Point3 point;
  point.x(3);
  point.y(2);
  point.z(1);
  Math::Matrix matrix = point;

  QCOMPARE(matrix.rows(), 4);
  QCOMPARE(matrix.cols(), 1);
  QCOMPARE(matrix(0,0), 3);
  QCOMPARE(matrix(1,0), 2);
  QCOMPARE(matrix(2,0), 1);
  QCOMPARE(matrix(3,0), 1); // 1 for point
}

void Matrix_test::test_compareEqual()
{

}

void Matrix_test::test_compareUnequal()
{

}

void Matrix_test::test_add()
{

}

void Matrix_test::test_subtract()
{

}

void Matrix_test::test_multiply()
{

}

void Matrix_test::test_multiplyScalar()
{

}

void Matrix_test::test_divideScalar()
{

}

// Construct

void Matrix_test::test_constructIdentity()
{
  Math::Matrix matrix = Math::Matrix::identity(3);

  QCOMPARE(matrix.rows(), 3);
  QCOMPARE(matrix.cols(), 3);
  QCOMPARE(matrix(0,0), 1);
  QCOMPARE(matrix(0,1), 0);
  QCOMPARE(matrix(0,2), 0);
  QCOMPARE(matrix(1,0), 0);
  QCOMPARE(matrix(1,1), 1);
  QCOMPARE(matrix(1,2), 0);
  QCOMPARE(matrix(2,0), 0);
  QCOMPARE(matrix(2,1), 0);
  QCOMPARE(matrix(2,2), 1);
}

// Calculate

void Matrix_test::test_transposed()
{
  Math::Matrix matrix1(3, 2);
  matrix1(0,0) = 1;
  matrix1(2,1) = 6;

  Math::Matrix matrix2 = matrix1.transposed();

  QCOMPARE(matrix2.rows(), 2);
  QCOMPARE(matrix2.cols(), 3);
  QCOMPARE(matrix2(0,0), 1);
  QCOMPARE(matrix2(1,2), 6);
}

void Matrix_test::test_determinant()
{
  Math::Matrix matrix = {
    {6,  1, 1},
    {4, -2, 5},
    {2,  8, 7}
  };

  double det = matrix.determinant();

  QCOMPARE(det, -306);
}

void Matrix_test::test_determinantNonSquare()
{
  Math::Matrix matrix = {
    {6,  1, 1},
    {4, -2, 5}
  };

  QVERIFY_EXCEPTION_THROWN(matrix.determinant(), std::out_of_range);
}

void Matrix_test::test_inverse()
{
  Math::Matrix matrix1 = {
    {3  , 3.2},
    {3.5, 3.6}
  };

  Math::Matrix matrix2 = matrix1.inverse();

  QCOMPARE(matrix2.rows(), 2);
  QCOMPARE(matrix2.cols(), 2);
  //QCOMPARE(matrix2(0,0), -9);
  //QCOMPARE(matrix2(0,1),  8);
  //QCOMPARE(matrix2(1,0),  8.75);
  //QCOMPARE(matrix2(1,1), -7.5);
  QVERIFY(Matrix_test::approximatelyEqualDoubles(matrix2(0,0), -9));
  QVERIFY(Matrix_test::approximatelyEqualDoubles(matrix2(0,1),  8));
  QVERIFY(Matrix_test::approximatelyEqualDoubles(matrix2(1,0),  8.75));
  QVERIFY(Matrix_test::approximatelyEqualDoubles(matrix2(1,1), -7.5));
}

void Matrix_test::test_inverseNonSquare()
{
  Math::Matrix matrix = {
    {3  , 3.2, 3},
    {3.5, 3.6, 3}
  };

  QVERIFY_EXCEPTION_THROWN(matrix.inverse(), std::out_of_range);
}

void Matrix_test::test_inverseSingular()
{
  Math::Matrix matrix = {
    {3, 4},
    {6, 8}
  };

  QVERIFY_EXCEPTION_THROWN(matrix.inverse(), std::out_of_range);
}

void Matrix_test::test_solveSystemOfEquations()
{
  Math::Matrix A =
  {
    {1, 1,  1},
    {0, 2,  5},
    {2, 5, -1}
  };

  Math::Vector b = { 6, -4, 27 };

  Math::Vector x = A.inverse() * b;

  // X = x(0) = 5
  // Y = x(1) = 3
  // Z = x(1) = -2
  QCOMPARE(x(0), 6);
  QCOMPARE(x(1), -4);
  QCOMPARE(x(2), 27);
}

void Matrix_test::test_leastSquares()
{
  // Least squares
  // Suppose we have 5 points given by X and Y coordinates (2, 20), (6, 18), (20, 10), (30, 6), (40, 2) and want to fit a line through these points.
  // Line equation: y = ax + b
  // Compute a (slope) and b (y-intercept)

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
  // Slope = x(0)
  // Y-intercept = x(1)

  // Compute residuals (error vector)
  //Math::Vector e = b - (A * x);

  QCOMPARE(x(0), -0.480376766091052); // Double compare?
  QCOMPARE(x(1), 20.61538461538461);  // Double compare?
}


void Matrix_test::test_eigenDecomposition2d()
{
  // Test 1
  Math::Matrix A = {{7,  3},
                    {3, -1}};

  double eig1, eig2;
  QVERIFY(eigenvalues2d(A, eig1, eig2));

  QCOMPARE(eig1, -2);
  QCOMPARE(eig2, 8);

  // Test 2
  A = {{ 0,  1},
       {-2, -3}};

  QVERIFY(eigenvalues2d(A, eig1, eig2));

  QCOMPARE(eig1, -2);
  QCOMPARE(eig2, -1);
}

bool Matrix_test::approximatelyEqualDoubles(double d1, double d2)
{
  return (std::abs(d1-d2) <= std::numeric_limits<double>::epsilon() * std::abs(d1+d2) * 2
          || std::abs(d1-d2) < std::numeric_limits<double>::min());
}

QTEST_APPLESS_MAIN(Matrix_test)

#include "Matrix_test.moc"
