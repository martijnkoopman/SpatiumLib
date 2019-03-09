#include <QtTest>
#include "TestUtilities.h"

#include <spatium/Image.h>

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
  void test_moveConstructor();
  void test_moveAssignment();

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
  Image<unsigned char, 3> img;

  QCOMPARE(img.width(), 1);
  QCOMPARE(img.height(), 1);
  QVERIFY(img.imageDataPtr() != nullptr);
}

void Image_test::test_constructor()
{
  Image<unsigned char, 3> img(640, 480);

  QCOMPARE(img.width(), 640);
  QCOMPARE(img.height(), 480);
}

void Image_test::test_constructorStack()
{
  Image<unsigned char, 3> *img = new Image<unsigned char, 3>(640, 480);

  QCOMPARE(img->width(), 640);
  QCOMPARE(img->height(), 480);
}

void Image_test::test_copyConstructor()
{
  Image<unsigned char, 3> img1(640, 480);
  img1.pixel(10, 20) = {255, 0, 255};
  img1.pixel(200, 300) = {0, 255, 255};
  img1.pixel(400, 200) = {127, 0, 255};
  img1.pixel(620, 440) = {0, 127, 127};

  // Implicit copy
  Image<unsigned char, 3> img2 = img1;
  QVERIFY(img1 == img2);

  // Explicit copy
  Image<unsigned char, 3> img3(img1);
  QVERIFY(img1 == img3);
}

void Image_test::test_copyAssignment()
{
  Image<unsigned char, 3> img1(640, 480);
  img1.pixel(10, 20) = {255, 0, 255};
  img1.pixel(200, 300) = {0, 255, 255};
  img1.pixel(400, 200) = {127, 0, 255};
  img1.pixel(620, 440) = {0, 127, 127};

  Image<unsigned char, 3> img2(640, 480);

  // Copy assignment
  img2 = img1;

  QVERIFY(img1 == img2);
}

void Image_test::test_moveConstructor()
{
  const int width = 640;
  const int height = 480;

  // Move constructor
  auto createImage = [=](int width, int height) -> Image<>
  {
    // Lambda to return an Image (rvalue)
    return Image<>(width, height);
  };

  ///\TODO Should work without std::move
  Image<> img1 = std::move(createImage(640, 480));
  QCOMPARE(img1.width(), width);
  QCOMPARE(img1.height(), height);

  // Move assignment
  //Image<unsigned char, 3> img2 = std::move(createImage(width, height));
}

void Image_test::test_moveAssignment()
{
  const int width = 640;
  const int height = 480;

  Image<unsigned char, 3> img1(width, height);
  Image<unsigned char, 3> img2;
  img2 = std::move(img1);

  QCOMPARE(img1.width(), 1);
  QCOMPARE(img1.height(), 1);
  QCOMPARE(img2.width(), width);
  QCOMPARE(img2.height(), height);
}

void Image_test::test_compareEqual()
{
  Image<unsigned char, 3> img1(640, 480);
  Image<unsigned char, 3> img2(640, 480);
  QVERIFY(img1 == img2);
}

void Image_test::test_compareUnequal()
{
  Image<unsigned char, 3> img1(640, 480);
  Image<unsigned char, 3> img2(555, 480); // Different width
  Image<unsigned char, 3> img3(640, 333); // Different height
  Image<unsigned char, 3> img4(640, 480); // Different values
  img4.pixel(10, 20) = {255, 0, 255};

  QVERIFY(img1 != img2);
  QVERIFY(img1 != img3);
  QVERIFY(img1 != img4);
}

void Image_test::test_getSetPixel()
{
  Image<unsigned char, 3> img(640, 480);

  // Set pixel value
  std::array<unsigned char, 3> val1 = {127, 191, 255};
  img.pixel(10, 20) = val1;

  // Get pixel value
  std::array<unsigned char, 3> val2 = img.pixel(10, 20);

  // Compare equal
  QVERIFY(val1 == val2);

  // Get another pixel value (zero)
  val2 = img.pixel(11, 21);

  // Compare unequal
  QVERIFY(val1 != val2);

  /// \TODO: Test with out of bounds
}

void Image_test::test_clear()
{
  Image<unsigned char, 1> img(20, 10);

  // Set all values to 255
  std::array<unsigned char, 1> val = {255};
  for(int y = 0; y < img.height(); y++)
  {
    for(int x = 0; x < img.height(); x++)
    {
      img.imageDataPtr()[y * img.width() + x] = val;
    }
  }

  // Clear all values
  img.clear();

  // Compare all values set to zero
  std::array<unsigned char, 1> zero = {0};
  for(int y = 0; y < img.height(); y++)
  {
    for(int x = 0; x < img.height(); x++)
    {
      QCOMPARE(img.imageDataPtr()[y * img.width() + x], zero);
    }
  }
}

QTEST_APPLESS_MAIN(Image_test)

#include "Image_test.moc"
