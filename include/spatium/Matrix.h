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

#ifndef SPATIUMLIB_MATRIX_H
#define SPATIUMLIB_MATRIX_H

#include <vector>
#include <initializer_list>
#include <stdexcept> // std::out_of_range
#include <ostream>

#ifdef __linux__
#undef minor
#endif

namespace spatium {

/// \class Matrix
/// \brief Mathematical matrix with an arbitrary number number of rows and
/// columns
///
/// Matrix is a class to represent a mathematical matrix, i.e. a 2D array
/// defined by a number of rows and columns. The content of the matrix is
/// stored in column-major format.
class Matrix
{
public:
  /// Constructor
  ///
  /// \param[in] rows Number of rows
  /// \param[in] cols Number of columns
  Matrix(size_t rows, size_t cols)
    : m_rows(rows)
    , m_cols(cols)
    , m_data(m_rows * m_cols, 0)
  {
  }

  /// Constructor
  ///
  /// \param[in] array 2D Initializer list
  Matrix(std::initializer_list<std::initializer_list<double>> array)
    : m_rows(0)
    , m_cols(0)
    , m_data(0)
  {
    // Check dimensions
    m_rows = array.size();
    m_cols = array.begin()->size();
    if (m_rows == 0 || m_cols == 0)
    {
      m_rows = 0;
      m_cols = 0;
    }
    m_data.resize(m_rows * m_cols, 0);

    // Set values
    auto rowIt = array.begin();
    size_t row = 0;
    while(rowIt != array.end() && row < m_rows)
    {
      auto colIt = rowIt->begin();
      size_t col = 0;
      while(colIt != rowIt->end() && col < m_cols)
      {
        operator()(row, col) = *colIt;

        ++colIt;
        ++col;
      }

      ++rowIt;
      ++row;
    }
  }

  /// Compare operator. Is equal.
  ///
  /// Equal matrices have equal dimensions and values.
  ///
  /// \param[in] other Other matrix
  /// \return True if equal, otherwise false
  bool operator==(const Matrix &other) const
  {
    // Check bounds
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
      return false;
    }

    // Compare elements
    for (size_t i = 0; i < m_data.size(); i++)
    {
      if (m_data[i] != other.m_data[i])
      {
        return false;
      }
    }

    return true;
  }

  /// Compare operator. Is unequal.
  ///
  /// \param[in] other Other matrix
  /// \return True if unequal, otherwise false
  bool operator!=(const Matrix &other) const
  {
    return !(operator ==(other));
  }

  /// Construct identity matrix.
  ///
  /// \return Identity matrix
  static Matrix identity(size_t order)
  {
    Matrix result(order, order);
    for (size_t i = 0; i < order; i++)
    {
      result(i,i) = 1;
    }
    return result;
  }

  /// Get the number of rows.
  ///
  /// \return Number of rows
  size_t rows() const
  {
    return m_rows;
  }

  /// Get the number of columns.
  ///
  /// \return Number of columns
  size_t cols() const
  {
    return m_cols;
  }

  /// Get all matrix elements.
  ///
  /// \return All matrix elements
  std::vector<double> data() const
  {
    return m_data;
  }

  /// Clear all matrix elements.
  void clear()
  {
    std::fill(m_data.begin(), m_data.end(), 0);
  }

  /// Get transposed matrix.
  ///
  /// \return Transposed matrix
  Matrix transposed() const
  {
    Matrix result(m_cols, m_rows);
    for (size_t row = 0; row < m_rows; row++)
    {
      for (size_t col = 0; col < m_cols; col++)
      {
        result(col, row) = operator()(row, col);
      }
    }
    return result;
  }

  /// Calculate determinant.
  ///
  /// The determinant is calculated through expansion by minors.
  ///
  /// \throw std::out_of_range Matrix is not square
  /// \return Determinant
  double determinant() const
  {
    if(m_rows != m_cols)
    {
      throw std::out_of_range ("Matrix determinant calculation requires square matrix");
    }
    return determinant(*this);
  }

  /// Calulcate minor
  ///
  /// The minor is the determinant of the matrix formed by omitting a given
  /// row and column.
  ///
  /// \param[in] row Row to omit
  /// \param[out] col Column to omit
  /// \return Minor
  double minor(size_t row, size_t col) const
  {
    Matrix t = omit(row, col);
    return t.determinant();
  }

  /// Omit a given row and column.
  ///
  /// \param[in] row Row to omit
  /// \param[out] col Column to omit
  /// \return Matrix with omitted row and column
  Matrix omit(size_t row, size_t col) const
  {
    Matrix result(m_rows-1, m_cols-1);
    size_t colCount = 0, rowCount = 0;

    for(size_t i = 0; i < m_rows; i++)
    {
      if(i != row )
      {
        colCount = 0;
        for(size_t j = 0; j < m_cols; j++)
        {
          if(j != col)
          {
            result(rowCount, colCount) = operator()(i,j);
            colCount++;
          }
        }
        rowCount++;
      }
    }

    return result;
  }

  /// Calculate inverse of matrix.
  ///
  /// \throw std::out_of_range Matrix is not square
  /// \throw std::out_of_range Matrix has no inverse
  /// \return Inverse of matrix
  Matrix inverse() const
  {
    if(m_rows != m_cols)
    {
      throw std::out_of_range ("Matrix inverse calculation requires square matrix");
    }

    double det = determinant();
    if(det == 0)
    {
      throw std::out_of_range ("Matrix has no inverse (matrix is singular)");
    }

    size_t order = m_rows;

    Matrix result(m_rows, m_cols);

    for(size_t j = 0; j < order; j++)
    {
      for(size_t i = 0; i < order; i++)
      {
        Matrix minor = this->omit(j,i);

        double r = determinant(minor) / det;
        result(i,j) = r;
        if( (i + j) % 2 == 1)
        {
          result(i,j) = -result(i,j);
        }
      }
    }
    return result;
  }

