#include "VideoSurface.h"
#include "MainWindow.h"
#include "qimageconvert.h"

#include <QVideoSurfaceFormat>
#include <QVideoFrame>

#include <spatium/Image.h>
#include <spatium/imgproc/GlobalThreshold.h>
#include <spatium/imgproc/Grayscale.h>
#include <spatium/imgproc/Blur.h>
#include <spatium/imgproc/Sobel.h>

VideoSurface::VideoSurface(QObject *parent)
  : QAbstractVideoSurface(parent)
{

}

QList<QVideoFrame::PixelFormat> VideoSurface::supportedPixelFormats(QAbstractVideoBuffer::HandleType type) const
{
  QList<QVideoFrame::PixelFormat> pixelFormats = { QVideoFrame::Format_RGB24 }; //, QVideoFrame::Format_RGB32, QVideoFrame::Format_ARGB32, QVideoFrame::Format_Y8, QVideoFrame::Format_Y16 };
  return pixelFormats;
}

bool VideoSurface::present(const QVideoFrame &frame)
{
  QVideoFrame copyFrame(frame);
  copyFrame.map(QAbstractVideoBuffer::ReadOnly);

  QImage::Format imageFormat = QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat());
  if (imageFormat == QImage::Format_Invalid)
  {
      copyFrame.unmap();
      return false;
  }

  QImage qimage(frame.bits(),
             frame.width(),
             frame.height(),
             frame.bytesPerLine(),
             imageFormat);
  copyFrame.unmap();

  if(qimage.isNull())
  {
    return false;
  }

  // QImage to spatium Image
  spatium::Image<unsigned char, 3> image;
  spatium::QImageConvert::QImageToImage(qimage, image);

  // Grayscale
  spatium::Image<unsigned char, 1> grayscale(frame.width(), frame.height());
  spatium::imgproc::Grayscale<unsigned char> grayscaleFilter;
  grayscaleFilter.apply(image, grayscale);

  // Blur
  spatium::Image<unsigned char, 1> blur(frame.width(), frame.height());
  spatium::imgproc::Blur blurFilter;
  blurFilter.apply(grayscale, blur);

  // Sobel
  spatium::Image<unsigned char, 1> sobel(frame.width(), frame.height());
  spatium::imgproc::Sobel sobelFilter;
  sobelFilter.apply(blur, sobel);

  // Threshold
//  spatium::Image<unsigned char, 1> binary(frame.width(), frame.height());
//  spatium::imgproc::GlobalThresholdFilter<unsigned char> filter(127);
//  filter.apply(image, binary);

  // Spatium image to QImage
  QImage qimageOut;
  spatium::QImageConvert::ImageToQImage(sobel, qimageOut);

  m_mainWindow->setImage(qimageOut);

  return true;
}

bool VideoSurface::start(const QVideoSurfaceFormat &format)
{
  QAbstractVideoSurface::start(format);

  QSize size = format.frameSize();
  QVideoFrame::PixelFormat pixelFormat = format.pixelFormat();
  qreal frameRate = format.frameRate();

  m_mainWindow->setImageSize(size);

  QString str = QString("%1 x %2 @ %3 fps").arg(size.width()).arg(size.height()).arg(frameRate);
  m_mainWindow->setStatusMessage(str);

  return true;
}

void VideoSurface::stop()
{
  QAbstractVideoSurface::stop();
}
