#include "test_getnodesofsameprecedencewithparenthesesopening.h"

Test_getNodesOfSamePrecedenceWithParenthesesOpening::
    Test_getNodesOfSamePrecedenceWithParenthesesOpening(QObject *parent)
    : QObject{parent}
{}

void Test_getNodesOfSamePrecedenceWithParenthesesOpening::testGetNodesOfSamePrecedenceWithParenthesesOpening()
{
    QFETCH(NodeOfExprTree*, root);
    QFETCH(bool, is_invert);
    QFETCH(QList<OperandOfExpr>, exp_list);

    // Получить результат
    QList<OperandOfExpr> real_list = root->getNodesOfSamePrecedenceWithParenthesesOpening(is_invert);

    // Сравнить полученный и ожидаемый списки
    QString error = compareListsOfNodes(exp_list, real_list);
    QVERIFY2(error.isEmpty(), qPrintable(error));

}

