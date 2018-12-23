#include <QtTest>

#include <SpatiumLib/Imaging/Image.h>
#include <SpatiumLib/Graphics2D/Line.h>
#include <SpatiumLib/Graphics2D/Drawing.h>

class Graphics2D_test : public QObject
{
  Q_OBJECT

public:
  Graphics2D_test();
  ~Graphics2D_test();

private slots:
  void test_drawPoint();
  void test_drawLine();
  void test_drawCircle();

private:
};

Graphics2D_test::Graphics2D_test()
{

}

Graphics2D_test::~Graphics2D_test()
{

}

// Draw functions
void Graphics2D_test::test_drawPoint()
{
  Graphics2D::Point point(10, 10);
  int radius = 5;

  //Graphics2D::Drawing::drawLine(point, radius, color, image);
}

void Graphics2D_test::test_drawLine()
{
  Graphics2D::Point start(10, 10);
  Graphics2D::Point end(90, 40);
  Graphics2D::Line line(start, end);

  //Graphics2D::Drawing::drawLine(line, color, image);
}

void Graphics2D_test::test_drawCircle()
{
  Graphics2D::Point center(30, 40);
  int radius = 20;

  //Graphics2D::Drawing::drawCircle(circle, fill, color, image);
}

QTEST_APPLESS_MAIN(Graphics2D_test)

#include "Graphics2D_test.moc"
