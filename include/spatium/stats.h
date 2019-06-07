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

#ifndef SPATIUM_STATS_H
#define SPATIUM_STATS_H

#include "Math.h" // solveQuadratic()
#include "Matrix.h"

#include <vector> // std::vector

namespace spatium {
namespace stats {

/// Compute mean value.
///
/// \param[in] values Values vector
/// \return Mean value
inline double mean(const std::vector<double> &values)
{
  double result = 0;

  const size_t count = values.size();
  const double divider = static_cast<double>(1) / static_cast<double>(count);
  for (size_t i = 0; i < count; i++)
  {
    result += values[i] * divider;
  }

  return result;
}

/// Compute the variance.
///
/// \param[in] values Values vector
/// \param[in] sample Sample variance if true, population if false (default)
/// \return Variance
inline double variance(const std::vector<double> &values, bool sample = false)
{
  double result = 0;
  const double m = mean(values);
  const size_t count = values.size();
  const double divider = static_cast<double>(1) / (sample ? static_cast<double>(count) - 1 : static_cast<double>(count));
  for (size_t i = 0; i < count; i++)
  {
    const double diff = values[i] - m;
    result += (diff * diff) * divider;
  }
  return result;
}

/// Compute the standard deviation.
///
/// \param[in] values Values vector
/// \param[in] sample Sample standard deviation if true, population if false
///                   (default)
/// \return Standard deviation
inline double stdDev(const std::vector<double> &values, bool sample = false)
{
  return sqrt(variance(values, sample));
}

/// Compute the covariance.
///
/// \param[in] values1 Values vector 1
/// \param[in] values2 Values vector 2
/// \param[in] sample Sample covariance if true, population if false (default)
/// \return Covariance
inline double covariance(const std::vector<double> &values1, const std::vector<double> &values2, bool sample = false)
{
  if (values1.size() != values2.size())
  {
    return 0;
  }

  double result = 0;
  const double m1 = mean(values1);
  const double m2 = mean(values2);
  const size_t count = values1.size();
  const double divider = static_cast<double>(1) / (sample ? static_cast<double>(count) - 1 : static_cast<double>(count));
  for (size_t i = 0; i < count; i++)
  {
    result += ((values1[i] - m1) * (values2[i] - m2)) * divider;
  }
  return result;
}

/// Compute the covariance matrix
inline Matrix covariance(const Matrix &values)
{
  const size_t inputRows = values.rows();
  const size_t outputSize = values.cols();
  Matrix result(outputSize, outputSize);

  for (size_t i = 0; i < outputSize; i++)
  {
    // Extract column 1 at i
    std::vector<double> column1(inputRows);
    for(size_t k = 0; k < inputRows; k++)
    {
      column1[k] = values(k,i);
    }

    for (size_t j = 0; j < outputSize; j++)
    {
      if (i == j)
      {
        // Covariance with itself. Variance
        result(i, j) = variance(column1);
      }
      else
      {
        // Covariance with other column
        // Extract column 2 at j
        std::vector<double> column2(inputRows);
        for(size_t l = 0; l < inputRows; l++)
        {
          column2[l] = values(l,j);
        }

        // Compute covariance
        result(i, j) = covariance(column1, column2);
      }
    }
  }

  return result;
}

/// Compute eigenvalues for 2-by-2 matrix.
///
/// \param[in] matrix 2-by-2 matrix
/// \param[out] eigenval1 Eigenvalue 1
/// \param[out] eigenval2 Eigenvalue 2
/// \return Number of unique solutions 0, 1 or 2
inline int eigenvalues2(const Matrix &matrix, double &eigenval1, double &eigenval2)
{
  // Check 2-by-2 matrix
  if (matrix.rows() != 2 || matrix.cols() != 2)
  {
    return 0;
  }

  const double p = matrix(0,0);
  const double q = matrix(0,1);
  const double r = matrix(1,0);
  const double s = matrix(1,1);

  return solveQuadratic(1, -1 * (p + s), p*s - q*r, eigenval1, eigenval2);
}

/// Compute the eigenvector of a 2-by-2 matrix for a given eigenvalue.
///
/// Beware. There are two solution vectors pointing in opposite direction.
/// Either is correct. Also the length of the vector may vary. You should
/// normalize the result vector.
///
/// \param[in] matrix 2-by-2 matrix
/// \param[in] eigenval Eigenvalue
/// \param[out] eigenvec Eigenvector
/// \return True on success, false if matrix is not 2-by-2.
inline bool eigenvector2(const Matrix &matrix, double eigenval, std::vector<double> &eigenvec)
{
  // Check 2-by-2 matrix
  if (matrix.rows() != 2 || matrix.cols() != 2)
  {
    return false;
  }

  // Check 2 rows vector
  if (eigenvec.size() != 2)
  {
    eigenvec.resize(2);
  }

  eigenvec[0] = matrix(0,1);
  eigenvec[1] = eigenval - matrix(0,0);

  // Other solution:
  // eigenvec(0) = eigenval - matrix(1,1);
  // eigenvec(1) = matrix(1,0);

  return true;
}

} // namespace statistics
} // namespace spatium

#endif // SPATIUM_STATS_H
