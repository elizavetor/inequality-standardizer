#include "test_getlistofnodesofsameprecedencelevel.h"

Test_getListOfNodesOfSamePrecedenceLevel::Test_getListOfNodesOfSamePrecedenceLevel(QObject *parent)
    : QObject{parent}
{}

void Test_getListOfNodesOfSamePrecedenceLevel::testGetListOfNodesOfSamePrecedenceLevel()
{
    QFETCH(NodeOfExprTree*, root);
    QFETCH(QList<OperandOfExpr>, exp_list);

    // Получить результат
    QList<OperandOfExpr> real_list = root->getListOfNodesOfSamePrecedenceLevel();

    // Сравнить полученный и ожидаемый списки
    QString error = compareListsOfNodes(exp_list, real_list);
    QVERIFY2(error.isEmpty(), qPrintable(error));

}

