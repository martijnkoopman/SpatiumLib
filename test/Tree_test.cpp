#include <QtTest>

#include <spatium/idx/Tree.h>
#include <spatium/idx/TreeIterator.h>
#include <spatium/idx/StringTree.h>
#include <spatium/idx/Quadtree.h>

#include <stack> // std::stack

using namespace spatium;

class Tree_test : public QObject
{
  Q_OBJECT

public:
  Tree_test();
  ~Tree_test();

private slots:

  void test_customTree();
  void test_stringTree();
  void test_quadtreeFromPoints();

private:
};

Tree_test::Tree_test()
{

}

Tree_test::~Tree_test()
{

}

// Functions

void Tree_test::test_customTree()
{
  idx::Tree<std::string> tree("abc");
  std::shared_ptr<idx::TreeNode<std::string>> root = tree.root();

  // Change node string value
  QCOMPARE(root->object(), "abc");
  root->setObject("root");
  QCOMPARE(root->object(), "root");

  // Add children to root node
  auto root_0 = root->addChild(root, "root-0");
  root->addChild(root, "root-1");
  root->addChild(root, "root-2");
  auto root_3 = root->addChild(root, "root-3");

  // Add children to root-0
  root_0->addChild(root_0, "root-0-0");
  root_0->addChild(root_0, "root-0-1");
  root_0->addChild(root_0, "root-0-2");
  root_0->addChild(root_0, "root-0-3");

  // Add children to root-3
  root_3->addChild(root_3, "root-3-0");
  root_3->addChild(root_3, "root-3-1");
  root_3->addChild(root_3, "root-3-2");
  auto root_3_3 = root_3->addChild(root_3, "root-3-3");

  // Add children to root-3-3
  root_3_3->addChild(root_3_3, "root-3-3-0");
  root_3_3->addChild(root_3_3, "root-3-3-1");
  root_3_3->addChild(root_3_3, "root-3-3-2");
  root_3_3->addChild(root_3_3, "root-3-3-3");

  std::string depthFirstString = "";
  for (idx::TreeIterator<std::string> it = tree.begin(); it != tree.end(); ++it)
  {
    std::shared_ptr<idx::TreeNode<std::string>> node = *it;

    //std::shared_ptr<idx::StringTreeNode> node = *it;
    depthFirstString += node->object() + ";";
  }

  QCOMPARE(depthFirstString, "root;root-0;root-0-0;root-0-1;root-0-2;root-0-3;root-1;root-2;root-3;root-3-0;root-3-1;root-3-2;root-3-3;root-3-3-0;root-3-3-1;root-3-3-2;root-3-3-3;");
}

void Tree_test::test_stringTree()
{
  // Create initial string tree with 1 root node
  idx::StringTree tree("abc");

  // Get root node
  std::shared_ptr<idx::StringTreeNode> root = std::static_pointer_cast<idx::StringTreeNode>(tree.root());

  // Change node string value
  QCOMPARE(root->str(), "abc");
  root->setString("root");
  QCOMPARE(root->str(), "root");

  // Add children to root node
  auto root_0 = root->addChild(root, "root-0");
  root->addChild(root, "root-1");
  root->addChild(root, "root-2");
  auto root_3 = root->addChild(root, "root-3");

  // Add children to root-0
  root_0->addChild(root_0, "root-0-0");
  root_0->addChild(root_0, "root-0-1");
  root_0->addChild(root_0, "root-0-2");
  root_0->addChild(root_0, "root-0-3");

  // Add children to root-3
  root_3->addChild(root_3, "root-3-0");
  root_3->addChild(root_3, "root-3-1");
  root_3->addChild(root_3, "root-3-2");
  auto root_3_3 = root_3->addChild(root_3, "root-3-3");

  // Add children to root-3-3
  root_3_3->addChild(root_3_3, "root-3-3-0");
  root_3_3->addChild(root_3_3, "root-3-3-1");
  root_3_3->addChild(root_3_3, "root-3-3-2");
  root_3_3->addChild(root_3_3, "root-3-3-3");

  // Check

  std::string depthFirstString = "";

  // Traverse tree depth-first (using stack)
  std::stack<std::shared_ptr<idx::StringTreeNode>> stacky;
  stacky.push(std::static_pointer_cast<idx::StringTreeNode>(tree.root()));
  while (!stacky.empty())
  {
    // Pop top element from stack
    std::shared_ptr<idx::StringTreeNode> node = stacky.top();
    stacky.pop();

    depthFirstString += node->str() + ";";

    // Iterate children
    if (node->hasChildren())
    {
      for (size_t i = 0; i < node->childCount(); i++)
      {
        auto n = std::static_pointer_cast<idx::StringTreeNode>(node->child(node->childCount()-1-i));
        stacky.push(n);
      }
    }
  }

  QCOMPARE(depthFirstString, "root;root-0;root-0-0;root-0-1;root-0-2;root-0-3;root-1;root-2;root-3;root-3-0;root-3-1;root-3-2;root-3-3;root-3-3-0;root-3-3-1;root-3-3-2;root-3-3-3;");

  depthFirstString = "";
  for (idx::TreeIterator<std::string> it = tree.begin(); it != tree.end(); ++it)
  {
    std::shared_ptr<idx::StringTreeNode> node = std::static_pointer_cast<idx::StringTreeNode>(*it);
    depthFirstString += node->str() + ";";
  }

  QCOMPARE(depthFirstString, "root;root-0;root-0-0;root-0-1;root-0-2;root-0-3;root-1;root-2;root-3;root-3-0;root-3-1;root-3-2;root-3-3;root-3-3-0;root-3-3-1;root-3-3-2;root-3-3-3;");
}

void Tree_test::test_quadtreeFromPoints()
{
  std::vector<std::array<double, 2>> points = { {0,0}, {10,10}, {8.5,8.5}, {8.5,9.5}, {9.5,8.5}, {4,1}, {9,4} };

  // Construct tree
  auto tree = idx::PointQuadtree::buildFromPoints(points, 1);

  // Check bounds
  auto bounds = tree.bounds();
  QCOMPARE(bounds.min()[0], 0);
  QCOMPARE(bounds.min()[1], 0);
  QCOMPARE(bounds.max()[0], 10);
  QCOMPARE(bounds.max()[1], 10);

  // Check max point count in leaf node
  QCOMPARE(tree.maxPointCountLeaf(), 1);

  // Check point count
  size_t pointCount = 0;
  for (idx::TreeIterator<std::vector<std::array<double,2>>> it = tree.begin(); it != tree.end(); ++it)
  {
    std::shared_ptr<idx::PointQuadtreeNode> node = std::static_pointer_cast<idx::PointQuadtreeNode>(*it);
    std::vector<std::array<double,2>> &p = node->object();
    pointCount += p.size();
  }
  QCOMPARE(pointCount, 7);
}

QTEST_APPLESS_MAIN(Tree_test)

#include "Tree_test.moc"
