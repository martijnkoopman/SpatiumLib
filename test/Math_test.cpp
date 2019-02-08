#include <QtTest>

#include <SpatiumLib/Math/Math.h>

class Math_test : public QObject
{
  Q_OBJECT

public:
  Math_test();
  ~Math_test();

private slots:

  void test_solveQuadratic();
  void test_solveCubic();

private:
};

Math_test::Math_test()
{

}

Math_test::~Math_test()
{

}

// Tests

void Math_test::test_solveQuadratic()
{
  // Solve: x^2 - 3x + 4 = 0 (has NO solutions)
  double x1 = 0, x2 = 0;
  QCOMPARE(Math::solveQuadratic(1, -3, 4, x1, x2), 0);

  // Solve: -4x^2 + 12x - 9 = 0 (has ONE solution)
  x1 = 0; x2 = 0;
  QCOMPARE(Math::solveQuadratic(-4, 12, -9, x1, x2), 1);
  QCOMPARE(x1, 1.5);
  QCOMPARE(x2, 1.5);

  // Solve: 2x^2 - 11x + 5 = 0 (has TWO solutions)
  x1 = 0; x2 = 0;
  QCOMPARE(Math::solveQuadratic(2, -11, 5, x1, x2), 2);
  QCOMPARE(x1, 0.5);
  QCOMPARE(x2, 5);
}

void Math_test::test_solveCubic()
{
  // Solve: x^3 - sqrt(3)x^2 - 2x - 2sqrt(3) = 0 (Has three solutions)
  double x1 = 0, x2 = 0, x3 = 0;
  QCOMPARE(Math::solveCubic(1, -sqrt(3), -2, 2*sqrt(3), x1, x2, x3), 3);
  QVERIFY(qFuzzyCompare(x1, -1.414213562373095));
  QVERIFY(qFuzzyCompare(x2, 1.4142135623730931));
  QVERIFY(qFuzzyCompare(x3, 1.7320508075688776));

  // Solve: x^3 - 4x^2 + 5x - 2 = 0 (Has two solutions)
  x1 = 0; x2 = 0; x3 = 0;
  QCOMPARE(Math::solveCubic(1, -4, 5, -2, x1, x2, x3), 2);
  QVERIFY(qFuzzyCompare(x1, 1));
  QVERIFY(qFuzzyCompare(x2, 2));
  QVERIFY(qFuzzyCompare(x3, 2)); // Same as x2

  // Solve: x^3 + x - 2 = 0 (Has one solution)
  x1 = 0; x2 = 0; x3 = 0;
  QCOMPARE(Math::solveCubic(1, 0, 1, -2, x1, x2, x3), 1);
  QVERIFY(qFuzzyCompare(x1, 1));
  QVERIFY(qFuzzyCompare(x2, 1)); // Same as x1
  QVERIFY(qFuzzyCompare(x3, 1)); // Same as x1

  // Solve: 2x^3 + 10x^2 - 2x - 4 = 0 (has THREE solutions)
  x1 = 0; x2 = 0; x3 = 0;
  QCOMPARE(Math::solveCubic(2, 10, -2, -4, x1, x2, x3), 3);
  QVERIFY(qFuzzyCompare(x1, -5.119026675525919));
  QVERIFY(qFuzzyCompare(x2, -0.5683728862102564));
  QVERIFY(qFuzzyCompare(x3, 0.6873995617361734));

  // Solve: x^3 - 0.4x^2 + 0.05x - 0.002 = 0 (has TWO solutions)
  x1 = 0; x2 = 0; x3 = 0;
  QCOMPARE(Math::solveCubic(1, -0.4, 0.05, -0.002, x1, x2, x3), 2);
  QCOMPARE(x1, 0.1);
  QCOMPARE(x2, 0.2);
  QCOMPARE(x3, 0.2); // Same as x2

  // Solve: x^3 + 0.7x^2 + 2.7x - 0.9 = 0 (has ONE solution)
  x1 = 0; x2 = 0; x3 = 0;
  QCOMPARE(Math::solveCubic(1, 0.7, 2.7, -0.9, x1, x2, x3), 1);
  QCOMPARE(x1, 0.3);
  QCOMPARE(x2, 0.3); // Same as x1
  QCOMPARE(x3, 0.3); // Same as x1
}

QTEST_APPLESS_MAIN(Math_test)

#include "Math_test.moc"
