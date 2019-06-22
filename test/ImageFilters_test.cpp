#include <QtTest>
#include "ImageIOQt.h"

#include <spatium/Image.h>
#include <spatium/ImageIO.h>
#include <spatium/imgproc/GlobalThreshold.h>
#include <spatium/imgproc/Grayscale.h>
#include <spatium/imgproc/Blur.h>
#include <spatium/imgproc/Sobel.h>

using namespace spatium;

class ImageFilters_test : public QObject
{
  Q_OBJECT

public:
  ImageFilters_test();
  ~ImageFilters_test();

private slots:

  // Constructors
  void test_globalThreshold();
  void test_grayscale();
  void test_blur();
  void test_sobel();
  //void test_prewit();

private:
};

ImageFilters_test::ImageFilters_test()
{

}

ImageFilters_test::~ImageFilters_test()
{

}

// Constructors

void ImageFilters_test::test_globalThreshold()
{
  // Read ground truth image for verification
  Image<unsigned char, 1> groundtruth;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/threshold.png", groundtruth));

  // Read input image from file
  Image<unsigned char, 1> input;
  ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.png", input);

  imgproc::GlobalThreshold<unsigned char> filter(127);

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

void ImageFilters_test::test_grayscale()
{
  // Read input image
  Image<unsigned char, 3> imageRgb;
  QVERIFY(ImageIO::readRgbImageFromPpm((QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.ppm").toStdString(), imageRgb));

  // Apply grayscale filter
  Image<unsigned char, 1> imageGray(imageRgb.width(), imageRgb.height());
  imgproc::Grayscale<> grayscale;
  grayscale.apply(imageRgb, imageGray);

  // Write output image
  QVERIFY(ImageIO::writeGrayscaleImageAsPgm(imageGray, (QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray.pgm").toStdString()));
}

void ImageFilters_test::test_blur()
{
  // Read input image
  Image<unsigned char, 3> imageRgb;
  QVERIFY(ImageIO::readRgbImageFromPpm((QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.ppm").toStdString(), imageRgb));

  // Apply blur filter
  Image<unsigned char, 3> imageBlur(imageRgb.width(), imageRgb.height());
  imgproc::Blur blur;
  blur.apply(imageRgb, imageBlur);

  // Write output image
  QVERIFY(ImageIO::writeRgbImageAsPpm(imageBlur, (QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_blur.ppm").toStdString()));
}

void ImageFilters_test::test_sobel()
{
  // Read input image
  Image<unsigned char, 1> imageGray;
  QVERIFY(ImageIO::readGrayscaleImageFromPgm((QFileInfo(__FILE__).absolutePath() + "/resources/lenna_gray.pgm").toStdString(), imageGray));
}

QTEST_APPLESS_MAIN(ImageFilters_test)

#include "ImageFilters_test.moc"
