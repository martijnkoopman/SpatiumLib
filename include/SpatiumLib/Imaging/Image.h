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

/// \class Image
/// \brief Templated image container
///
/// An image has no knowledge about color.
template<typename T=unsigned char, int N=3>
class Image
{
public:
  /// Constructor
  ///
  /// Empty image.
  explicit Image()
  : m_width(0)
  , m_height(0)
  , m_imageData(nullptr)
  {
  }

  /// Constructor
  ///
  /// \param[in] width Image width in pixels
  /// \param[in] height Image height in pixels
  /// \throw std::bad_alloc on bad allocation
  explicit Image(int width, int height)
  : m_width(width)
  , m_height(height)
  , m_imageData(nullptr)
  {
    // Allocate memory for image pixels
    // May throw std::bad_alloc exception
    m_imageData.reset(new T[m_height * m_width * N]());
  }

  /// Copy constructor.
  /// \throw std::bad_alloc on bad allocation
  explicit Image(const Image &other)
  : m_width(other.m_width)
  , m_height(other.m_height)
  , m_imageData(new T[other.m_height * other.m_width * N]())
  {
    std::memcpy(m_imageData.get(),
                other.m_imageData.get(),
                other.m_height * other.m_width * N);
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

    // Allocate new memory (may throw bad_alloc exception)
    m_imageData.reset(new T[other.m_height * other.m_width * N]());

    // Copy values
    m_width = other.m_width;
    m_height = other.m_height;
    std::memcpy(m_imageData.get(),
                other.m_imageData.get(),
                other.m_height * other.m_width * N);

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
      || other.m_width != m_width)
    {
      return false;
    }

    // Compare byte-wise
    for (size_t i = 0; i < m_height * m_width * N; i++)
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

  int channelCount() const
  {
    return N;
  }

  /// Pointer to image data.
  /// The
  T *imageDataPtr() const
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
    m_imageData.reset(new T[m_height * m_width * N]());
  }

  /// Clear the image data (Set to zero)
  void clear()
  {
    std::memset(m_imageData.get(), 0, m_height * m_width * N);
  }

  /// Set pixel value.
  bool setPixel(int x, int y, std::array<T, N> value)
  {
    // Check bounds
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
      return false;
    }

    // Copy array to pixel value
    const int index = y * m_width * N + (x * N);
    for (int i = 0; i < N; i++)
    {
      m_imageData.get()[index + i] = value[i];
    }

    return true;
  }

  /// Get pixel value
  std::array<T, N> getPixel(int x, int y) const
  {
    std::array<T, N> result = {};

    // Check bounds
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
    {
      return result;
    }

    // Copy pixel value to array
    const int index = y * m_width * N + (x * N);
    for (int i = 0; i < N; i++)
    {
      result[i] = m_imageData.get()[index + i];
    }

    return result;
  }

protected:
  /// Image width in pixels.
  int m_width;

  /// Image height in pixels.
  int m_height;

  /// Pointer to image data.
  std::shared_ptr<T> m_imageData;
};

} // namespace Imaging

#endif // SPATIUMLIB_IMAGE_H
