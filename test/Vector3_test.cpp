#include <QtTest>

#include <spatium/geom3d/Vector3.h>

using namespace spatium;

class Vector3_test : public QObject
{
  Q_OBJECT

public:
  Vector3_test();
  ~Vector3_test();

private slots:
  void test_normalize();
  void test_angle();
  void test_dot();
  void test_cross();
};

Vector3_test::Vector3_test()
{

}

Vector3_test::~Vector3_test()
{

}

void Vector3_test::test_normalize()
{
  /// \todo Unit test: normalize vector
}

void Vector3_test::test_angle()
{
  /// \todo Unit test: angle between vectors
}

void Vector3_test::test_dot()
{
  geom3d::Vector3 v1(1,0,0);
  geom3d::Vector3 v2(0,1,0); // perpendicular
  geom3d::Vector3 v3(1,0,0); // parallel

  QCOMPARE(v1.dot(v2), 0);
  QCOMPARE(v1.dot(v3), 1);
}

void Vector3_test::test_cross()
{
  /// \todo Unit test: cross product
}

QTEST_APPLESS_MAIN(Vector3_test)

#include "Vector3_test.moc"
