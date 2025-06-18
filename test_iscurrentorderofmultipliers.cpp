#include "test_iscurrentorderofmultipliers.h"

void Test_isCurrentOrderOfMultipliers::testIsCurrentOrderOfMultipliers()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить результат сравнения
    bool real_result = elem_1.isCurrentOrderOfMultipliers(elem_2);

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_result, exp_result);
}
