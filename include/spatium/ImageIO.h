/*
 * Program: Spatium Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef SPATIUMLIB_IMAGEIO_H
#define SPATIUMLIB_IMAGEIO_H

#include "Image.h"

#include <fstream> // std::ofstream

namespace spatium {

/// \class ImageIO
/// \brief Read and write images as PNM files (Portable Any Map).
///
/// This class supports 3 types:
///
/// Portable Bit Map (PBM)
/// http://netpbm.sourceforge.net/doc/pbm.html
/// This file format supports binary images (0 or 1 values).
///
/// Portable Gray Map (PGM)
/// http://netpbm.sourceforge.net/doc/ppm.html
/// This file format supports grayscale images. 8 and 16 bit.
///
/// Portable Pixel Map (PPM)
/// http://netpbm.sourceforge.net/doc/ppm.html
/// This file format supports RGB images.
class ImageIO
{
public:

  /// Write 8-bit grayscale image to file as PGM (Portable Gray Map)
  ///
  /// \param[in] image Image
  /// \param[in] pgmPath Path to PGM file. Should have file extension *.pgm
  /// \return True on success, false otherwise
  static bool writeGrayscaleImageAsPgm(const Image<unsigned char, 1> &image, const std::string &pgmPath)
  {
    std::ofstream ofile(pgmPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    ofile.write("P5\n", 3);

    // Write width ASCII
    std::string widthStr = std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write maximum value
    ofile.write("255\n", 4);

    // Write pixel values
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < image.width(); x++)
      {
        char val = static_cast<char>(image.pixel(x,y,false)[0]);
        ofile.write(&val, 1);
      }
    }

    ofile.close();

    return  true;
  }

  /// Write 16-bit grayscale image to file as PGM (Portable Gray Map)
  ///
  /// \param[in] image Image
  /// \param[in] pgmPath Path to PGM file. Should have file extension *.pgm
  /// \return True on success, false otherwise
  static bool writeGrayscaleImageAsPgm(const Image<unsigned short, 1> &image, const std::string &pgmPath)
  {
    std::ofstream ofile(pgmPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    ofile.write("P5\n", 3);

    // Write width ASCII
    std::string widthStr = std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write maximum value
    ofile.write("65535\n", 6);

    // Write pixel values
    unsigned short inputval;
    unsigned short *inputvalPtr = &inputval;
    char *v = reinterpret_cast<char*>(inputvalPtr);
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < image.width(); x++)
      {
        inputval = image.pixel(x,y,false)[0];
        ofile.write(v, 2); // NOT WORKING! Always 0
      }
    }

    ofile.close();

    return true;
  }

  /// Write 24-bit RGB image to file as PPM (Portable Pixel Map)
  ///
  /// \param[in] image Image
  /// \param[in] ppmPath Path to PPM file. Should have file extension *.ppm
  /// \return True on success, false otherwise
  static bool writeRgbImageAsPpm(const Image<unsigned char, 3> &image, const std::string &ppmPath)
  {
    std::ofstream ofile(ppmPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    ofile.write("P6\n", 3);

    // Write width ASCII
    std::string widthStr = std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write maximum value
    ofile.write("255\n", 4);

    // Write pixel values
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < image.width(); x++)
      {
        std::array<unsigned char, 3> pixel = image.pixel(x, y, false);
        char val[3] = { static_cast<char>(pixel[0]), static_cast<char>(pixel[1]), static_cast<char>(pixel[2]) };
        ofile.write(val, 3);
      }
    }

    ofile.close();

    return true;
  }

  /// Write 32-bit RGBA image to file as PPM (Portable Pixel Map)
  ///
  /// This file format does not natively support transparancy. The alpha channel
  /// is mitted.
  ///
  /// \param[in] image Image
  /// \param[in] ppmPath Path to PPM file. Should have file extension *.ppm
  /// \return True on success, false otherwise
  static bool writeRgbaImageAsPpm(const Image<unsigned char, 4> &image,
                                  const std::string &ppmPath)
  {
    std::ofstream ofile(ppmPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    ofile.write("P6\n", 3);

    // Write width ASCII
    std::string widthStr = std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write maximum value
    ofile.write("255\n", 4);

    // Write pixel values
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < image.width(); x++)
      {
        std::array<unsigned char, 4> pixel = image.pixel(x, y, false);
        char val[3] = { static_cast<char>(pixel[0]), static_cast<char>(pixel[1]), static_cast<char>(pixel[2]) };
        ofile.write(val, 3);
      }
    }

    ofile.close();

    return true;
  }

  /// Write 24-bit RGB image to file as PAM (Portable Arbitrary Map)
  ///
  /// \param[in] image Image
  /// \param[in] pamPath Path to PAM file. Should have file extension *.pam
  /// \return True on success, false otherwise
  static bool writeRgbImageAsPam(const Image<unsigned char, 3> &image, const std::string &pamPath)
  {
    std::ofstream ofile(pamPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    std::string magicNumberStr = "P7\n";
    ofile.write(magicNumberStr.c_str(), magicNumberStr.length());

    // Write width ASCII
    std::string widthStr = "WIDTH " + std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = "HEIGHT " + std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write depth
    std::string depthStr = "DEPTH 3\n";
    ofile.write(depthStr.c_str(), depthStr.length());

    // Write maximum value
    std::string maxValStr = "MAXVAL 255\n";
    ofile.write(maxValStr.c_str(), maxValStr.length());

    // Write tuple type
    std::string tupleTypeStr = "TUPLTYPE RGB\n";
    ofile.write(tupleTypeStr.c_str(), tupleTypeStr.length());

    // Write header end
    std::string headerEndStr = "ENDHDR\n";
    ofile.write(headerEndStr.c_str(), headerEndStr.length());

    // Write pixel values
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < image.width(); x++)
      {
        std::array<unsigned char, 3> pixel = image.pixel(x, y, false);
        char val[3] = { static_cast<char>(pixel[0]), static_cast<char>(pixel[1]), static_cast<char>(pixel[2]) };
        ofile.write(val, 3);
      }
    }

    ofile.close();

    return true;
  }

  /// Write 32-bit RGBA image to file as PAM (Portable Arbitrary Map)
  ///
  /// \param[in] image Image
  /// \param[in] pamPath Path to PAM file. Should have file extension *.pam
  /// \return True on success, false otherwise
  static bool writeRgbaImageAsPam(const Image<unsigned char, 4> &image, const std::string &pamPath)
  {
    std::ofstream ofile(pamPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    std::string magicNumberStr = "P7\n";
    ofile.write(magicNumberStr.c_str(), magicNumberStr.length());

    // Write width ASCII
    std::string widthStr = "WIDTH " + std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = "HEIGHT " + std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write depth
    std::string depthStr = "DEPTH 4\n";
    ofile.write(depthStr.c_str(), depthStr.length());

    // Write maximum value
    std::string maxValStr = "MAXVAL 255\n";
    ofile.write(maxValStr.c_str(), maxValStr.length());

    // Write tuple type
    std::string tupleTypeStr = "TUPLTYPE RGB\n";
    ofile.write(tupleTypeStr.c_str(), tupleTypeStr.length());

    // Write header end
    std::string headerEndStr = "ENDHDR\n";
    ofile.write(headerEndStr.c_str(), headerEndStr.length());

    // Write pixel values
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < image.width(); x++)
      {
        std::array<unsigned char, 4> pixel = image.pixel(x, y, false);
        char val[4] = { static_cast<char>(pixel[0]), static_cast<char>(pixel[1]), static_cast<char>(pixel[2]), static_cast<char>(pixel[3]) }; // \TODO Some nice pointer arithmetic
        ofile.write(val, 4);
      }
    }

    ofile.close();

    return true;
  }

protected:

private:
  // Disable object instantiation
  ImageIO() = delete;
};

} // namespace spatium

#endif // SPATIUMLIB_IMAGEIO_H
