#include <SpatiumLib/Imaging/Image.h>

#include <QString>
#include <QImage>

#include <functional>

class TestUtilities
{
public:
 static bool ReadImageFromFile(const QString &fileName, Imaging::Image &image);
 static bool WriteImageToFile(const QString &fileName, const Imaging::Image &image);

private:
  TestUtilities();
};

bool TestUtilities::ReadImageFromFile(const QString &fileName, Imaging::Image &image)
{
  // Read QImage from file
  QImage inputImage(fileName);
  if (inputImage.isNull())
  {
    return false;
  }

  // Determine image format + copy-value function
  Imaging::Image::Format format;
  std::function<void(const QImage&, Imaging::Image&, int, int)> copyValue;

  switch (inputImage.format())
  {
  case QImage::Format_Grayscale8:
    // Set image format
    format = Imaging::Image::Format_Grayscale8;

    // Set copy-value function
    copyValue = [&](const QImage &input, Imaging::Image &output, int x, int y) {
      output.imageData()[y * output.width() + x] = qGray(input.pixel(x,y));
    };

    break;
  case QImage::Format_RGB32:
    // Set image format
    format = Imaging::Image::Format_RGB32;

    // Set copy-value function
    copyValue = [&](const QImage &input, Imaging::Image &output, int x, int y) {
      Imaging::Color32bppRgb *colorRgb = reinterpret_cast<Imaging::Color32bppRgb *>(
        output.imageData()) + ((y * output.width()) + x);
      QRgb rgb = input.pixel(x, y);
      colorRgb->red = qRed(rgb);
      colorRgb->green = qGreen(rgb);
      colorRgb->blue = qBlue(rgb);
      colorRgb->unused = 0xFF;
    };

    break;
  case QImage::Format_ARGB32:
    // Set image format
    format = Imaging::Image::Format_RGBA32;

    // Set copy-value function
    copyValue = [&](const QImage &input, Imaging::Image &output, int x, int y) {
      Imaging::Color32bppRgba *colorRgba = reinterpret_cast<Imaging::Color32bppRgba *>(
        output.imageData()) + ((y * output.width()) + x);
      QRgb rgb = input.pixel(x, y);
      colorRgba->red = qRed(rgb);
      colorRgba->green = qGreen(rgb);
      colorRgba->blue = qBlue(rgb);
      colorRgba->alpha = qAlpha(rgb);
    };

    break;
  default:
    return false;
  }

  // Create Imaging::Image
  Imaging::Image outputImage(inputImage.width(), inputImage.height(), format);

  // Set pixel values
  for (int y = 0; y < outputImage.height(); y++)
  {
    for (int x = 0; x < outputImage.width(); x++)
    {
      copyValue(inputImage, outputImage, x, y);
    }
  }

  image = outputImage;
  return true;
}

bool TestUtilities::WriteImageToFile(const QString &fileName, const Imaging::Image &image)
{
  // Determine image format + copy-value function
  QImage::Format format;
  std::function<void(const Imaging::Image&, QImage&, int, int)> copyValue;

  switch (image.format())
  {
  case Imaging::Image::Format_Grayscale8:
    // Set format
    format = QImage::Format_Grayscale8;

    // Set copy-value function
    copyValue = [&](const Imaging::Image &input, QImage &output, int x, int y) {
      unsigned char val = input.imageData()[y * input.width() + x];
      output.setPixel(x, y, qGray(val, val, val));
    };

    break;
  case Imaging::Image::Format_RGB32:
    // Set format
    format = QImage::Format_RGB32;

    // Set copy-value function
    copyValue = [&](const Imaging::Image &input, QImage &output, int x, int y) {
      Imaging::Color32bppRgb *color = reinterpret_cast<Imaging::Color32bppRgb *>(
         input.imageData()) + y * input.width() + x;
      output.setPixel(x, y, qRgb(color->red, color->green, color->blue));
    };

    break;
  case Imaging::Image::Format_RGBA32:
    // Set format
    format = QImage::Format_ARGB32;

    // Set copy-value function
    copyValue = [&](const Imaging::Image &input, QImage &output, int x, int y) {
      Imaging::Color32bppRgba *color = reinterpret_cast<Imaging::Color32bppRgba *>(
         input.imageData()) + y * input.width() + x;
      output.setPixel(x, y, qRgba(color->red, color->green, color->blue, color->alpha));
    };

    break;
  default:
    return false;
  }

  QImage outputImage(image.width(), image.height(), format);

  // Set pixel values
  for (int y = 0; y < outputImage.height(); y++)
  {
    for (int x = 0; x < outputImage.width(); x++)
    {
      copyValue(image, outputImage, x, y);
    }
  }

  // Save output image
  return outputImage.save(fileName);
}
