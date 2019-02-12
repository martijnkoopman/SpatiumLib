#include <QtTest>
#include "TestUtilities.h"

#include <spatium/imgproc/Image.h>
#include <spatium/gfx3d/SceneObject.h>
//#include <spatium/gfx3d/Camera.h>

using namespace spatium;

class Graphics3D_test : public QObject
{
  Q_OBJECT

public:
  Graphics3D_test();
  ~Graphics3D_test();

private slots:
  void test_objectPointToWorldPoint();

private:
};

Graphics3D_test::Graphics3D_test()
{

}

Graphics3D_test::~Graphics3D_test()
{

}

// Test functions

void Graphics3D_test::test_objectPointToWorldPoint()
{
  //

  // Write to file
  // QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/bezier_cubic.png", image));
}

QTEST_APPLESS_MAIN(Graphics3D_test)

#include "Graphics3D_test.moc"
