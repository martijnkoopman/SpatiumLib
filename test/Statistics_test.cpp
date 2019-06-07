#include <QtTest>

#include <spatium/stats.h>
#include <spatium/geom2d.h>

using namespace spatium;

class Statistics_test : public QObject
{
  Q_OBJECT

public:
  Statistics_test();
  ~Statistics_test();

private slots:

  void test_mean();
  void test_stdDev();
  void test_variance();
  void test_covariance();
  void test_eigenDecomposition2();
  void test_eigenDecompositionPoints();

private:
};

Statistics_test::Statistics_test()
{

}

Statistics_test::~Statistics_test()
{

}

// Functions

void Statistics_test::test_mean()
{
  std::vector<double> vec({2,4,4,4,5,5,7,9});
  double m = stats::mean(vec);
  QCOMPARE(m, 5);
}

void Statistics_test::test_variance()
{
  std::vector<double> vec({2,4,4,4,5,5,7,9});
  double var = stats::variance(vec);
  QCOMPARE(var, 4);
}

void Statistics_test::test_stdDev()
{
  std::vector<double> vec({2,4,4,4,5,5,7,9});
  double sd = stats::stdDev(vec);
  QCOMPARE(sd, 2);
}

void Statistics_test::test_covariance()
{
  // Input vectors
  std::vector<double> x({1, 6, 3, 4, 4, 2, 5, 3, 2, 5});
  std::vector<double> y({1, 4, 2, 3, 2, 2, 3, 3, 1, 4});

  // Check mean
  double x_mean = stats::mean(x);
  double y_mean = stats::mean(y);

  QCOMPARE(x_mean, 3.5);
  QCOMPARE(y_mean, 2.5);

  // Check variance
  double x_variance = stats::variance(x);
  double y_variance = stats::variance(y);

  QCOMPARE(x_variance, 2.25);
  QCOMPARE(y_variance, 1.05);

  // Covariance as two vectors
  double covPopulaton = stats::covariance(x,y);
  double covSample = stats::covariance(x,y,true);

  QCOMPARE(covPopulaton, 1.35);
  QCOMPARE(covSample, 1.50);

  // Construct input matrix with two columns
  Matrix m(10,2);
  for (size_t i = 0; i < m.rows(); i++)
  {
    m(i,0) = x[i];
    m(i,1) = y[i];
  }

  // Covariance as matrix with two columns
  Matrix covMatrix = stats::covariance(m);

  QCOMPARE(covMatrix.rows(), 2);
  QCOMPARE(covMatrix.cols(), 2);

  QCOMPARE(covMatrix(0,0), x_variance);
  QCOMPARE(covMatrix(0,1), covPopulaton);
  QCOMPARE(covMatrix(1,0), covPopulaton);
  QCOMPARE(covMatrix(1,1), y_variance);
}

void Statistics_test::test_eigenDecomposition2()
{
  // Test 1
  Matrix A = {{7,  3},
              {3, -1}};

  // Compute eigenvalues
  double eigval1, eigval2;
  QVERIFY(stats::eigenvalues2(A, eigval1, eigval2));

  QCOMPARE(eigval1, -2);
  QCOMPARE(eigval2, 8);

  // Compute first corresponding eigenvector
  std::vector<double> eigvec(2);
  stats::eigenvector2(A, eigval1, eigvec);

  // Validate paralell
  geom2d::Vector2 eigvec2(eigvec[0], eigvec[1]);
  geom2d::Vector2 checkvec2(-1, 3);

  QCOMPARE(abs(eigvec2.dot(checkvec2)), eigvec2.length()*checkvec2.length());

  // Compute second corresponding eigenvector
  stats::eigenvector2(A, eigval2, eigvec);

  // Validate paralell
  eigvec2 = { eigvec[0], eigvec[1] };
  checkvec2 = { 3, 1 };
  QCOMPARE(abs(eigvec2.dot(checkvec2)), eigvec2.length()*checkvec2.length());

  // Test 2
  A = {{ 0,  1},
       {-2, -3}};

  QVERIFY(stats::eigenvalues2(A, eigval1, eigval2));

  QCOMPARE(eigval1, -2);
  QCOMPARE(eigval2, -1);
}

void Statistics_test::test_eigenDecompositionPoints()
{
  Matrix m({ {1,1}, {6,4}, {3,2}, {4,3}, {4,2}, {2,2}, {5,3}, {3,3}, {2,1}, {5,4} });

  // Check input matrix
  QCOMPARE(m.rows(), 10);
  QCOMPARE(m.cols(), 2);

  // Compute covariance matrix
  Matrix covMatrix = stats::covariance(m);

  // Check covariance matrix values
  QCOMPARE(covMatrix(0,0), 2.25);
  QCOMPARE(covMatrix(0,1), 1.35);
  QCOMPARE(covMatrix(1,0), 1.35);
  QCOMPARE(covMatrix(1,1), 1.05);

  // Compute eigenvalues
  double eigval1, eigval2;
  QVERIFY(stats::eigenvalues2(covMatrix, eigval1, eigval2));

  QCOMPARE(eigval1, 0.1726713297305844);
  QCOMPARE(eigval2, 3.1273286702694154);

  // Compute corresponding eigenvectors
  std::vector<double> eigvec1(2), eigvec2(2);
  stats::eigenvector2(covMatrix, eigval1, eigvec1);
  stats::eigenvector2(covMatrix, eigval2, eigvec2);

  QCOMPARE(eigvec1[0], 1.35);
  QCOMPARE(eigvec1[1], -2.077328670269416);

  QCOMPARE(eigvec2[0], 1.35);
  QCOMPARE(eigvec2[1], 0.8773286702694154);
}

QTEST_APPLESS_MAIN(Statistics_test)

#include "Statistics_test.moc"
