#include <QtTest>
#include "ImageIOQt.h"

#include <spatium/Image.h>
#include <spatium/imgproc/GlobalThresholdFilter.h>

using namespace spatium;

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
  // Read ground truth image for verification
  Image<unsigned char, 1> groundtruth;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/threshold.png", groundtruth));

  // Read input image from file
  Image<unsigned char, 1> input;
  ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.png", input);

  imgproc::GlobalThresholdFilter<unsigned char> filter(127);

  // Apply in another image
  Image<unsigned char, 1> output(input.width(), input.height());
  QVERIFY(filter.apply(input, output));

  // Verify output image
  //QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/threshold.png", output));
  QVERIFY(output == groundtruth);

  // Apply in input image
  QVERIFY(filter.apply(input));

  // Verify output image
  //QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/threshold.png", input));
  QVERIFY(input == groundtruth);
}

QTEST_APPLESS_MAIN(GlobalThresholdFilter_test)

#include "GlobalThresholdFilter_test.moc"
