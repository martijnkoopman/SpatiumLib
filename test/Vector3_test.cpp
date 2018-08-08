#include <QtTest>

// add necessary includes here

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

}

void Vector3_test::test_angle()
{

}

void Vector3_test::test_dot()
{

}

void Vector3_test::test_cross()
{

}

QTEST_APPLESS_MAIN(Vector3_test)

#include "Vector3_test.moc"
