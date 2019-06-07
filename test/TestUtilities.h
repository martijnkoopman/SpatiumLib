#include <spatium/Matrix.h>
#include <QtGlobal>

using namespace spatium;

class TestUtilities
{
public:

  static bool fuzzyCompareMatrix(const Matrix &m1, const Matrix &m2)
  {
    if (m1.cols() != m2.cols() || m1.rows() != m2.rows())
    {
      return false;
    }

    for (size_t row = 0; row < m1.rows(); row++)
    {
      for (size_t col = 0; col < m1.cols(); col++)
      {
        const double val1 = m1(row,col);
        const double val2 = m2(row,col);

        if (qFuzzyIsNull(val1))
        {
          if (!qFuzzyIsNull(val2))
          {
            return false;
          }
        }
        else if (qFuzzyIsNull(val2))
        {
          if (!qFuzzyIsNull(val1))
          {
            return false;
          }
        }
        else if (!qFuzzyCompare(val1, val2))
        {
          return false;
        }
      }
    }

    return true;
  }

private:
  TestUtilities() = delete;
};
