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

#ifndef SPATIUMLIB_GFX2D_BEZIERCURVE_H
#define SPATIUMLIB_GFX2D_BEZIERCURVE_H

#include <spatium/Math.h> // binomialCoefficient

#include <vector> // vector
#include <array> // array
#include <ostream>

namespace spatium {
namespace gfx2d {

/// \class BezierCurve
/// \brief 2D Bezier curve
///
/// BezierCurve is a class to represent a parametric Bezier curve.
class BezierCurve
{
public:

  /// Constructor
  ///
  /// \param[in] points Anchor points (first and last point) and
  ///                   control points (intermediate). Min length = 2.
  BezierCurve(const std::vector<std::array<double, 2>> &points)
    : m_points(points)
  {
  }

  /// Get the points of the curve
  ///
  /// A curve should at least have 2 control points. The first and last
  /// control points (anchor points) are the starting point and end point of
  /// the line.
  /// \return Points
  std::vector<std::array<double,2>> points() const
  {
    return m_points;
  }

  /// Get the degree of the curve.
  ///
  /// The degree is the number of points - 1.
  /// A 1st degree curve (linear) has two points, a 2nd degree curve (cubic)
  /// has 3 points, a 3rd degree curve (cubic) has 4 points, etc,
  /// \return Degree
  int degree() const
  {
    return static_cast<int>(m_points.size()) - 1;
  }

  /// Evaluate bezier curve
  ///
  /// \param[in] t Parameter along curve. Range [0,1]
  /// \return Point coordinates (x,y)
  std::array<double, 2> evaluate(double t) const
  {
    const std::vector<std::array<double, 2>> &P = m_points;
    const int N = degree();

    // Check for at least two anchor points
    if (N < 1)
    {
      return {0,0};
    }

    double x = 0, y = 0;
    for(int i = 0; i <= N; i++)
    {
      x += binomialCoefficient(N, i) * pow(1 - t, N - i) * pow(t, i) * P[i][0];
      y += binomialCoefficient(N, i) * pow(1 - t, N - i) * pow(t, i) * P[i][1];
    }
    return {x, y};
  }

  /// Divide a bezier curve
  ///
  /// This will increase the degree of the curve without affecting the shape.
  /// The new control points are placed in between the existing
  /// control points
  ///
  /// \return Bezier curve with degree + 1
  BezierCurve divide() const
  {
    /// \todo This function doesn't work properly yet.
    /// Perhaps it should be recursive.
    std::vector<std::array<double, 2>> points;

    points.push_back(m_points.front());

    for (size_t i = 0; i < static_cast<size_t>(degree()); i++)
    {
      auto P0 = m_points[i];
      auto P1 = m_points[i+1];

      double x = (P0[0] + P1[0]) / 2; // P0[0] + (P1[0] - P0[0])*0.5;
      double y = (P0[1] + P1[1]) / 2; // P0[1] + (P1[1] - P0[1])*0.5;

      points.push_back({x, y});
    }

    points.push_back(m_points.back());

    return BezierCurve(points);
  }

  /// Output to ostream
  friend std::ostream &operator<<(std::ostream &os, const BezierCurve &curve)
  {
    os << "BezierCurve ";
    for (auto point : curve.m_points)
    {
      os << "(" << point[0] << ", " << point[1] << ") ";
    }
    return os;
  }

private:
  std::vector<std::array<double, 2>> m_points;
};

} // namespace gfx2d
} // namespace spatium

#endif // SPATIUMLIB_GFX2D_BEZIERCURVE_H
