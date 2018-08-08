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

#ifdef __linux__
#undef minor
#endif

namespace Math {

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

  /// Constructor
  ///
  /// \param[in] array 2D Initializer list
  Matrix(std::initializer_list<std::initializer_list<double>> array)
    : m_rows(0)
    , m_cols(0)
    , m_data(0)
  {
    // Check dimensions
    m_rows = static_cast<unsigned>(array.size());
    m_cols = static_cast<unsigned>(array.begin()->size());
    if (m_rows == 0 || m_cols == 0)
    {
      m_rows = 0;
      m_cols = 0;
    }
    m_data.resize(m_rows * m_cols, 0);

    // Set values
    auto rowIt = array.begin();
    unsigned row = 0;
    while(rowIt != array.end() && row < m_rows)
    {
      auto colIt = rowIt->begin();
      unsigned col = 0;
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

  /// Compare operator. Is equal.
  ///
  /// \param[in] other Other matrix
  /// \exception std::out_of_range Matrix dimensions mismatch
  /// \return True if equal, otherwise false
  bool operator==(const Matrix &other) const
  {
    // Check bounds
    if (other.m_rows != m_rows || other.m_cols != m_cols)
    {
      throw std::out_of_range ("Matrix dimensions mismatch");
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
  /// \exception std::out_of_range Matrix dimensions mismatch
  /// \return True if unequal, otherwise false
  bool operator!=(const Matrix &other) const
  {
    return !(operator ==(other));
  }

  /// Destructor
  virtual ~Matrix() = default;

  /// Construct identity matrix.
  ///
  /// \return Identity matrix
  static Matrix identity(unsigned order)
  {
    Matrix result(order, order);
    for (unsigned i = 0; i < order; i++)
    {
      result(i,i) = 1;
    }
    return result;
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
        result(col, row) = operator()(row, col);
      }
    }
    return result;
  }

  /// Calculate determinant.
  /// The determinant is calculated through expansion by minors.
  ///
  /// \exception std::out_of_range Matrix is not square
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
  /// The minor is the determinant of the matrix formed by omitting a given
  /// row and column.
  ///
  /// \param[in] row Row to omit
  /// \param[out] col Column to omit
  /// \return Minor
  double minor(unsigned row, unsigned col) const
  {
    Matrix t = omit(row, col);
    return t.determinant();
  }

  /// Omit a given row and column.
  ///
  /// \param[in] row Row to omit
  /// \param[out] col Column to omit
  /// \return Matrix with omitted row and column
  Matrix omit(unsigned row, unsigned col) const
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
      throw std::out_of_range ("Matrix inverse calculation requires square matrix");
    }

    double det = determinant();
    if(det == 0)
    {
      throw std::out_of_range ("Matrix has no inverse (matrix is singular)");
    }

    unsigned order = m_rows;

    Matrix result(m_rows, m_cols);

    for(unsigned j = 0; j < order; j++)
    {
      for(unsigned i = 0; i < order; i++)
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
      throw std::out_of_range ("Matrix dimensions mismatch");
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
        double val = 0;
        for (unsigned k = 0; k < m_cols; k++)
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
    os << "Matrix(" << matrix.m_rows << ", " << matrix.m_cols << ")" << std::endl;
    for (unsigned row = 0; row < matrix.m_rows; row++)
    {
      for (unsigned col = 0; col < matrix.m_cols; col++)
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

    for(unsigned i = 0; i < matrix.cols(); i++ )
    {
      Matrix minor = matrix.omit(0, i);
      det += (i % 2 == 1 ? -1.0 : 1.0) * matrix(0, i) * determinant(minor);
    }

    return det;
  }

  unsigned m_rows;
  unsigned m_cols;
  std::vector<double> m_data;
};

} // namespace Math

#endif // MATRIX_H
