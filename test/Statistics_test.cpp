#include <QtTest>

#include <SpatiumLib/Math/Statistics.h>

class Statistics_test : public QObject
{
  Q_OBJECT

public:
  Statistics_test();
  ~Statistics_test();

private slots:

  void test_mean();
  void test_variance();
  void test_covariance();
  void test_stdDev();

private:
};

Statistics_test::Statistics_test()
{

}

Statistics_test::~Statistics_test()
{

}

// Constructors

void Statistics_test::test_mean()
{

  QCOMPARE(1, 1);
}

void Statistics_test::test_variance()
{
  QCOMPARE(1, 1);
}

void Statistics_test::test_covariance()
{
  QCOMPARE(1, 1);
}

void Statistics_test::test_stdDev()
{
  QCOMPARE(1, 1);
}

QTEST_APPLESS_MAIN(Statistics_test)

#include "Statistics_test.moc"
