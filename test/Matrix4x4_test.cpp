#include <QtTest>
#include "TestUtilities.h"

#include <spatium/geom3d/Vector3.h>
#include <spatium/geom3d/Matrix4x4.h>

using namespace spatium;

class Matrix4x4_test : public QObject
{
  Q_OBJECT

public:
  Matrix4x4_test();
  ~Matrix4x4_test();

private slots:

  // Constructors
  void test_constructor();

  // Calculate
  void test_rotateX();
  void test_rotateY();
  void test_rotateZ();
  void test_rotateVector();
  void test_rotation();
};

Matrix4x4_test::Matrix4x4_test()
{

}

Matrix4x4_test::~Matrix4x4_test()
{

}

// Constructors

void Matrix4x4_test::test_constructor()
{
  geom3d::Matrix4x4 matrix;

  // Check identity matrix
  for (unsigned row = 0; row < 4; row++)
  {
    for (unsigned col = 0; col < 4; col++)
    {
      if (row == col) // Diagonal
      {
        QCOMPARE(matrix(row,col), 1);
      }
      else
      {
        QCOMPARE(matrix(row,col), 0);
      }
    }
  }
}

void Matrix4x4_test::test_rotateX()
{
  const double angle = 90 * Deg2Rad;
  geom3d::Matrix4x4 rotX = geom3d::Matrix4x4::rotationX(angle);
  QCOMPARE(rotX(1,1), cos(angle));
  QCOMPARE(rotX(1,2), -sin(angle));
  QCOMPARE(rotX(2,1), sin(angle));
  QCOMPARE(rotX(2,2), cos(angle));
}

void Matrix4x4_test::test_rotateY()
{
  const double angle = 90 * Deg2Rad;
  geom3d::Matrix4x4 rotY = geom3d::Matrix4x4::rotationY(angle);
  QCOMPARE(rotY(0,0), cos(angle));
  QCOMPARE(rotY(0,2), sin(angle));
  QCOMPARE(rotY(2,0), -sin(angle));
  QCOMPARE(rotY(2,2), cos(angle));
}

void Matrix4x4_test::test_rotateZ()
{
  const double angle = 90 * Deg2Rad;
  geom3d::Matrix4x4 rotZ = geom3d::Matrix4x4::rotationZ(angle);
  QCOMPARE(rotZ(0,0), cos(angle));
  QCOMPARE(rotZ(0,1), -sin(angle));
  QCOMPARE(rotZ(1,0), sin(angle));
  QCOMPARE(rotZ(1,1), cos(angle));

  // Compare by value
  QVERIFY(qFuzzyIsNull(rotZ(0,0)));
  QVERIFY(qFuzzyCompare(rotZ(0,1), -1));
  QVERIFY(qFuzzyCompare(rotZ(1,0), 1));
  QVERIFY(qFuzzyIsNull(rotZ(1,1)));
}

void Matrix4x4_test::test_rotateVector()
{
  const double angle = 90 * Deg2Rad;
  const geom3d::Matrix4x4 rotZ = geom3d::Matrix4x4::rotationZ(angle);
  const geom3d::Vector3 vec = {1, 0, 0};

  geom3d::Vector3 result = rotZ * vec;
  QVERIFY(qFuzzyIsNull(result(0))); // 0
  QVERIFY(qFuzzyCompare(result(1), 1)); // 1
  QVERIFY(qFuzzyIsNull(result(2))); // 0
}

void Matrix4x4_test::test_rotation()
{
  const double angleX = 45 * Deg2Rad;
  const double angleY = 90 * Deg2Rad;
  const double anglez = 135 * Deg2Rad;
  const geom3d::Matrix4x4 rot = geom3d::Matrix4x4::rotation(angleX, angleY, anglez);

  // Check: T * T' = I
  const geom3d::Matrix4x4 T = rot * rot.transposed();

  // Check for identity matrix
  QVERIFY(TestUtilities::fuzzyCompareMatrix(T, geom3d::Matrix4x4()));

  // Check: |T| = 1
  QCOMPARE(rot.determinant(), 1);

  geom3d::Matrix4x4 m1 = geom3d::Matrix4x4::rotationX(angleX);
  geom3d::Matrix4x4 m2 = geom3d::Matrix4x4::rotation(angleX, 0, 0);
  geom3d::Matrix4x4 m3 = geom3d::Matrix4x4::rotationAround({1, 0, 0}, angleX);

  QVERIFY(TestUtilities::fuzzyCompareMatrix(m1, m2));
  QVERIFY(TestUtilities::fuzzyCompareMatrix(m2, m3));
}

QTEST_APPLESS_MAIN(Matrix4x4_test)

#include "Matrix4x4_test.moc"
