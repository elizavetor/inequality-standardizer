#include "test_listtotree.h"

Test_listToTree::Test_listToTree(QObject *parent)
    : QObject{parent}
{}

void Test_listToTree::testListToTree()
{
    QFETCH(QList<OperandOfExpr>, list);
    QFETCH(NodeOfExprTree*, exp_tree);

    // Установыть связи внутри каждого элемента списка
    for(int i=0; i < list.size(); i++)
    {
        if (list[i].parent) list[i].parent->setRightOperand(list[i].operand);
    }

    // Установить связи между элементами списка
    NodeOfExprTree* real_tree = exp_tree->listToTree(list);

    // Сравнить полученное и ожидаемое деревья
    QStringList path;
    QString error;
    QVERIFY2(compareTrees(exp_tree, real_tree, path, error), error.toUtf8());
}
