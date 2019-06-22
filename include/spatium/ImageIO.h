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

#include <fstream> // std::ofstream, std::ifstream
#include <cctype> // std::isspace
#include <string> // std::stol

namespace spatium {

/// \class ImageIO
/// \brief Read and write images
///
/// This class supports 4 file formats:
///
/// - Portable Bit Map (PBM) for binary images (values 0 and 1).
///   - http://netpbm.sourceforge.net/doc/pbm.html
/// - Portable Gray Map (PGM) for 8-bit and 16-bit grayscale images.
///   - http://netpbm.sourceforge.net/doc/ppm.html
/// - Portable Pixel Map (PPM) for 24-bit and 48-bit RGB images.
///   - http://netpbm.sourceforge.net/doc/ppm.html
/// - Portable Arbitrary Map (PAM) for arbitrary images (binary, RGB, RGBA, etc).
///   - http://netpbm.sourceforge.net/doc/pam.html
///   - Although this file format supports many pixel formats, it is not widely
/// supported. Consider using the other 3 file formats when possisble. Only use
/// this format if you require transparancy (alpha channel).
///
/// Beware! These functions have not been tested on endianness; big-endian vs
/// little-endian.
class ImageIO
{
public:
  /// Write binary image to file as PBM (Portable Bit Map).
  ///
  /// In this file each pixel is represented by 1 bit. In the Image object
  /// each pixel is represented by 1 byte.
  ///
  /// \param[in] image Image
  /// \param[in] pbmPath Path to PBM file. Should have file extension *.pbm
  /// \return True on success, false otherwise
  static bool writeBinaryImageAsPbm(const Image<unsigned char, 1> &image, const std::string &pbmPath)
  {
    std::ofstream ofile(pbmPath, std::ios::out | std::ios::binary);
    if (!ofile.is_open())
    {
      return false;
    }

    // Write magic number ASCII
    ofile.write("P4\n", 3);

    // Write width ASCII
    std::string widthStr = std::to_string(image.width()) + "\n";
    ofile.write(widthStr.c_str(), widthStr.length());

    // Write height as ASCII
    std::string heightStr = std::to_string(image.height()) + "\n";
    ofile.write(heightStr.c_str(), heightStr.length());

    // Write pixel values
    const size_t width = image.width();
    for (size_t y = 0; y < image.height(); y++)
    {
      for (size_t x = 0; x < width; x += 8)
      {
        // Construct byte
        unsigned char val = 0x00; // inverted (black = 0)
        for (unsigned char i = 0; (i < 8 && x + i < width); i++)
        {
          unsigned char shift = 7 - i;
          unsigned char pixel = (image.pixel(x+i,y,false)[0] == 0 ? 0x00 : 0x01); // inverted (white = 1)
          unsigned char mask = static_cast<unsigned char>(pixel << shift);
          val |= mask;
        }
        val = ~val; // invert as needed (black = 1, white = 0)

        // Write byte
        ofile.write(reinterpret_cast<char*>(&val), 1);
      }
    }

    return  true;
  }

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

    return true;
  }

