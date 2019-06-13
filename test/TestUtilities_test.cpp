#include <QtTest>
#include "TestUtilities.h"

class TestUtilities_test : public QObject
{
  Q_OBJECT

public:
  TestUtilities_test();
  ~TestUtilities_test();

private slots:
  void test_fuzzyCompareMatrix();
};

TestUtilities_test::TestUtilities_test()
{

}

TestUtilities_test::~TestUtilities_test()
{

}

// Read functions

void TestUtilities_test::test_fuzzyCompareMatrix()
{
  /// \todo Unit test: Fuzzy matrix compare
}

QTEST_APPLESS_MAIN(TestUtilities_test)

#include "TestUtilities_test.moc"
