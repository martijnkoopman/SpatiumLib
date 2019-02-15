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
  // Create an object with one vertex at origin. No transformation applied.
  geom3d::Point3 origin = {0,0,0};
  std::vector<geom3d::Point3> vertices;
  vertices.push_back(origin);
  std::vector<std::array<int, 2>> edges;
  gfx3d::Mesh pointMesh(vertices, edges);

  // Convert point to world coordinates
  geom3d::Point3 worldPoint = pointMesh.objectPointToWorldPoint(origin);

  // Check coinciding points
  QCOMPARE(worldPoint, origin);

  // Translate object in world space
  pointMesh.setPosition({10, 5, 2});

  // Rotate mesh around itself. Should not affect position
  pointMesh.rotate({90, 45, 0});

  // Convert object origin to world space
  worldPoint = pointMesh.objectPointToWorldPoint(origin);

  // Check translated point
  QCOMPARE(worldPoint, geom3d::Point3({10, 5, 2}));

  // Get world origin in object space
  geom3d::Point3 objectPoint  = pointMesh.worldPointToObjectPoint(origin);

  // Check point in world space
  QCOMPARE(objectPoint, geom3d::Point3({-10, -5, -2}));
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
