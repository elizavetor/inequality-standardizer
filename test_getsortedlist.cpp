#include "test_getsortedlist.h"

Test_getSortedList::Test_getSortedList(QObject *parent)
    : QObject{parent}
{}

void Test_getSortedList::testGetSortedList()
{
    QFETCH(NodeOfExprTree*, root);
    QFETCH(QList<OperandOfExpr>, exp_list);

    // Получить результат
    QList<OperandOfExpr> real_list = root->getSortedList();

    // Сравнить полученный и ожидаемый списки
    QString error = compareListsOfNodes(exp_list, real_list);
    QVERIFY2(error.isEmpty(), qPrintable(error));
}

