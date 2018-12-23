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

#include <cstring> // memcpy, memset
#include <memory> // shared_ptr

namespace Imaging {

struct Color24bppRgb
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
};

struct Color32bppRgb
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char unused;
};

struct Color32bppRgba
{
  unsigned char red;
  unsigned char green;
  unsigned char blue;
  unsigned char alpha;
};

/// \class Image
/// \brief Low-level image container
class Image
{
public:

  enum Format
  {
    Format_RGB24,
    Format_RGB32,
    Format_RGBA32,
    Format_Grayscale8,
  };

  static size_t FormatByteCount(Format format)
  {
    switch(format)
    {
    case Format_Grayscale8:
        return 1;
    case Format_RGB24:
        return 3;
    case Format_RGB32:
    case Format_RGBA32:
      return 4;
    default:
        return 0;
    }
  }

  /// Constructor
  ///
  /// Empty image. Assignment required.
  Image()
  : m_width(0)
  , m_height(0)
  , m_format(Format_RGB24)
  , m_byteCount(0)
  , m_imageData(nullptr)
  {
  }

  /// Constructor
  ///
  /// \param[in] width Image width in pixels
  /// \param[in] height Image height in pixels
  /// \param[in] pixelFormat Image pixel format
  /// \throw std::bad_alloc on bad allocation
  Image(int width, int height, Format pixelFormat)
  : m_width(width)
  , m_height(height)
  , m_format(pixelFormat)
  , m_byteCount(width * height * FormatByteCount(pixelFormat))
  , m_imageData(nullptr)
  {
    // Allocate memory for image pixels
    // May throw std::bad_alloc exception
    m_imageData.reset(new unsigned char[m_byteCount]);
  }

  /// Copy constructor.
  /// \throw std::bad_alloc on bad allocation
  Image(const Image &other)
  : m_width(other.m_width)
  , m_height(other.m_height)
  , m_format(other.m_format)
  , m_byteCount(other.m_byteCount)
  , m_imageData(new unsigned char[other.m_byteCount])
  {
    std::memcpy(m_imageData.get(), other.m_imageData.get(), m_byteCount);
  }

  /// Destructor
  virtual ~Image() = default;

  /// Assignment operator
  /// \throw std::bad_alloc on bad allocation
  Image& operator=(const Image &other)
  {
    // Check for self-assignment
    if(&other == this)
    {
      return *this;
    }

    // Copy values
    m_width = other.m_width;
    m_height = other.m_height;
    m_format = other.m_format;
    m_byteCount = other.m_byteCount;
    // Allocate new memory (may throw bad_alloc exception)
    m_imageData.reset(new unsigned char[other.m_byteCount]);
    std::memcpy(m_imageData.get(), other.m_imageData.get(), m_byteCount);

    return *this;
  }

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other image
  /// \return True if equal, otherwise false
  bool operator==(const Image &other) const
  {
    // Check bounds
    if (other.m_height != m_height
      || other.m_width != m_width
      || other.m_format != m_format
      || other.m_byteCount != m_byteCount)
    {
      return false;
    }

    // Compare byte-wise
    for (size_t i = 0; i < m_byteCount; i++)
    {
      if (m_imageData.get()[i] != other.m_imageData.get()[i])
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

  /// Image pixel format.
  Format format() const
  {
    return m_format;
  }

  /// Pointer to image data.
  unsigned char *imageData() const
  {
    return m_imageData.get();
  }

  /// Clear the image data (Set to zero)
  void clear()
  {
    std::memset(m_imageData.get(), 0, m_byteCount);
  }

protected:
  /// Image width in pixels.
  int m_width;

  /// Image height in pixels.
  int m_height;

  /// Image pixel format.
  Format m_format;

  /// Image data size in bytes.
  size_t m_byteCount;

  /// Pointer to image data.
  std::shared_ptr<unsigned char> m_imageData;
};

} // namespace Imaging

#endif // SPATIUMLIB_IMAGE_H
