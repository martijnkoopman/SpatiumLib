#include <QtTest>
#include "ImageIOQt.h"

#include <spatium/Image.h>

using namespace spatium;

class ImageIOQt_test : public QObject
{
  Q_OBJECT

public:
  ImageIOQt_test();
  ~ImageIOQt_test();

private slots:

  // Constructors
  void test_readGrayscaleToGrayscale();
  void test_readGrayscaleToRgb();
  void test_readGrayscaleToRgba();

  void test_readRgbToGrayscale();
  void test_readRgbToRgb();
  void test_readRgbToRgba();

  void test_readRgbaToGrayscale();
  void test_readRgbaToRgb();
  void test_readRgbaToRgba();

//  void test_writeGrayscale();
//  void test_writeRgb();
//  void test_writeRgba();

private:
};

ImageIOQt_test::ImageIOQt_test()
{

}

ImageIOQt_test::~ImageIOQt_test()
{

}

// Read functions

void ImageIOQt_test::test_readGrayscaleToGrayscale()
{
  // Read grayscale image
  Image<unsigned char, 1> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_gray.png", input));

  // Write as grayscale
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray2gray.png", input));

  // Compare output with input
  Image<unsigned char, 1> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray2gray.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readGrayscaleToRgb()
{
  // Read grayscale image
  Image<unsigned char, 3> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_gray.png", input));

  // Write as RGB
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray2rgb.png", input));

  // Compare output with input
  Image<unsigned char, 3> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray2rgb.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readGrayscaleToRgba()
{
  // Read grayscale image
  Image<unsigned char, 4> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_gray.png", input));

  // Write as RGBA
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray2rgba.png", input));

  // Compare output with input
  Image<unsigned char, 4> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_gray2rgba.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readRgbToGrayscale()
{
  // Read RGB image as grayscale image
  Image<unsigned char, 1> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.png", input));

  // Write as grayscale
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgb2gray.png", input));

  // Compare output with input
  Image<unsigned char, 1> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgb2gray.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readRgbToRgb()
{
  // Read RGB image
  Image<unsigned char, 3> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.png", input));

  // Write as RGB
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgb2rgb.png", input));

  // Compare output with input
  Image<unsigned char, 3> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgb2rgb.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readRgbToRgba()
{
  // Read RGB image
  Image<unsigned char, 4> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgb.png", input));

  // Write as RGBA
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgb2rgba.png", input));

  // Compare output with input
  Image<unsigned char, 4> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgb2rgba.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readRgbaToGrayscale()
{
  // Read RGBA image
  Image<unsigned char, 1> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgba.png", input));

  // Write as grayscale
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgba2gray.png", input));

  // Compare output with input
  Image<unsigned char, 1> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgba2gray.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readRgbaToRgb()
{
  // Read RGBA image
  Image<unsigned char, 3> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgba.png", input));

  // Write as RGB
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgba2rgb.png", input));

  // Compare output with input
  Image<unsigned char, 3> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgba2rgb.png", output));
  QVERIFY(input == output);
}

void ImageIOQt_test::test_readRgbaToRgba()
{
  // Read RGBA image
  Image<unsigned char, 4> input;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lenna_rgba.png", input));

  // Write as RGBA
  QVERIFY(ImageIOQt::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgba2rgba.png", input));

  // Compare output with input
  Image<unsigned char, 4> output;
  QVERIFY(ImageIOQt::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lenna_rgba2rgba.png", output));
  QVERIFY(input == output);
}

QTEST_APPLESS_MAIN(ImageIOQt_test)

#include "ImageIOQt_test.moc"
