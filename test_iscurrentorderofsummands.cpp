#include "test_iscurrentorderofsummands.h"

Test_isCurrentOrderOfSummands::Test_isCurrentOrderOfSummands(QObject *parent)
    : QObject{parent}
{}

void Test_isCurrentOrderOfSummands::testIsCurrentOrderOfSummands()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить результат сравнения
    bool real_result = elem_1.isCurrentOrderOfMultipliers(elem_2);

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_result, exp_result);
}

