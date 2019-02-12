#include <QtTest>
#include "TestUtilities.h"

#include <spatium/imgproc/Image.h>

class Image_test : public QObject
{
  Q_OBJECT

public:
  Image_test();
  ~Image_test();

private slots:

  // Constructors
  void test_constructorEmpty();
  void test_constructor();
  void test_constructorStack();
  void test_copyConstructor();
  void test_copyAssignment();

  // Operators
  void test_compareEqual();
  void test_compareUnequal();

  void test_getSetPixel();
  void test_clear();

private:
};

Image_test::Image_test()
{

}

Image_test::~Image_test()
{

}

// Constructors

void Image_test::test_constructorEmpty()
{
  imgproc::Image<unsigned char, 3> img;

  QCOMPARE(img.width(), 0);
  QCOMPARE(img.height(), 0);
  QCOMPARE(img.imageDataPtr(), nullptr);
}

void Image_test::test_constructor()
{
  imgproc::Image<unsigned char, 3> img(640, 480);

  QCOMPARE(img.width(), 640);
  QCOMPARE(img.height(), 480);
}

void Image_test::test_constructorStack()
{
  imgproc::Image<unsigned char, 3> *img = new imgproc::Image<unsigned char, 3>(640, 480);

  QCOMPARE(img->width(), 640);
  QCOMPARE(img->height(), 480);
}

void Image_test::test_copyConstructor()
{
  imgproc::Image<unsigned char, 3> img1(640, 480);
  img1.setPixel(10, 20, {255, 0, 255});
  img1.setPixel(200, 300, {0, 255, 255});
  img1.setPixel(400, 200, {127, 0, 255});
  img1.setPixel(620, 440, {0, 127, 127});

  // Copy constructor
  //imgproc::Image<unsigned char, 3> img2 = img1; // implicit
  imgproc::Image<unsigned char, 3> img2(img1); // explicit

  QVERIFY(img1 == img2);
}

void Image_test::test_copyAssignment()
{
  imgproc::Image<unsigned char, 3> img1(640, 480);
  img1.setPixel(10, 20, {255, 0, 255});
  img1.setPixel(200, 300, {0, 255, 255});
  img1.setPixel(400, 200, {127, 0, 255});
  img1.setPixel(620, 440, {0, 127, 127});

  imgproc::Image<unsigned char, 3> img2(640, 480);

  // Copy assignment
  img2 = img1;

  QVERIFY(img1 == img2);
}


void Image_test::test_compareEqual()
{
  imgproc::Image<unsigned char, 3> img1(640, 480);
  imgproc::Image<unsigned char, 3> img2(640, 480);
  QVERIFY(img1 == img2);
}

void Image_test::test_compareUnequal()
{
  imgproc::Image<unsigned char, 3> img1(640, 480);
  imgproc::Image<unsigned char, 3> img2(555, 480); // Different width
  imgproc::Image<unsigned char, 3> img3(640, 333); // Different height
  imgproc::Image<unsigned char, 3> img4(640, 480); // Different values
  img4.setPixel(10, 20, {255, 0, 255});

  QVERIFY(img1 != img2);
  QVERIFY(img1 != img3);
  QVERIFY(img1 != img4);
}

void Image_test::test_getSetPixel()
{
  imgproc::Image<unsigned char, 3> img(640, 480);

  // Set pixel value
  std::array<unsigned char, 3> val1 = {127, 191, 255};
  img.setPixel(10, 20, val1);

  // Get pixel value
  std::array<unsigned char, 3> val2 = img.getPixel(10, 20);

  // Compare equal
  QVERIFY(val1 == val2);

  // Get another pixel value (zero)
  val2 = img.getPixel(11, 21);

  // Compare unequal
  QVERIFY(val1 != val2);
}

void Image_test::test_clear()
{
  imgproc::Image<unsigned char, 1> img(20, 10);

  // Set all values to 255
  for(int y = 0; y < img.height(); y++)
  {
    for(int x = 0; x < img.height(); x++)
    {
      img.imageDataPtr()[y * img.width() + x] = 255;
    }
  }

  // Clear all values
  img.clear();

  // Compare all values set to zero
  for(int y = 0; y < img.height(); y++)
  {
    for(int x = 0; x < img.height(); x++)
    {
      QCOMPARE(img.imageDataPtr()[y * img.width() + x], 0);
    }
  }
}

QTEST_APPLESS_MAIN(Image_test)

#include "Image_test.moc"
