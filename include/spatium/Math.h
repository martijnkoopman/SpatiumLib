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

#ifndef SPATIUMLIB_MATH_H
#define SPATIUMLIB_MATH_H

#include <cmath>  // std::atan cbrt()
#include <utility> // std:swap
#include <limits> // numeric_limits

namespace spatium {

/// Pi constant
const double PI = std::atan(1) * 4;
const double Rad2Deg = 180 / PI;
const double Deg2Rad = PI / 180;

/// Calculate the factorial
/// Example: factorial(4) = 4! = 4*3*2*1 = 24
///
/// \param[in] n A positive integer
/// \return Factorial
inline double factorial(int n)
{
  double result = 1;
  for (int i = n; i > 1; i--)
  {
    result *= i;
  }
  return result;
}

/// Calculate the binomial coefficient.
/// Combinatorics: Choose a subset of K elements from a fixed set of N elements
/// 'N choose K'
///
/// \param[in] n Number of elements in fixed set
/// \param[in] k Number of elements to choose
/// \return Binomial coefficient
inline double binomialCoefficient(int n, int k)
{
  return factorial(n) / (factorial(k) * factorial(n-k));
}

/// Solve a quadratic equation: ax^2 + bx + c = 0
///
/// \param[in] a First coefficient
/// \param[in] b Second coefficient
/// \param[in] c Third coefficient
/// \param[out] x1 First solution (if exists). Lowest value
/// \param[out] x2 Second solution (if exists). Highest value
/// \return Number of unique solutions 0, 1 or 2
inline int solveQuadratic(double a, double b, double c, double &x1, double &x2)
{
  // Compute discriminant
  double D = (b * b) - (4 * a * c);
  if (D < 0)
  {
    return 0;
  }

  // Calculate x's
  x1 = (-b - sqrt(D)) / (2 * a);
  x2 = (-b + sqrt(D)) / (2 * a);

  // Swap if necessary
  if (x1 > x2)
  {
    std::swap(x1, x2);
  }

  // Return number of solutions
  if (D > 0)
  {
    return 2;
  }
  else // D == 0
  {
    return 1;
  }
}

/// Solve a qubic equation: ax^3 + bx^2 + cx + d =0
///
/// \param[in] a First coefficient
/// \param[in] b Second coefficient
/// \param[in] c Third coefficient
/// \param[in] d Fourth coefficient
/// \param[out] x1 First solution (if exists). Lowest value
/// \param[out] x2 Second solution (if exists).
/// \param[out] x3 Third solution (if exists). Highest value
/// \return Number of solutions 1, 2 or 3
inline int solveCubic(double a, double b, double c, double d, double &x1, double &x2, double &x3)
{
  // http://www2.trinity.unimelb.edu.au/~rbroekst/MathX/Cubic%20Formula.pdf
  // https://en.wikibooks.org/wiki/Trigonometry/The_solution_of_cubic_equations

  // Make a = 1. Then omit d
  if (a != 1)
  {
    b /= a;
    c /= a;
    d /= a;
  }
  a = b; b = c; c = d; d = 0;

  double p = b - ((a*a) / 3);
  double q = ((2*(a*a*a)) / 27) - ((a*b) / 3) + c;
  //double D = ((q*q) / 4) + ((p*p*p) / 27);

  double Q = (3*b - a*a) / 9;
  double R = (9*a*b - 27*c - 2*a*a*a) / 54;
  double D = Q*Q*Q + R*R;

  if (D < std::numeric_limits<double>::epsilon()
      && D > -std::numeric_limits<double>::epsilon()) // D == 0
  {
    // There are TWO real solutions
    x1 = -2*cbrt(q/2) - (a/3);
    x2 = cbrt(q/2) - (a/3);

    // Reorder results
    if (x1 > x2)
    {
      std::swap(x1, x2);
    }
    x3 = x2;

    return 2;
  }
  else if (D > 0)
  {
    // There is ONE real solution
    x1 = x2 = x3 = cbrt(-1*(q/2) + sqrt(D)) + cbrt(-1*(q/2) - sqrt(D)) - (a/3);

    return 1;
  }
  else if(D < 0)
  {
    // There are THREE real solution

    // Solve with trigonometry
    double theta = acos(R/sqrt(-(Q*Q*Q)));
    x1 = 2 * sqrt(-Q) * cos(theta / 3) - (a/3);
    x2 = 2 * sqrt(-Q) * cos(theta / 3 + (2*PI/3)) - (a/3);
    x3 = 2 * sqrt(-Q) * cos(theta / 3 + (4*PI/3)) - (a/3);

    // Reorder results
    if (x1 > x2)
    {
      std::swap(x1, x2);
    }
    if (x1 > x3)
    {
      std::swap(x1, x3);
    }
    if (x2 > x3)
    {
      std::swap(x2, x3);
    }

    return 3;
  }
}

} // namespace spatium

#endif // SPATIUMLIB_MATH_H
