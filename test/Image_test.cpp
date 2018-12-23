#include <QtTest>

#include <SpatiumLib/Imaging/Image.h>

class Image_test : public QObject
{
  Q_OBJECT

public:
  Image_test();
  ~Image_test();

private slots:

  // Constructors
  void test_constructorEmpty();
  void test_constructorStack();

  // Operators
  void test_compareEqual();
  void test_compareUnequal();

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
  Imaging::Image img(640, 480, Imaging::Image::Format_RGB24);

  QCOMPARE(img.width(), 640);
  QCOMPARE(img.height(), 480);
  QCOMPARE(img.format(), Imaging::Image::Format_RGB24);
}

void Image_test::test_constructorStack()
{
  int width = 640;
  int height = 480;

  //Imaging::Image<unsigned char, 3, width, height> *img = new Imaging::Image<unsigned char, 3, 640, 480>();

}

void Image_test::test_compareEqual()
{
  Imaging::Image img1(640, 480, Imaging::Image::Format_RGB24);
  Imaging::Image img2(640, 480, Imaging::Image::Format_RGB24);

  img1.clear();
  img2.clear();

  QVERIFY(img1 != img2);
}

void Image_test::test_compareUnequal()
{
  Imaging::Image img1(640, 480, Imaging::Image::Format_RGB24);
  Imaging::Image img2(640, 480, Imaging::Image::Format_RGBA32); // Different PixelFormat
  Imaging::Image img3(555, 480, Imaging::Image::Format_RGB24); // Different width
  Imaging::Image img4(640, 333, Imaging::Image::Format_RGB24); // Different height

  img1.clear();
  img2.clear();
  img3.clear();
  img4.clear();

  QVERIFY(img1 != img2);
  QVERIFY(img1 != img3);
  QVERIFY(img1 != img4);


}

QTEST_APPLESS_MAIN(Image_test)

#include "Image_test.moc"
