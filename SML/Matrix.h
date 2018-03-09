/*
 * Program: Spatial Math Library
 *
 * Copyright (C) Martijn Koopman
 * All Rights Reserved
 *
 * This software is distributed WITHOUT ANY WARRANTY; without even
 * the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.
 *
 */

#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

namespace SML {

/// \brief Matrix
class Matrix
{
public:
  /// Constructor
  ///
  /// \param[in] rows Number of rows
  /// \param[in] cols Number of columns
  Matrix(unsigned rows, unsigned cols)
    : m_rows(rows)
    , m_cols(cols)
    , m_data(m_rows * m_cols, 0)
  {
  }

  /// Copy constructor
  Matrix(const Matrix &other)
    : m_rows(other.m_rows)
    , m_cols(other.m_cols)
    , m_data(m_rows * m_cols)
  {
    std::copy(other.m_data.begin(), other.m_data.end(), m_data.begin());
  }

  /// Assignment operator
  Matrix& operator=(Matrix other)
  {
    // Exception safe assignment operator
    std::swap(m_rows, other.m_rows);
    std::swap(m_cols, other.m_cols);
    std::swap(m_data, other.m_data);
    return *this;
  }

  /// Destructor
  virtual ~Matrix()
  {
  }

  /// Get the number of rows.
  ///
  /// \return Number of rows
  unsigned rows() const
  {
    return m_rows;
  }

  /// Get the number of columns.
  ///
  /// \return Number of columns
  unsigned cols() const
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
    for (unsigned row = 0; row < m_rows; row++)
    {
      for (unsigned col = 0; col < m_cols; col++)
      {
        result(row, col) = operator()(col, row);
      }
    }
    return result;
  }

  /// Calculate determinant.
  ///
  /// \exception std::out_of_range Matrix is not square
  /// \return Determinant
  double determinant() const
  {
    if(m_rows != m_cols)
    {
      throw std::out_of_range ("Matrix determinant calculation requires sqaure matrix");
    }
    return determinant(*this);
  }

  Matrix minor(unsigned row, unsigned col) const
  {
    Matrix result(m_rows-1, m_cols-1);
    unsigned colCount = 0, rowCount = 0;

    for(unsigned i = 0; i < m_rows; i++)
    {
      if(i != row )
      {
        colCount = 0;
        for(unsigned j = 0; j < m_cols; j++)
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
  /// \exception std::out_of_range Matrix is not square
  /// \exception std::out_of_range Matrix has no inverse
  /// \return Inverse of matrix
  Matrix inverse() const
  {
    if(m_rows != m_cols)
    {
      throw std::out_of_range ("Matrix inverse calculation requires sqaure matrix");
    }
    if(determinant() == 0)
    {
      throw std::out_of_range ("Matrix has no inverse");
    }

    unsigned order = m_rows;

    Matrix result(m_rows, m_cols);
    double det = 1.0 / determinant();

    for(unsigned j = 0; j < order; j++)
    {
      for(unsigned i = 0; i < order; i++)
      {
        Matrix minor = this->minor(j,i);

        result(i,j) = det * determinant(minor);
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
  /// \exception std::out_of_range Matrix element out of range
  /// \return Element value
  double operator() (unsigned row, unsigned col) const
  {
    if (row >= m_rows || col >= m_cols)
    {
      throw std::out_of_range ("Matrix element out of range");
    }
    return m_data[m_cols * row + col];
  }

  /// Access element by reference.
  ///
  /// \param[in] row Row of element
  /// \param[in] col Column of element
  /// \exception std::out_of_range Matrix element out of range
  /// \return Element reference
  double& operator() (unsigned row, unsigned col)
  {
    if (row >= m_rows || col >= m_cols)
    {
      throw std::out_of_range ("Matrix element out of range");
    }
    return m_data[m_cols * row + col];
  }

  /// Add with matrix.
  ///
  /// \param[in] other Matrix to add
  /// \exception std::out_of_range Matrix element out of range
  /// \return Added matrix
  Matrix operator+(const Matrix &other) const
  {
    // Check bounds
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
      throw std::out_of_range ("Matrix element out of range");
    }

    // Add
    Matrix result(m_rows, m_cols);
    for (unsigned row = 0; row < m_rows; row++)
    {
      for (unsigned col = 0; col < m_cols; col++)
      {
        result(row,col) = operator()(row,col) + other(row,col);
      }
    }
    return result;
  }

  /// Subtract by matrix.
  ///
  /// \param[in] other Matrix to subtract
  /// \exception std::out_of_range Matrix element out of range
  /// \return Subtracted matrix
  Matrix operator-(const Matrix &other) const
  {
    // Check bounds
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
      throw std::out_of_range ("Matrix element out of range");
    }

    // Subtract
    Matrix result(m_rows, m_cols);
    for (unsigned row = 0; row < m_rows; row++)
    {
      for (unsigned col = 0; col < m_cols; col++)
      {
        result(row,col) = operator()(row,col) - other(row,col);
      }
    }
    return result;
  }

  /// Multiply by matrix.
  ///
  /// \param[in] other Matrix to multiply with
  /// \exception std::out_of_range Matrix dimensions mismatch
  /// \return Multiplied matrix
  Matrix operator*(const Matrix &other) const
  {
    // Check bounds
    if (m_cols != other.m_rows)
    {
      throw std::out_of_range ("Matrix multiplication requires matrices with equal sized rows and columns");
    }

    // Multiply
    Matrix result(m_rows, other.m_cols);
    for (unsigned i = 0; i < m_rows; i++)
    {
      for (unsigned j = 0; j < other.m_cols; j++)
      {
        for (unsigned k = 0; k < m_rows; k++)
        {
          result(i,j) += operator()(i,k) * other(k,j);
        }
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
    for (unsigned row = 0; row < m_rows; row++)
    {
      for (unsigned col = 0; col < m_cols; col++)
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
    for (unsigned row = 0; row < m_rows; row++)
    {
      for (unsigned col = 0; col < m_cols; col++)
      {
        result(row,col) += operator()(row,col) / scalar;
      }
    }
    return result;
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const Matrix &matrix)
  {
    os << "Matrix(" << matrix.m_rows << ", " << matrix.m_cols << ")\n";
    for (unsigned row = 0; row < matrix.m_rows; row++)
    {
      for (unsigned col = 0; col < matrix.m_cols; col++)
      {
        os << matrix(row, col) << " ";
      }
      os << "\n";
    }
    return os;
  }

protected:

  /// Calculate determinant.
  /// Recursive.
  ///
  /// \return Determinant
  double determinant(const Matrix &matrix) const
  {
    if(matrix.rows() == 1)
    {
      return matrix(0, 0);
    }

    double det = 0;

    for(unsigned i = 0; i < matrix.cols(); i++ )
    {
      Matrix minor = matrix.minor(0, i);
      det += (i % 2 == 1 ? -1.0 : 1.0) * matrix(0, i) * determinant(minor);
    }

    return det;
  }

  unsigned m_rows;
  unsigned m_cols;
  std::vector<double> m_data;
};

} // namespace SML

#endif // MATRIX_H
