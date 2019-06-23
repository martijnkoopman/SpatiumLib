#ifndef SCENEWIDGET_H
#define SCENEWIDGET_H

#include <QLabel>

#include <spatium/gfx3d.h>

class SceneWidget : public QLabel
{
  Q_OBJECT
public:
  explicit SceneWidget(spatium::gfx3d::Scene &scene, QWidget *parent = nullptr);

  void render();

signals:

public slots:

protected:
  virtual QSize sizeHint() const override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseReleaseEvent(QMouseEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

private:
  spatium::gfx3d::Scene &m_scene;

  bool m_mousePressed;
  QPoint m_mousePosition;
};

#endif // SCENEWIDGET_H
