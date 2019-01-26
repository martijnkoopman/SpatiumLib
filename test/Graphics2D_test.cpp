#include <QtTest>
#include "TestUtilities.h"

#include <SpatiumLib/Imaging/Image.h>
#include <SpatiumLib/Graphics2D/Drawing.h>

class Graphics2D_test : public QObject
{
  Q_OBJECT

public:
  Graphics2D_test();
  ~Graphics2D_test();

private slots:
  void test_drawLine();
  void test_drawCircle();
  void test_drawRectangle();

private:
};

Graphics2D_test::Graphics2D_test()
{

}

Graphics2D_test::~Graphics2D_test()
{

}

// Draw functions

void Graphics2D_test::test_drawLine()
{
  Imaging::Image<unsigned char, 3> image(30, 30);

  Graphics2D::Drawing::drawLine(image, {15, 5}, {15, 25}, {255, 0, 0}); // vertical red line
  Graphics2D::Drawing::drawLine(image, {5, 15}, {25, 15}, {255, 255, 255}); // horizontal white line
  Graphics2D::Drawing::drawLine(image, {5, 5}, {25, 25}, {0, 255, 0}); // diagonal green line
  Graphics2D::Drawing::drawLine(image, {5, 25}, {25, 5}, {0, 0, 255}); // diagonal blue line

  // Write as RGBA
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lines.png", image));

  // Compare output with input
  Imaging::Image<unsigned char, 3> groundtruth;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lines.png", groundtruth));
  QVERIFY(image == groundtruth);
}

void Graphics2D_test::test_drawCircle()
{
  Imaging::Image<unsigned char, 3> image(30, 30);

  Graphics2D::Drawing::drawCircle(image, {15, 15}, 10, {255, 0, 0});

  // Write as RGBA
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/circle.png", image));

  // Compare output with input
  Imaging::Image<unsigned char, 3> groundtruth;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/circle.png", groundtruth));
  QVERIFY(image == groundtruth);
}

void Graphics2D_test::test_drawRectangle()
{
  Imaging::Image<unsigned char, 3> image(30, 20);

  // Draw rectangle WITHOUT fill
  Graphics2D::Drawing::drawRectangle(image, {5, 5}, {25, 15}, {255, 0, 0});

  // Write to file
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/rectangle.png", image));

  // Compare output with input
  Imaging::Image<unsigned char, 3> groundtruth;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/rectangle.png", groundtruth));
  QVERIFY(image == groundtruth);

  // Draw rectangle WITH fill
  image.clear();
  Graphics2D::Drawing::drawRectangle(image, {5, 5}, {25, 15}, {255, 0, 0}, true);

  // Write to file
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/rectangle_fill.png", image));

  // Compare output with input
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/rectangle_fill.png", groundtruth));
  QVERIFY(image == groundtruth);
}

QTEST_APPLESS_MAIN(Graphics2D_test)

#include "Graphics2D_test.moc"
