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

#ifndef SPATIUMLIB_IMAGE_H
#define SPATIUMLIB_IMAGE_H

#include <limits> // std::numeric_limits
#include <cstring> // std::memcpy, std::memset
#include <array> // std::array
#include <memory> // std::unique_ptr

namespace spatium {

// These conversion functions are embedded in structs because otherwise
// their call is ambiguous: same arguments, different return type

/// \brief Value of an image pixel with arbitrary data type and channel count
template<typename T, int N>
struct PixelValue
{
};

/// \brief Value of an image pixel with arbitrary data type and 1 channel
///
/// This struct can be used to convert a pixel value of 3 or 4 channels to a
/// 1-channel pixel value.
template<typename T>
struct PixelValue<T, 1>
{
  static std::array<T, 1> value(const std::array<T, 1> &input)
  {
    // No conversion
    return input;
  }

  // Convert 3 channel pixel value to 1 channel
  static std::array<T, 1> value(const std::array<T, 3> &input)
  {
    // Convert 3 channel RGB to 1 channel Grayscale
    return { input[0] * 0.2125 + input[1] * 0.7154 + input[2] * 0.0721 };
  }

  // Convert 4 channel pixel value to 1 channel
  static std::array<T, 1> pixelValue(const std::array<T, 4> &input)
  {
    // Convert 4 channel RGBA to grayscale by luminosity (BT.709) (Alpha is ignored)
    return { input[0] * 0.2125 + input[1] * 0.7154 + input[2] * 0.0721 };
  }
};

/// \brief Value of an image pixel with arbitrary data type and 3 channels
///
/// This struct can be used to convert a pixel value of 1 or 4 channels to a
/// 3-channel pixel value.
template<typename T>
struct PixelValue<T, 3>
{
  // Convert 1 channel pixel value to 3 channel
  static std::array<T, 3> pixelValue(const std::array<T, 1> &input)
  {
    // Convert 1 channel Grayscale to 3 channel RGB
    return { input[0], input[0], input[1] };
  }

  static std::array<T, 3> value(const std::array<T, 3> &input)
  {
    // No conversion
    return input;
  }

  // Convert a 4 channel pixel value to 3 channel
  static std::array<T, 3> pixelValue(const std::array<T, 4> &input)
  {
    // Convert 4 channel RGBA to 3 channel RGB (Alpha is ignored)
    return { input[0], input[1], input[2] };
  }
};

/// \brief Value of an image pixel with arbitrary data type and 4 channels
///
/// This struct can be used to convert a pixel value of 1 or 3 channels to a
/// 4-channel pixel value.
template<typename T>
struct PixelValue<T, 4>
{
  // Convert a 1 channel pixel value to 4 channel
  static std::array<T, 4> pixelValue(const std::array<T, 1> &input)
  {
    // Convert 1 channel Grayscale to 4 channel RGBA. (Alpha is full opaque)
    return { input[0], input[0], input[0], std::numeric_limits<T>::max() };
  }

  // Convert a 3 channel pixel value to 4 channel
  static std::array<T, 4> pixelValue(const std::array<T, 3> &input)
  {
    // Convert 3 channel RGB to 4 channel RGBA. (Alpha is full opaque)
    return { input[0], input[1], input[2], std::numeric_limits<T>::max() };
  }

  static std::array<T, 4> value(const std::array<T, 4> &input)
  {
    // No conversion
    return input;
  }
};

/// \class Image
/// \brief Templated image container
///
/// An image has no knowledge about color.
template<typename T=unsigned char, int N=3>
class Image
{
public:
  /// Constructor
  /// Constructs an image with a single pixel to ensure function pixel() can
  /// always return a reference to a value.
  ///
  /// \throw std::bad_alloc on bad allocation
  Image()
    : m_width(1)
    , m_height(1)
    , m_imageData(new std::array<T, N>[1])
  {
    // Clear value
    m_imageData[0] = {0};
  }

  /// Constructor
  ///
  /// \param[in] width Image width in pixels
  /// \param[in] height Image height in pixels
  /// \throw std::bad_alloc on bad allocation
  Image(int width, int height)
    : m_width(width)
    , m_height(height)
    , m_imageData(new std::array<T, N>[height * width])
  {
    // Clear values
    clear();
  }

  /// Copy constructor.
  /// Deep copy.
  ///
  /// \throw std::bad_alloc on bad allocation
  Image(const Image &other)
    : m_width(other.m_width)
    , m_height(other.m_height)
    , m_imageData(new std::array<T, N>[other.m_height * other.m_width])
  {
    // Iterate pixels
    for (size_t i = 0; i < m_height * m_width; i++)
    {
      std::array<T, N> &pixelFrom = other.m_imageData[i];
      std::array<T, N> &pixelTo = m_imageData[i];

      // Iterate channels
      for (size_t c = 0; c < N; c++)
      {
        // Copy value
        pixelTo[c] = pixelFrom[c];
      }
    }
  }

  /// Move constructor
  ///
  /// \throw std::bad_alloc on bad allocation
  Image(Image &&other)
    : m_width(1)
    , m_height(1)
    , m_imageData(new std::array<T, N>[1])
  {
    m_imageData[0] = {0};

    // Swap values
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_imageData, other.m_imageData);
  }

