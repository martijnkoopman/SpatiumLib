#include <QApplication>

#include "SceneWidget.h"

#include <spatium/gfx3d.h>

using namespace spatium;

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Martijn Koopman");
  QCoreApplication::setApplicationName("SceneViewer");
  QCoreApplication::setApplicationVersion("0.1.0");

  // Create a scene
  gfx3d::Scene scene;

  // Add a cube mesh with size 2 at origin
  auto cube = std::make_shared<gfx3d::Mesh>(gfx3d::Mesh::cube(2));
  scene.addRenderObject(cube);

  // X axis (red)
  std::vector<geom3d::Point3> vertices = { {0, 0, 0}, {1, 0, 0} };
  std::vector<std::array<int, 2>> edges = { {0, 1} };
  auto xAxis = std::make_shared<gfx3d::Mesh>(vertices, edges);
  xAxis->setColor({255, 0, 0});
  scene.addRenderObject(xAxis);

  // Y axis (green)
  vertices = { {0, 0, 0}, {0, 1, 0} };
  edges = { {0, 1} };
  auto yAxis = std::make_shared<gfx3d::Mesh>(vertices, edges);
  yAxis->setColor({0, 255, 0});
  scene.addRenderObject(yAxis);

  // Z axis (blue)
  vertices = { {0, 0, 0}, {0, 0, 1} };
  edges = { {0, 1} };
  auto zAxis = std::make_shared<gfx3d::Mesh>(vertices, edges);
  zAxis->setColor({0, 0, 255});
  scene.addRenderObject(zAxis);

  // Set othographic camera in the scene
  auto camera = std::make_shared<gfx3d::OrthographicCamera>(5, 15, 5);
  camera->lookAt({10,5,5}, {0,0,0}, {0,0,1});
  //camera->lookAt({0,-5,0}, {0,0,0}, {0,0,1});
  scene.setCamera(camera);

  // Construct scene widget
  SceneWidget widget(scene);
  widget.show();

  return app.exec();
}
