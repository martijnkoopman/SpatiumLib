#include <QtTest>

#include <spatium/Image.h>
#include <spatium/ImageIO.h>
#include <spatium/gfx2d/Drawing.h>

using namespace spatium;

class ImageIO_test : public QObject
{
  Q_OBJECT

public:
  ImageIO_test();
  ~ImageIO_test();

private slots:

  // Functions

  // Write to PNM (PBM, PGM, PPM)
  void test_writeBinaryToPbm();
  void test_writeGrayscaleToPgm();
  void test_writeRgbToPpm();

  // Write to PAM
  void test_writeBinaryToPam();
  void test_writeGrayscaleToPam();
  void test_writeGrayscaleAlphaToPam();
  void test_writeRgbToPam();
  void test_writeRgbaToPam();

private:
};

ImageIO_test::ImageIO_test()
{

}

ImageIO_test::~ImageIO_test()
{

}

// Write functions to PNM (PBM, PGM, PMM)

void ImageIO_test::test_writeBinaryToPbm()
{
  // TODO
}

void ImageIO_test::test_writeGrayscaleToPgm()
{
  Image<unsigned char, 1> image8(20, 15);
  gfx2d::Drawing::drawCircle(image8, {10,8}, 5, {128});
  QVERIFY(ImageIO::writeGrayscaleImageAsPgm(image8, "grayscale8bit.pgm"));

  Image<unsigned short, 1> image16(20, 15);
  gfx2d::Drawing::drawCircle(image16, {10,8}, 5, {32768});
  QVERIFY(ImageIO::writeGrayscaleImageAsPgm(image16, "grayscale16bit.pgm"));
}

void ImageIO_test::test_writeRgbToPpm()
{
  Image<unsigned char, 3> imageRgb(20, 15);
  gfx2d::Drawing::drawCircle(imageRgb, {10,8}, 5, {255, 128, 0});
  QVERIFY(ImageIO::writeRgbImageAsPpm(imageRgb, "rgb24bit.pgm"));
}

// Write functions to PAM

void ImageIO_test::test_writeBinaryToPam()
{
  // TODO
}

void ImageIO_test::test_writeGrayscaleToPam()
{
  // TODO
}

void ImageIO_test::test_writeGrayscaleAlphaToPam()
{
  // TODO
}

void ImageIO_test::test_writeRgbToPam()
{
  Image<unsigned char, 3> imageRgb(20, 15);
  gfx2d::Drawing::drawCircle(imageRgb, {10,8}, 5, {255, 128, 0});
  QVERIFY(ImageIO::writeRgbImageAsPam(imageRgb, "rgb24bit.pam"));
}

void ImageIO_test::test_writeRgbaToPam()
{
  Image<unsigned char, 4> imageRgba(20, 15);
  gfx2d::Drawing::drawCircle(imageRgba, {10,8}, 5, {255, 128, 0, 128});
  QVERIFY(ImageIO::writeRgbaImageAsPam(imageRgba, "rgba32bit.pam"));
}

// Read functions

// ...


QTEST_APPLESS_MAIN(ImageIO_test)

#include "ImageIO_test.moc"
