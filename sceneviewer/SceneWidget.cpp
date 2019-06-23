#include "SceneWidget.h"

#include "qimageconvert.h"

#include <QMouseEvent>
#include <QWheelEvent>

SceneWidget::SceneWidget(spatium::gfx3d::Scene &scene, QWidget *parent)
  : QLabel(parent)
  , m_scene(scene)
  , m_mousePressed(false)
{
  setMouseTracking(true);
}

void SceneWidget::render()
{
  size_t width = static_cast<size_t>(size().width());
  size_t height = static_cast<size_t>(size().height());

  // Construct image
  spatium::Image<unsigned char, 3> image(width, height);

  // Render frame
  //image.pixel(width/2, height/2) = { 255, 0, 0 };
  spatium::gfx3d::WireframeRenderer renderer;
  renderer.render(m_scene, image);

  // Convert to QImage
  QImage qimageOut;
  spatium::QImageConvert::ImageToQImage(image, qimageOut);

  // Show as pixmap in label
  setPixmap(QPixmap::fromImage(qimageOut));
}

QSize SceneWidget::sizeHint() const
{
  return QSize(640, 480);
}

void SceneWidget::mouseMoveEvent(QMouseEvent *event)
{
  QPoint oldMousePosition = m_mousePosition;
  m_mousePosition = event->pos();

  if (m_mousePressed)
  {
    QPoint delta = m_mousePosition - oldMousePosition;

    double angleX = spatium::PI * delta.x() / size().width();
    double angleY = spatium::PI * delta.y() / size().height();

    // Rotate camera around origin
    auto camera = m_scene.camera();
    if (camera == nullptr)
    {
      return;
    }

    // For now only support orthographic projection
    std::shared_ptr<spatium::gfx3d::OrthographicCamera> cameraOrtho = std::dynamic_pointer_cast<spatium::gfx3d::OrthographicCamera>(camera);
    if (cameraOrtho == nullptr)
    {
      return;
    }

    camera->transform().rotateAround(camera->transform().up(), angleX);
    camera->transform().rotateAround(camera->transform().right(), -angleY);
    camera->orthogonalizeViewUp();

    render();
  }
}

void SceneWidget::mousePressEvent(QMouseEvent *event)
{
  m_mousePressed = true;
}

void SceneWidget::mouseReleaseEvent(QMouseEvent *event)
{
  m_mousePressed = false;
}

void SceneWidget::resizeEvent(QResizeEvent *event)
{
  render();
}

void SceneWidget::showEvent(QShowEvent *event)
{
  render();
}

void SceneWidget::wheelEvent(QWheelEvent *event)
{
  event->accept();

  QPoint numDegrees = event->angleDelta() / 8;

  if (!numDegrees.isNull())
  {
    QPoint numSteps = numDegrees / 15;

    // Check for camera in scene
    auto camera = m_scene.camera();
    if (camera == nullptr)
    {
      return;
    }

    // For now only support orthographic projection
    std::shared_ptr<spatium::gfx3d::OrthographicCamera> cameraOrtho = std::dynamic_pointer_cast<spatium::gfx3d::OrthographicCamera>(camera);
    if (cameraOrtho == nullptr)
    {
      return;
    }

    double orthoSize = cameraOrtho->size();
    if (numSteps.y() > 0)
    {
      cameraOrtho->setSize(orthoSize-1);
    }
    else if(numSteps.y() < 0)
    {
     cameraOrtho->setSize(orthoSize+1);
    }

    render();
  }
}