  /// Write 32-bit RGBA image to file as PPM (Portable Pixel Map)
  ///
  /// This file format does not support transparancy. The alpha channel is
  /// omitted. Use PAM instead.
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
        char val[3] = { static_cast<char>(pixel[0]),
                        static_cast<char>(pixel[1]),
                        static_cast<char>(pixel[2]) };
        ofile.write(val, 3);
      }
    }

    return true;
  }

  /// Write 24-bit RGB image to file as PAM (Portable Arbitrary Map)
  ///
  /// \param[in] image Image
  /// \param[in] pamPath Path to PAM file. Should have file extension *.pam
  /// \return True on success, false otherwise
  static bool writeRgbImageAsPam(const Image<unsigned char, 3> &image,
                                 const std::string &pamPath)
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
        char val[3] = { static_cast<char>(pixel[0]),
                        static_cast<char>(pixel[1]),
                        static_cast<char>(pixel[2]) };
        ofile.write(val, 3);
      }
    }

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
        char val[4] = { static_cast<char>(pixel[0]),
                        static_cast<char>(pixel[1]),
                        static_cast<char>(pixel[2]),
                        static_cast<char>(pixel[3]) };
        ofile.write(val, 4);
      }
    }

    return true;
  }

  /// Read 1-bit binary image from PBM file (Portable Bit Map).
  ///
  /// \param[in] pbmPath Path to PBM file. Should have file extension *.pbm
  /// \param[out] image Image
  /// \return True on success, false otherwise
  static bool readBinaryImageFromPbm(const std::string &pbmPath, Image<unsigned char, 1> &image)
  {
    // Minimal file content:
    //P4\n        (magic number + whitespace; 3 bytes)
    //1 1\n       (width height whitespaces; 4 bytes)
    //0x01        (binary: bits; 1 byte) (1 = black, 0 = white)

    // Optional content:
    //# Comments with spaces.\n (comment ending with \n)

    // Open file
    std::ifstream ifile(pbmPath, std::ios::in | std::ios::binary);
    if (!ifile.is_open())
    {
      return false;
    }

    // Check file size
    ifile.seekg (0, ifile.end);
    long size = ifile.tellg();
    ifile.seekg (0, ifile.beg);
    if (size < 8)
    {
      return false;
    }

    // Read header
    size_t width = 1, height = 1;
    unsigned long maxVal = 0;
    if (!readPnmFileHeader(ifile, "P4", width, height, maxVal))
    {
      return false;
    }

    // Resize output image
    image.resize(width, height);

    // Pass last whitespace
    ifile.seekg(1, ifile.cur);

    // Read pixels
    //std::unique_ptr<unsigned char> pixel(new unsigned char);
    unsigned char pixel;
    for (size_t y = 0; y < height; y++)
    {
      for (size_t x = 0; x < width; x += 8)
      {
        // Read byte
        ifile.read(reinterpret_cast<char*>(&pixel), 1);

        // Iterate bits
        for (unsigned char i = 0; (i < 8 && x + i < width); i++)
        {
          // Extract value
          unsigned char shift = 7 - i;
          unsigned char mask = static_cast<unsigned char>(0x01 << shift);
          unsigned char value = ((pixel & mask) > 0 ? 0 : 255);

          // Set pixel value
          image.pixel(x+i, y, false) = { value };
        }
      }
    }

    return true;
  }

  /// Read 8-bit grayscale image from PGM file (Portable Gray Map)
  ///
  /// Beware! This file format also supports 16-bit grayscale format (2 bytes
  /// per channel). This is not implemented and function will return false in
  /// that situation.
  ///
  /// \param[in] pgmPath Path to PGM file. Should have file extension *.pgm
  /// \param[out] image Image
  /// \return True on success, false otherwise
  static bool readGrayscaleImageFromPgm(const std::string &pgmPath, Image<unsigned char, 1> &image)
  {
    // Minimal file content:
    //P5\n        (magic number + whitespace; 3 bytes)
    //1 1\n       (width height whitespaces; 4 bytes)
    //1\n         (max value + whitespace; 2 bytes)
    //0x11        (binary: gray; 1 byte)

    // Optional content:
    //# Comments with spaces.\n (comment ending with \n)

    std::ifstream ifile(pgmPath, std::ios::in | std::ios::binary);
    if (!ifile.is_open())
    {
      return false;
    }

    // Check file size
    ifile.seekg (0, ifile.end);
    long size = ifile.tellg();
    ifile.seekg (0, ifile.beg);
    if (size < 10)
    {
      return false;
    }

    // Read header
    size_t width = 1, height = 1;
    unsigned long maxVal = 255;
    if (!readPnmFileHeader(ifile, "P5", width, height, maxVal))
    {
      return false;
    }

    // Check max value
    if (maxVal > 255)
    {
      return false;
    }

    // Resize output image
    image.resize(width, height);

    // Pass last whitespace
    ifile.seekg(1, ifile.cur);

    // Read pixels
    std::unique_ptr<unsigned char> pixel(new unsigned char);
    for (size_t y = 0; y < height; y++)
    {
      for (size_t x = 0; x < width; x++)
      {
        ifile.read(reinterpret_cast<char*>(pixel.get()), 1);
        image.pixel(x,y) = { *(pixel.get()) };
      }
    }

    return true;
  }

  /// Read 24-bit RGB image from PPM file (Portable Pixel Map)
  ///
  /// Beware! This file format also supports 48-bit RGB format (2 bytes per
  /// channel). This is not implemented and function will return false in that
  /// situation.
  ///
  /// \param[in] ppmPath Path to PPM file. Should have file extension *.ppm
  /// \param[out] image Image
  /// \return True on success, false otherwise
  static bool readRgbImageFromPpm(const std::string &ppmPath, Image<unsigned char, 3> &image)
  {
    // Minimal file content:
    //P6\n        (magic number + whitespace; 3 bytes)
    //1 1\n       (width height whitespaces; 4 bytes)
    //1\n         (max value + whitespace; 2 bytes)
    //0x001122    (binary: red green, blue; 3 bytes)

    // Optional content:
    //# Comments with spaces.\n (comment ending with \n)

    std::ifstream ifile(ppmPath, std::ios::in | std::ios::binary);
    if (!ifile.is_open())
    {
      return false;
    }

    // Check file size
    ifile.seekg (0, ifile.end);
    long size = ifile.tellg();
    ifile.seekg (0, ifile.beg);
    if (size < 12)
    {
      return false;
    }

    // Read header
    size_t width = 1, height = 1;
    unsigned long maxVal = 255;
    if (!readPnmFileHeader(ifile, "P6", width, height, maxVal))
    {
      return false;
    }

    // Check max value
    if (maxVal > 255)
    {
      return false;
    }

    // Resize output image
    image.resize(width, height);

    // Pass last whitespace
    ifile.seekg(1, ifile.cur);

    // Read pixels
    std::unique_ptr<std::array<unsigned char, 3>> pixel(new std::array<unsigned char, 3>());
    for (size_t y = 0; y < height; y++)
    {
      for (size_t x = 0; x < width; x++)
      {
        ifile.read(reinterpret_cast<char*>(pixel->data()), 3);// pixel.get(), 3);
        image.pixel(x,y) = *(pixel.get());
      }
    }

    return true;
  }