  // Operators

  /// Access element by value.
  ///
  /// \param[in] row Row of element
  /// \param[in] col Column of element
  /// \throw std::out_of_range Matrix element out of range
  /// \return Element value
  double operator() (size_t row, size_t col) const
  {
    if (row >= m_rows || col >= m_cols)
    {
      throw std::out_of_range ("Matrix element index out of range");
    }
    return m_data[m_cols * row + col];
  }

  /// Access element by reference.
  ///
  /// \param[in] row Row of element
  /// \param[in] col Column of element
  /// \throw std::out_of_range Matrix element out of range
  /// \return Element reference
  double& operator() (size_t row, size_t col)
  {
    if (row >= m_rows || col >= m_cols)
    {
      throw std::out_of_range ("Matrix element index out of range");
    }
    return m_data[m_cols * row + col];
  }

  /// Add by matrix.
  ///
  /// \param[in] other Matrix to add
  /// \throw std::out_of_range Matrix dimensions mismatch
  /// \return Added matrix
  Matrix operator+(const Matrix &other) const
  {
    // Check matrix dimensions
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
      throw std::out_of_range ("Matrix dimensions mismatch");
    }

    // Add
    Matrix result(m_rows, m_cols);
    for (size_t row = 0; row < m_rows; row++)
    {
      for (size_t col = 0; col < m_cols; col++)
      {
        result(row,col) = operator()(row,col) + other(row,col);
      }
    }
    return result;
  }

  /// Subtract by matrix.
  ///
  /// \param[in] other Matrix to subtract
  /// \throw std::out_of_range Matrix dimensions mismatch
  /// \return Subtracted matrix
  Matrix operator-(const Matrix &other) const
  {
    // Check matrix dimensions
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
      throw std::out_of_range ("Matrix dimensions mismatch");
    }

    // Subtract
    Matrix result(m_rows, m_cols);
    for (size_t row = 0; row < m_rows; row++)
    {
      for (size_t col = 0; col < m_cols; col++)
      {
        result(row,col) = operator()(row,col) - other(row,col);
      }
    }
    return result;
  }

  /// Multiply by matrix.
  ///
  /// \param[in] other Matrix to multiply with
  /// \throw std::out_of_range Matrix dimensions mismatch
  /// \return Multiplied matrix
  Matrix operator*(const Matrix &other) const
  {
    // Check column and row count
    if (m_cols != other.m_rows)
    {
      throw std::out_of_range ("Matrix column count mismatch with row count of other matrix");
    }

    // Multiply
    Matrix result(m_rows, other.m_cols);
    for (size_t i = 0; i < m_rows; i++)
    {
      for (size_t j = 0; j < other.m_cols; j++)
      {
        double val = 0;
        for (size_t k = 0; k < m_cols; k++)
        {
          val += operator()(i,k) * other(k,j);
        }
        result(i,j) = val;
      }
    }
    return result;
  }

  /// Multiply by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Multiplied matrix
  Matrix operator*(double scalar) const
  {
    // Multiply
    Matrix result(m_rows, m_cols);
    for (size_t row = 0; row < m_rows; row++)
    {
      for (size_t col = 0; col < m_cols; col++)
      {
        result(row,col) += operator()(row,col) * scalar;
      }
    }
    return result;
  }

  /// Divide by scalar.
  ///
  /// \param[in] scalar Scalar
  /// \return Divided matrix
  Matrix operator/(double scalar) const
  {
    // Divide
    Matrix result(m_rows, m_cols);
    for (size_t row = 0; row < m_rows; row++)
    {
      for (size_t col = 0; col < m_cols; col++)
      {
        result(row,col) += operator()(row,col) / scalar;
      }
    }
    return result;
  }

  // Other functions

  /// Resize.
  ///
  /// This will set all values to 0.
  ///
  /// \param[in] rows Number of rows
  /// \param[in] cols Number of columns
  void resize(size_t rows, size_t cols)
  {
    m_rows = rows;
    m_cols = cols;
    m_data.resize(m_rows * m_cols, 0);
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
  {
    os << "Matrix(" << matrix.m_rows << ", " << matrix.m_cols << ")" << std::endl;
    for (size_t row = 0; row < matrix.m_rows; row++)
    {
      for (size_t col = 0; col < matrix.m_cols; col++)
      {
        os << matrix(row, col) << " ";
      }
      if (row < matrix.m_rows - 1) {
        os << std::endl;
      }
    }
    return os;
  }

protected:
  /// Calculate determinant.
  ///
  /// Recursive function.
  ///
  /// \return Determinant
  double determinant(const Matrix &matrix) const
  {
    if(matrix.rows() == 1)
    {
      return matrix(0, 0);
    }

    double det = 0;

    for(size_t i = 0; i < matrix.cols(); i++ )
    {
      Matrix minor = matrix.omit(0, i);
      det += (i % 2 == 1 ? -1.0 : 1.0) * matrix(0, i) * determinant(minor);
    }

    return det;
  }

  size_t m_rows;
  size_t m_cols;
  std::vector<double> m_data;
};

} // namespace spatium

#endif // SPATIUMLIB_MATRIX_H
