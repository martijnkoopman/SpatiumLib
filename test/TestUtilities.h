#include <spatium/imgproc/Image.h>

#include <QString>
#include <QImage>

#include <functional>

using namespace spatium;

// To read a pixel value from an QImage
template<typename T, int N>
struct ValueReader
{
};

// To READ a pixel value from an QImage.
// The input value has always 1 CHANNEL using using this template.
template<typename T>
struct ValueReader<T, 1>
{
  static std::array<T, 1> pixelValue(int gray) { return { static_cast<T>(gray) }; }
  static std::array<T, 1> pixelValue(int red, int green, int blue) { return { static_cast<T>(red) * 0.2125 + static_cast<T>(green) * 0.7154 + static_cast<T>(blue) * 0.072 }; }
  static std::array<T, 1> pixelValue(int red, int green, int blue, int) { return { static_cast<T>(red * 0.2125) + static_cast<T>(green * 0.7154) + static_cast<T>(blue * 0.0721) }; }
};

// To READ a pixel value from an QImage.
// The input value has always 3 CHANNELS using using this template.
template<typename T>
struct ValueReader<T, 3>
{
  static std::array<T, 3> pixelValue(int gray) { return std::array<T, 3> { static_cast<T>(gray), static_cast<T>(gray), static_cast<T>(gray) }; }
  static std::array<T, 3> pixelValue(int red, int green, int blue) { return std::array<T, 3> { static_cast<T>(red), static_cast<T>(green), static_cast<T>(blue) }; }
  static std::array<T, 3> pixelValue(int red, int green, int blue, int) { return std::array<T, 3> { static_cast<T>(red), static_cast<T>(green), static_cast<T>(blue) }; }
};

// To READ a pixel value from an QImage.
// The input value has always 4 CHANNELS using using this template.
template<typename T>
struct ValueReader<T, 4>
{
  static std::array<T, 4> pixelValue(int gray) { return std::array<T, 4> { static_cast<T>(gray), static_cast<T>(gray), static_cast<T>(gray), 255 }; }
  static std::array<T, 4> pixelValue(int red, int green, int blue) { return std::array<T, 4> { static_cast<T>(red), static_cast<T>(green), static_cast<T>(blue), 255 }; }
  static std::array<T, 4> pixelValue(int red, int green, int blue, int alpha) { return std::array<T, 4> { static_cast<T>(red), static_cast<T>(green), static_cast<T>(blue), static_cast<T>(alpha) }; }
};

// To write a pixel value to an QImage
template<typename T, int N>
struct ValueWriter
{
};

// To WRITE a pixel value to an QImage
// The input value has always 1 CHANNEL using using this template.
template<typename T>
struct ValueWriter<T, 1>
{
  static uint pixelValue(std::array<T, 1> gray) { return gray[0]; }
};

// To WRITE a pixel value to an QImage
// The input value has always 3 CHANNELS using using this template.
template<typename T>
struct ValueWriter<T, 3>
{
  static uint pixelValue(std::array<T, 3> rgb) { return qRgb(rgb[0], rgb[1], rgb[2]); }
};

// To WRITE a pixel value to an QImage
// The input value has always 4 CHANNELS using using this template.
template<typename T>
struct ValueWriter<T, 4>
{
  static uint pixelValue(std::array<T, 4> rgba) { return qRgba(rgba[0], rgba[1], rgba[2], rgba[3]); }
};

class TestUtilities
{
public:

  // Read an image from file
  template<typename T, int N>
  static bool ReadImageFromFile(const QString &fileName, imgproc::Image<T, N> &image)
  {
    // Read QImage from file
    QImage input(fileName);
    if (input.isNull())
    {
      return false;
    }

    image.resize(input.width(), input.height());

    for (int y = 0; y < image.height(); y++)
    {
      for (int x = 0; x < image.width(); x++)
      {
        if (input.format() == QImage::Format_Grayscale8)
        {
          int gray = qGray(input.pixel(x,y));
          std::array<T, N> val = ValueReader<T, N>::pixelValue(gray);
          image.setPixel(x, y, val);
        }
        else if(input.format() == QImage::Format_RGB32)
        {
          QRgb rgb = input.pixel(x, y);
          std::array<T, N> val = ValueReader<T, N>::pixelValue(qRed(rgb), qGreen(rgb), qBlue(rgb));
          image.setPixel(x, y, val);
        }
        else if(input.format() == QImage::Format_ARGB32)
        {
          QRgb rgba = input.pixel(x, y);
          std::array<T, N> val = ValueReader<T, N>::pixelValue(qRed(rgba), qGreen(rgba), qBlue(rgba), qAlpha(rgba));
          image.setPixel(x, y, val);
        }
        else
        {
          return false;
        }
      }
    }

    return true;
  }

  // Write an image to file
  template<class T, int N>
  static bool WriteImageToFile(const QString &fileName, const imgproc::Image<T, N> &image)
  {
    // Determine output image format
    QImage::Format format;
    if (N == 1)
    {
      format = QImage::Format_Grayscale8;
    }
    else if(N == 3) {
      format = QImage::Format_RGB32;
    }
    else if(N == 4) {
      format = QImage::Format_ARGB32;
    }
    else {
      return false;
    }

    // Create output image
    QImage outputImage(image.width(), image.height(), format);

    // Set pixel values
    for (int y = 0; y < outputImage.height(); y++)
    {
      for (int x = 0; x < outputImage.width(); x++)
      {
        std::array<T, N> val = image.getPixel(x,y);

        if (format == QImage::Format_Grayscale8)
        {
          uint grayColor = ValueWriter<T, N>::pixelValue(val);
          outputImage.setPixelColor(x, y, QColor(grayColor, grayColor, grayColor));
        }
        else
        {
          outputImage.setPixel(x, y, ValueWriter<T, N>::pixelValue(val));
        }
      }
    }

    // Save output image
    return outputImage.save(fileName);
  }

private:
  TestUtilities() = delete;
};
