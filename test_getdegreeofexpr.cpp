#include "test_getdegreeofexpr.h"

Test_getDegreeOfExpr::Test_getDegreeOfExpr(QObject *parent)
    : QObject{parent}
{}

void Test_getDegreeOfExpr::testGetDegreeOfExpr()
{
    QFETCH(NodeOfExprTree*, expr);
    QFETCH(int, exp_degree);

    // Получить результат сравнения
    int real_degree = expr->getDegreeOfExpr();

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_degree, exp_degree);
}
