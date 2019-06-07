#include <QtTest>

#include <spatium/idx.h>

#include <stack> // std::stack
#include <tuple>

using namespace spatium;

class Tree_test : public QObject
{
  Q_OBJECT

public:
  Tree_test();
  ~Tree_test();

private slots:

  void test_quadtreeFromPoints();

private:
};

Tree_test::Tree_test()
{

}

Tree_test::~Tree_test()
{

}

// Constructors

void Tree_test::test_quadtreeFromPoints()
{
  std::vector<std::array<double, 2>> points = { {0,0}, {10,10}, {8.5,8.5}, {8.5,9.5}, {9.5,8.5} };

  auto tree = idx::PointQuadtree::buildFromPoints(points, 1);

//  //idx::Tree<std::array<double,2>>::
//  for (idx::TreeIterator<std::array<double, 2>> it = tree.beginDepthFirst() ; it != tree.endDepthFirst(); ++it)
//  {
//    std::cout << ' ' << *it;
//  }

  //int depth = tree.computeDepth();

  // Traverse tree depth-first (using stack)
  // Depth, index (0-3), node
  std::stack<std::tuple<int, int, std::shared_ptr<idx::PointQuadtreeNode>>> stacky;
  stacky.push(std::make_tuple(0,0, std::static_pointer_cast<idx::PointQuadtreeNode>(tree.root())));
  while (!stacky.empty())
  {
    // Pop top element from stack
    std::tuple<int, int, std::shared_ptr<idx::PointQuadtreeNode>> s = stacky.top();
    stacky.pop();

    int depth = std::get<0>(s);
    int index = std::get<1>(s);
    std::shared_ptr<idx::PointQuadtreeNode> node = std::get<2>(s);

    //std::cout << node->str() << std::endl;

    // Iterate 4 children
    if (node->hasChildren())
    {
      for (size_t i = 0; i < 4; i++)
      {
        auto n = std::static_pointer_cast<idx::PointQuadtreeNode>(node->child(i));
        stacky.push(std::make_tuple(depth+1,i, n));
      }
    }
  }

  QCOMPARE(1, 1);
}



QTEST_APPLESS_MAIN(Tree_test)

#include "Tree_test.moc"
