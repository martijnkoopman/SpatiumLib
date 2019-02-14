#include <QtTest>
#include "TestUtilities.h"

#include <spatium/imgproc/Image.h>
#include <spatium/gfx3d/Scene.h>
#include <spatium/gfx3d/Mesh.h>
#include <spatium/gfx3d/OrthographicCamera.h>
#include <spatium/gfx3d/WireframeRenderer.h>

#include <memory> // std::shared_ptr

using namespace spatium;

class Graphics3D_test : public QObject
{
  Q_OBJECT

public:
  Graphics3D_test();
  ~Graphics3D_test();

private slots:
  void test_cubeMesh();
  void test_sceneObjectTransform();
  void test_objectPointToWorldPoint();
  void test_orthographicProjection();

private:
};

Graphics3D_test::Graphics3D_test()
{

}

Graphics3D_test::~Graphics3D_test()
{

}

// Test functions

void Graphics3D_test::test_cubeMesh()
{
  // Construct mesh with diameter of 2 at origin
  gfx3d::Mesh cube = gfx3d::Mesh::cube(2);

  // Check bounds
  std::array<double, 6> bounds = cube.bounds();
  QCOMPARE(bounds[0], -1); // Xmin
  QCOMPARE(bounds[1],  1); // Xmax
  QCOMPARE(bounds[2], -1); // Ymin
  QCOMPARE(bounds[3],  1); // Ymax
  QCOMPARE(bounds[4], -1); // Zmin
  QCOMPARE(bounds[5],  1); // Zmax
}

void Graphics3D_test::test_sceneObjectTransform()
{
  // Construct mesh with diameter of 2 at origin
  gfx3d::Mesh cube = gfx3d::Mesh::cube(2);

  cube.setPosition({0, 0, 10});



  // gfx3d::WireframeRenderer renderer;
  //renderer.render(scene, )


}

void Graphics3D_test::test_objectPointToWorldPoint()
{
  //gfx3d::Mesh cube = gfx3d::Mesh::cube(1);
  //geom3d::Point3 vertex0 = cube.vertex(0);
  //cube.rotate(0, 0, 90 * spatium::Deg2Rad);

  // Write to file
  // QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/bezier_cubic.png", image));
}

void Graphics3D_test::test_orthographicProjection()
{
  // Create a scene
  gfx3d::Scene scene;

  // Add a cube mesh to the scene
  auto cube = std::make_shared<gfx3d::Mesh>(gfx3d::Mesh::cube(2));
  scene.addRenderObject(cube);

  // Set othographic camera in the scene
  auto camera = std::make_shared<gfx3d::OrthographicCamera>(1,1);
  camera->lookAt({10,10,10}, {0,0,0}, {0,0,1});
  scene.setCamera(camera);

  // Render a 2D wireframe image
  imgproc::Image<unsigned char, 3> image(640, 480);
  gfx3d::WireframeRenderer renderer;
  renderer.render(scene, image);

  // Compare image....
}

QTEST_APPLESS_MAIN(Graphics3D_test)

#include "Graphics3D_test.moc"