  /// Copy assignment operator
  /// Deep copy.
  ///
  /// \throw std::bad_alloc on bad allocation
  Image& operator=(const Image &other)
  {
    // Check for self-assignment
    if(&other == this)
    {
      return *this;
    }

    // Allocate new memory (may throw bad_alloc exception)
    std::unique_ptr<std::array<T, N>[]> newImageData(new std::array<T, N>[other.m_height * other.m_width]);

    // Swap pointers
    std::swap(m_imageData, newImageData);

    // Copy values
    m_width = other.m_width;
    m_height = other.m_height;

    // Iterate pixels
    for (size_t i = 0; i < m_height * m_width; i++)
    {
      std::array<T, N> &pixelFrom = other.m_imageData[i];
      std::array<T, N> &pixelTo = m_imageData[i];

      // Iterate channels
      for (size_t c = 0; c < N; c++)
      {
        // Copy value
        pixelTo[c] = pixelFrom[c];
      }
    }

    return *this;
  }

  /// Move assignment operator
  Image operator=(Image&& other)
  {
    // Check for self-assignment
    if(&other == this)
    {
      return *this;
    }

    // Reset this object
    m_width = 1;
    m_height = 1;
    m_imageData.reset(new std::array<T, N>[1]);

    // Swap values
    std::swap(m_width, other.m_width);
    std::swap(m_height, other.m_height);
    std::swap(m_imageData, other.m_imageData);

    return *this;
  }

  /// Destructor
  ~Image() = default;

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other image
  /// \return True if equal, otherwise false
  bool operator==(const Image &other) const
  {
    // Compare bounds
    if (other.m_height != m_height
      || other.m_width != m_width)
    {
      return false;
    }

    // Compare pixel-wise
    for (size_t i = 0; i < m_height * m_width; i++)
    {
      if (m_imageData[i] != other.m_imageData[i])
      {
        return false;
      }
    }

    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other image
  /// \return True if unequal, otherwise false
  bool operator!=(const Image &other) const
  {
    return !(operator ==(other));
  }

  /// Image width in pixels.
  int width() const
  {
    return m_width;
  }

  /// Image height in pixels.
  int height() const
  {
    return m_height;
  }

  /// Channel count of pixel values.
  int channelCount() const
  {
    return N;
  }

  /// Pointer to image data.
  std::array<T, N> *imageDataPtr() const
  {
    return m_imageData.get();
  }

  /// Resize image.
  /// This allocates new memory without copying pixel values.
  ///
  /// \param[in] width Image width in pixels
  /// \param[in] height Image height in pixels
  /// \throw std::bad_alloc on bad allocation
  void resize(int newWidth, int newHeight)
  {
    m_width = newWidth;
    m_height = newHeight;
    m_imageData.reset(new std::array<T,N>[m_height * m_width]);

    // Clear values
    clear();
  }

  /// Clear the image data (Set to zero)
  void clear()
  {
    // Iterate pixels
    for (size_t i = 0; i < m_height * m_width; i++)
    {
      std::array<T, N> &pixelTo = m_imageData[i];

      // Iterate channels
      for (size_t c = 0; c < N; c++)
      {
        // Clear value
        pixelTo[c] = 0;
      }
    }
  }

  /// Access pixel by value.
  /// The X and Y coordinate are clamped if they are out of bounds of the
  /// image resolution. Beware: this alters the X and Y coordinates.
  ///
  /// \param[in,out] x X coordinate
  /// \param[in,out] y Y coordinate
  /// \return Pixel value
  std::array<T, N> pixel(int &x, int &y) const
  {
    // Clamp coordinates
    x = (x < 0 ? 0 : (x >= m_width ? m_width-1 : x));
    y = (y < 0 ? 0 : (y >= m_height ? m_height-1 : y));

    // Return value
    return m_imageData[y * m_width + x];
  }

  /// Access pixel by reference.
  ///
  /// The X and Y coordinate are clamped if they are out of bounds of the
  /// image resolution. Beware: this alters the X and Y coordinates.
  ///
  /// \param[in,out] x X coordinate
  /// \param[in,out] y Y coordinate
  /// \return Pixel reference
  std::array<T, N>& pixel(int &x, int &y)
  {
    // Clamp coordinates
    x = (x < 0 ? 0 : (x >= m_width ? m_width-1 : x));
    y = (y < 0 ? 0 : (y >= m_height ? m_height-1 : y));

    // Return reference
    return m_imageData[y * m_width + x];
  }

  /// Access pixel by reference.
  ///
  /// \param[in,out] x X coordinate
  /// \param[in,out] y Y coordinate
  /// \return Pixel reference
  std::array<T, N>& pixel(const int &x, const int &y)
  {
    // Clamp coordinates
    int xClamp = (x < 0 ? 0 : (x >= m_width ? m_width-1 : x));
    int yClamp = (y < 0 ? 0 : (y >= m_height ? m_height-1 : y));

    // Return reference
    return m_imageData[yClamp * m_width + xClamp];
  }

protected:
  /// Image width in pixels.
  int m_width;

  /// Image height in pixels.
  int m_height;

  /// Pointer to image data.
  std::unique_ptr<std::array<T, N>[]> m_imageData;
};

} // namespace spatium

#endif // SPATIUMLIB_IMAGE_H
