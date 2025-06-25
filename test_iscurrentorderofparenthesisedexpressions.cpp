#include "test_iscurrentorderofparenthesisedexpressions.h"

Test_isCurrentOrderOfParenthesisedExpressions::Test_isCurrentOrderOfParenthesisedExpressions(
    QObject *parent)
    : QObject{parent}
{}

void Test_isCurrentOrderOfParenthesisedExpressions::testIsCurrentOrderOfParenthesisedExpressions()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить результат сравнения
    bool real_result = elem_1.isCurrentOrderOfMultipliers(elem_2);

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_result, exp_result);
}

