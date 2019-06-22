#ifndef VIDEOSURFACE_H
#define VIDEOSURFACE_H

#include <QAbstractVideoSurface>

class MainWindow;

class VideoSurface : public QAbstractVideoSurface
{
  Q_OBJECT
public:
  explicit VideoSurface(QObject *parent = nullptr);
  //~VideoSurface();

  void setMainWindow(MainWindow *mw)
  {
    m_mainWindow = mw;
  }

  // Format functions
  QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType type = QAbstractVideoBuffer::NoHandle) const override;

  // Presentation functions
  bool present(const QVideoFrame &frame) override;
  bool start(const QVideoSurfaceFormat &format) override;
  void stop() override;

signals:

public slots:

private:
  MainWindow *m_mainWindow;

//  QImage qt_imageFromVideoFrame(const QVideoFrame &f);
};

#endif // VIDEOSURFACE_H