protected:
  /// Read header of a PNM file (PBM, PGM or PPM)
  ///
  /// \param[in] ifile Input file stream
  /// \param[in] magicNumber Expected magic number
  /// \param[out] width Image width
  /// \param[out] height Image height
  /// \param[out] maxVal Maximum pixel value (ignored for PBM images)
  /// \return True on success, false otherwise
  static bool readPnmFileHeader(std::ifstream &ifile, std::string magicNumber, size_t &width, size_t &height, unsigned long &maxVal)
  {
    // Read magic number
    std::string line;
    ifile >> line;
    if (line != magicNumber)
    {
      return false;
    }

    // Read next token and skip any comments
    ifile >> line;
    while (line.find("#") == 0)
    {
      std::getline(ifile, line);
      ifile >> line;
    }

    // Parse width
    try
    {
      width = std::stoul(line);
    }
    catch (std::exception e)
    {
      return false;
    }

    // Read next token and skip any comments
    ifile >> line;
    while (line.find("#") == 0)
    {
      std::getline(ifile, line);
      ifile >> line;
    }

    // Parse height
    try
    {
      height = std::stoul(line);
    }
    catch (std::exception e)
    {
      return false;
    }

    if (magicNumber == "P4")
    {
      // Binaryt image header has no max value
      maxVal = 1;
    }
    else // P5, P6
    {
      // Read next token and skip any comments
      ifile >> line;
      while (line.find("#") == 0)
      {
        std::getline(ifile, line);
        ifile >> line;
      }

      // Parse max value
      try
      {
        maxVal = std::stoul(line); // should be unsigned short (max val < 65536)
      }
      catch (std::exception e)
      {
        return false;
      }
    }

    return true;
  }

private:
  // Disable object instantiation
  ImageIO() = delete;
};

} // namespace spatium

#endif // SPATIUMLIB_IMAGEIO_H
