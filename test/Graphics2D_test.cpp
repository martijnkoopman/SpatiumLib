#include <QtTest>
#include "TestUtilities.h"

#include <spatium/imgproc/Image.h>
#include <spatium/gfx2d/Drawing.h>
#include <spatium/gfx2d/BezierCurve.h>

#include <iostream> // DELETE MEE

using namespace spatium;

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

  void test_drawLinearCurve();
  void test_drawQuadraticCurve();
  void test_drawCubicCurve();

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
  imgproc::Image<unsigned char, 3> image(30, 30);

  gfx2d::Drawing::drawLine(image, {15, 5}, {15, 25}, {255, 0, 0}); // vertical red line
  gfx2d::Drawing::drawLine(image, {5, 15}, {25, 15}, {255, 255, 255}); // horizontal white line
  gfx2d::Drawing::drawLine(image, {5, 5}, {25, 25}, {0, 255, 0}); // diagonal green line
  gfx2d::Drawing::drawLine(image, {5, 25}, {25, 5}, {0, 0, 255}); // diagonal blue line

  // Write as RGBA
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/lines.png", image));

  // Compare output with input
  imgproc::Image<unsigned char, 3> groundtruth;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/lines.png", groundtruth));
  QVERIFY(image == groundtruth);
}

void Graphics2D_test::test_drawCircle()
{
  imgproc::Image<unsigned char, 3> image(30, 30);

  gfx2d::Drawing::drawCircle(image, {15, 15}, 10, {255, 0, 0});

  // Write as RGBA
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/circle.png", image));

  // Compare output with input
  imgproc::Image<unsigned char, 3> groundtruth;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/circle.png", groundtruth));
  QVERIFY(image == groundtruth);
}

void Graphics2D_test::test_drawRectangle()
{
  imgproc::Image<unsigned char, 3> image(30, 20);

  // Draw rectangle WITHOUT fill
  gfx2d::Drawing::drawRectangle(image, {5, 5}, {25, 15}, {255, 0, 0});

  // Write to file
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/rectangle.png", image));

  // Compare output with input
  imgproc::Image<unsigned char, 3> groundtruth;
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/rectangle.png", groundtruth));
  QVERIFY(image == groundtruth);

  // Draw rectangle WITH fill
  image.clear();
  gfx2d::Drawing::drawRectangle(image, {5, 5}, {25, 15}, {255, 0, 0}, true);

  // Write to file
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/rectangle_fill.png", image));

  // Compare output with input
  QVERIFY(TestUtilities::ReadImageFromFile(QFileInfo(__FILE__).absolutePath() + "/resources/rectangle_fill.png", groundtruth));
  QVERIFY(image == groundtruth);
}

void Graphics2D_test::test_drawLinearCurve()
{

}

void Graphics2D_test::test_drawQuadraticCurve()
{
  std::vector<std::array<double, 2>> points;
  points.push_back({10, 30});
  points.push_back({40, 90});
  points.push_back({110, 40});
  gfx2d::BezierCurve quadratic(points);

  imgproc::Image<unsigned char, 3> image(120, 100);

  gfx2d::Drawing::drawCurve(image, quadratic, {255, 0, 0});
  image.setPixel(points[0][0], points[0][1], {255,255,255});
  image.setPixel(points[1][0], points[1][1], {255,255,255});
  image.setPixel(points[2][0], points[2][1], {255,255,255});

  // Write to file
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/bezier_quadratic.png", image));

}

void Graphics2D_test::test_drawCubicCurve()
{
  std::vector<std::array<double, 2>> points;
  points.push_back({10, 50});
  points.push_back({10, 10});
  points.push_back({90, 90});
  points.push_back({90, 50});
  gfx2d::BezierCurve cubic(points);

  imgproc::Image<unsigned char, 3> image(100, 100);

  // Draw curve and control points
  gfx2d::Drawing::drawCurve(image, cubic, {255, 0, 0});
  for (auto point : points)
  {
    image.setPixel(point[0], point[1], {255,255,255});
  }

  std::cout << cubic << std::endl;

  // Split curve
  gfx2d::BezierCurve quartic = cubic.split();

  std::cout << quartic << std::endl;

  // Draw curve and control points
  gfx2d::Drawing::drawCurve(image, quartic, {0, 255, 0});
  for (auto point : quartic.points())
  {
    image.setPixel(point[0], point[1], {255,127,0});
  }

  // Write to file
  QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/bezier_cubic.png", image));
}

QTEST_APPLESS_MAIN(Graphics2D_test)

#include "Graphics2D_test.moc"
