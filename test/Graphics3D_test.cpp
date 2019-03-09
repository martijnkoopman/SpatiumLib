#include <QtTest>
#include "TestUtilities.h"
#include "ImageIO.h"

#include <spatium/Image.h>
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
  void test_transform();
  void test_lookAt();
  void test_cubeMesh();
  void test_sceneObjectTransform();
  void test_objectPointToWorldPoint();
  void test_wireframeRendering();

private:
};

Graphics3D_test::Graphics3D_test()
{

}

Graphics3D_test::~Graphics3D_test()
{

}

// Test functions

void Graphics3D_test::test_transform()
{
  gfx3d::Transform transform;

  // Check transformation matrix is identity matrix
  geom3d::Matrix4x4 matrix = transform.matrix();
  QCOMPARE(transform.rotation(), geom3d::Vector3(0,0,0));
  QCOMPARE(transform.right(), geom3d::Vector3(1,0,0));
  QCOMPARE(transform.up(), geom3d::Vector3(0,1,0));
  QCOMPARE(transform.back(), geom3d::Vector3(0,0,1));

  // Rotate along x axis 90 degrees counterclockwise
  transform.rotate({90 * Deg2Rad, 0, 0});
  QVERIFY(TestUtilities::fuzzyCompareMatrix(transform.right(), geom3d::Vector3(1,0,0)));
  QVERIFY(TestUtilities::fuzzyCompareMatrix(transform.up(), geom3d::Vector3(0,0,1)));
  QVERIFY(TestUtilities::fuzzyCompareMatrix(transform.back(), geom3d::Vector3(0,-1,0)));

  // Set rotation around three axis
  double deg90 = 90 * Deg2Rad;
  double deg45 = 45 * Deg2Rad;
  double deg22 = 22.5 * Deg2Rad;
  transform.setRotation({ deg90, deg45, deg22 });
  QVERIFY(TestUtilities::fuzzyCompareMatrix(transform.rotation(), geom3d::Vector3(deg90, deg45, deg22)));
}

void Graphics3D_test::test_lookAt()
{
  gfx3d::OrthographicCamera camera(5, 15, 10);

  // By default the camera is positioned at the origin (0,0,0) and aligned
  // along the negative Z axis.

//  // Point centered at near plane
//  geom3d::Point3 viewPoint = camera.worldToViewPoint({0, 0, -5});
//  QVERIFY(TestUtilities::fuzzyCompareMatrix(viewPoint, geom3d::Point3(0,0,1)));

//  // Point centered at far plane
//  viewPoint = camera.worldToViewPoint({0, 0, -15});
//  QVERIFY(TestUtilities::fuzzyCompareMatrix(viewPoint, geom3d::Point3(0,0,-1)));

//  // Set camera at (10,0,0) and look along positive X axis with Y is up
//  camera.lookAt({10, 0, 0}, {20, 0, 0}, {0, 0, 1});

//  viewPoint = camera.worldToViewPoint({25, 0, 0});
//  QVERIFY(TestUtilities::fuzzyCompareMatrix(viewPoint, geom3d::Point3(0,0,-1)));
}

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
  geom3d::Point3 worldPoint = pointMesh.transform().objectPointToWorldPoint(origin);

  // Check coinciding points
  QCOMPARE(worldPoint, origin);

  // Translate object in world space
  pointMesh.transform().setPosition({10, 5, 2});

  // Rotate mesh around itself. Should not affect position
  pointMesh.transform().rotate({90, 45, 0});

  // Convert object origin to world space
  worldPoint = pointMesh.transform().objectPointToWorldPoint(origin);

  // Check translated point
  QCOMPARE(worldPoint, geom3d::Point3({10, 5, 2}));

  // Get world origin in object space
  geom3d::Point3 objectPoint  = pointMesh.transform().worldPointToObjectPoint(origin);

  // Check point in world space
  QCOMPARE(objectPoint, geom3d::Point3({-10, -5, -2}));
}

void Graphics3D_test::test_objectPointToWorldPoint()
{
//  gfx3d::Mesh cube = gfx3d::Mesh::cube(2);
//  gfx3d::OrthographicCamera camera(1,1);
//  camera.lookAt({10,10,10}, {0,0,0}, {0,0,1});



  //gfx3d::Mesh cube = gfx3d::Mesh::cube(1);
  //geom3d::Point3 vertex0 = cube.vertex(0);
  //cube.rotate(0, 0, 90 * spatium::Deg2Rad);

  // Write to file
  // QVERIFY(TestUtilities::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/bezier_cubic.png", image));
}

void Graphics3D_test::test_wireframeRendering()
{
  // Create a scene
  gfx3d::Scene scene;

  // Add a cube mesh with size 2 at origin
  auto cube = std::make_shared<gfx3d::Mesh>(gfx3d::Mesh::cube(2));
  scene.addRenderObject(cube);

  // Set othographic camera in the scene
  auto camera = std::make_shared<gfx3d::OrthographicCamera>(5, 15, 5);
  camera->lookAt({10,5,5}, {0,0,0}, {0,0,1});
  scene.setCamera(camera);

  // Render a 2D wireframe image
  Image<unsigned char, 3> image(640, 480);
  gfx3d::WireframeRenderer renderer;
  renderer.render(scene, image);

  // Write image to output
  QVERIFY(ImageIO::WriteImageToFile(QFileInfo(__FILE__).absolutePath() + "/resources/tmp/render_cube.png", image));

}

QTEST_APPLESS_MAIN(Graphics3D_test)

#include "Graphics3D_test.moc"
