#include "test_operatorgt.h"

Test_operatorGt::Test_operatorGt(QObject *parent)
    : QObject{parent}
{}

void Test_operatorGt::testOperatorGt()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить дерево
    bool real_result = elem_1 > elem_2;

    // Сравнить полученные ошибки с ожидаемыми
    QCOMPARE(real_result, exp_result);
}

