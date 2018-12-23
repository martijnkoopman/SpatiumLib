#include <QtTest>
#include "TestUtilities.h"

#include <SpatiumLib/Imaging/GlobalThresholdFilter.h>

#include <iostream>

class GlobalThresholdFilter_test : public QObject
{
  Q_OBJECT

public:
  GlobalThresholdFilter_test();
  ~GlobalThresholdFilter_test();

private slots:

  // Constructors
  void test_apply();

private:
};

GlobalThresholdFilter_test::GlobalThresholdFilter_test()
{

}

GlobalThresholdFilter_test::~GlobalThresholdFilter_test()
{

}

// Constructors

void GlobalThresholdFilter_test::test_apply()
{
  // Read image from file
  Imaging::Image image;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna.png", image));

  Imaging::GlobalThresholdFilter filter(170, false);
  //Imaging::Image result(image.width(), image.height(), filter.outputFormat());
  QVERIFY(filter.apply(image));

  // Save output image
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna2.png", image));
}

QTEST_APPLESS_MAIN(GlobalThresholdFilter_test)

#include "GlobalThresholdFilter_test.moc"
