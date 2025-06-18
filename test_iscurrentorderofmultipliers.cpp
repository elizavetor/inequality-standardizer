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

void Test_isCurrentOrderOfMultipliers::testIsCurrentOrderOfMultipliers_data()
{
    QTest::addColumn<OperandOfExpr>("elem_1");
    QTest::addColumn<OperandOfExpr>("elem_2");
    QTest::addColumn<bool>("exp_result");

    // 1. Проверка на правило: сначала числа, потом переменные, далее - выражения в скобках

    // Создать общего родителя для множителя : "*"
    NodeOfExprTree* parent = new NodeOfExprTree("*");

    // Создать указатель на операнд типа переменная
    NodeOfExprTree* operand_is_var = new NodeOfExprTree("variable");

    // Создать указатель на операнд типа число
    NodeOfExprTree* operand_is_num = new NodeOfExprTree("3");

    // Создать указатель на операнд типа выражения в скобках
    NodeOfExprTree* left_operand = new NodeOfExprTree("1");
    NodeOfExprTree* right_operand = new NodeOfExprTree("2");
    NodeOfExprTree* operand_is_expr = new NodeOfExprTree("+", left_operand, right_operand);

    // Создать сравниваемую структуру типа переменной
    OperandOfExpr var = OperandOfExpr{parent, operand_is_var, false};

    // Создать сравниваемую структуру типа число
    OperandOfExpr num = OperandOfExpr{parent, operand_is_num, false};

    // Создать сравниваемую струкуру типа выражения в скобках
    OperandOfExpr expr = OperandOfExpr{parent, operand_is_expr, false};

    // 1.1 Первый узел есть число, второй - переменная
    QTest::newRow("1.1 Correct order: number, variable, expression in parentheses. Order check: number, variable") << num << var << true;
}
