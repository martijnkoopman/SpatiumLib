#include <QtTest>
#include "TestUtilities.h"

#include <SpatiumLib/Imaging/GlobalThresholdFilter.h>

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
  Imaging::Image<unsigned char, 3> image;
  TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna.png", image);
//QVERIFY(

  //Imaging::GlobalThresholdFilter<unsigned char> filter(170, 255);
  //Imaging::Image<unsigned char, 1> result(image.width(), image.height());
  //QVERIFY(filter.apply(image, result));

  // Save output image
  //QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna2.png", image));
}


QTEST_APPLESS_MAIN(GlobalThresholdFilter_test)

#include "GlobalThresholdFilter_test.moc"
