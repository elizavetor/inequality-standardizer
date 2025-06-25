#include "test_treetoinfix.h"

Test_treeToInfix::Test_treeToInfix(QObject *parent)
    : QObject{parent}
{}

void Test_treeToInfix::testTreeToInfix()
{
    QFETCH(NodeOfExprTree*, tree);
    QFETCH(QString, exp_infix);

    // Получить инфиксную запись дерева
    QString real_infix = tree->treeToInfix();

    // Сравнить полученную строку с ожидаемой
    QCOMPARE(real_infix, exp_infix);
}
