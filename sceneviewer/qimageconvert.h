#ifndef SPATIUMLIB_QIMAGECONVERT_H
#define SPATIUMLIB_QIMAGECONVERT_H

#include <QImage>
#include <spatium/Image.h>

namespace spatium {

class QImageConvert
{
public:
  /// QImageToImage
  ///
  /// \param[in] qimage QImage
  /// \param[out] image Image
  /// \return True on success, false otherwise
  static bool QImageToImage(const QImage &qimage, Image<unsigned char, 3> &image)
  {
    if (qimage.format() != QImage::Format_RGB888)
    {
      return false;
    }

    image.resize(qimage.width(), qimage.height());

    for (int y = 0; y < qimage.height(); y++)
    {
      for (int x = 0; x < qimage.width(); x++)
      {
        QRgb rgb = qimage.pixel(x, y);
        std::array<unsigned char, 3> val = { static_cast<unsigned char>(qRed(rgb)),
                                             static_cast<unsigned char>(qGreen(rgb)),
                                             static_cast<unsigned char>(qBlue(rgb)) };
        image.pixel(x, y) = val;
      }
    }

    return true;
  }

  /// ImageToQImage
  ///
  /// \param[in] image Image
  /// \param[out] qimage QImage
  /// \return True on success, false otherwise
  static bool ImageToQImage(const Image<unsigned char, 3> &image, QImage &qimage)
  {
    qimage = QImage(image.width(), image.height(), QImage::Format_RGB888);

    for (int y = 0; y < image.height(); y++)
    {
      for (int x = 0; x < image.width(); x++)
      {
        std::array<unsigned char, 3> rgb = image.pixel(x,y);
        qimage.setPixel(x, y, qRgb(rgb[0], rgb[1], rgb[2]));
      }
    }

    return true;
  }

  static bool ImageToQImage(const Image<unsigned char, 1> &image, QImage &qimage)
  {
    qimage = QImage(image.width(), image.height(), QImage::Format_Grayscale8);

    for (int y = 0; y < image.height(); y++)
    {
      for (int x = 0; x < image.width(); x++)
      {
        unsigned char gray = image.pixel(x,y)[0];
        qimage.setPixelColor(x, y, QColor(gray, gray, gray));
      }
    }

    return true;
  }

private:
  QImageConvert() = delete;
};

} // namespace spatium

#endif // SPATIUMLIB_QIMAGECONVERT_H
