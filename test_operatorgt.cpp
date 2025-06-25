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

void Test_operatorGt::testOperatorGt_data()
{
    // Добавить столбцы
    QTest::addColumn<OperandOfExpr>("elem_1");
    QTest::addColumn<OperandOfExpr>("elem_2");
    QTest::addColumn<bool>("exp_result");

    // Набор базовых узлов и деревьев для тестирования
    NodeOfExprTree* plus = new NodeOfExprTree("+");
    NodeOfExprTree* minus = new NodeOfExprTree("-");
    NodeOfExprTree* multiply = new NodeOfExprTree("*");
    NodeOfExprTree* division = new NodeOfExprTree("/");
    NodeOfExprTree* _1 = new NodeOfExprTree("1");
    NodeOfExprTree* _2 = new NodeOfExprTree("2");
    NodeOfExprTree* un_2 = new NodeOfExprTree("~", nullptr, _2);
    NodeOfExprTree* equal_node = nullptr;

    // 1. Сравнение слагаемых со знаком «+», первое больше второго
    OperandOfExpr plus_1 = {plus, _1, false};
    OperandOfExpr plus_2 = {plus, _2, false};
    QTest::newRow("1.Comparison of terms with a \"+\" sign, the first is greater than the second") << plus_1 << plus_2 << true;

    // 2. Сравнение слагаемых со знаком «+», второе больше первого
    QTest::newRow("2.Comparison of terms with a \"+\" sign, the second is greater than the first") << plus_2 << plus_1 << false;

    // 3. Одинаковые слагаемые
    QTest::newRow("3.Identical summands") << plus_1 << plus_1 << false;

    // 4. Сравнение множителей, первое больше второго
    OperandOfExpr multiply_1 = {multiply, _1, false};
    OperandOfExpr multiply_2 = {multiply, _2, false};
    QTest::newRow("4.Comparing multipliers, the first is greater than the second") << multiply_2 << multiply_1 << true;

    // 5. Сравнение множителей, второе больше первого
    QTest::newRow("5.Comparing multipliers, the second is greater than the first") << multiply_1 << multiply_2 << false;

    // 6. Одинаковые множители
    QTest::newRow("6.The same multipliers") << multiply_1 << multiply_1 << false;

    // 7. Первый узел есть делитель, если бы не был делителем － первый больше второго
    OperandOfExpr division_1 = {division, _1, false};
    OperandOfExpr division_2 = {division, _2, false};
    QTest::newRow("7.The first node is a divisor, if it were not a divisor, the first is greater than the second") << division_1 << multiply_2 << true;

    // 8. Первый узел есть делитель, если бы не был делителем － второй больше первого
    QTest::newRow("8.The first node is a divisor, if it were not a divisor, the second is greater than the first") << division_2 << multiply_1 << true;

    // 9. Второй узел есть делитель, если бы не был делителем － первый больше второго
    QTest::newRow("9.The second node is a divisor, if it were not a divisor, the first is greater than the second") << multiply_2 << division_1 << false;

    // 10. Второй узел есть делитель, если бы не был делителем － второй больше первого
    QTest::newRow("10.The second node is a divisor, if it were not a divisor, the second is greater than the first") << multiply_1 << division_2 << false;

    // 11. Оба делителя
    QTest::newRow("11. Both dividers") << division_2 << division_1 << false;

    // 12. Первый узел есть вычитаемое, первый узел больше второго
    OperandOfExpr minus_1 = {minus, _1, false};
    OperandOfExpr minus_2 = {minus, _2, false};
    QTest::newRow("12.The first node is the subtractible, the first node is greater than the second") << minus_2 << plus_1 << true;

    // 13. Первый узел есть вычитаемое, второй узел больше первого
    OperandOfExpr plus_un_2 = {minus, un_2, false};
    QTest::newRow("13.The first node is the subtractible, the second node is greater than the first") << minus_1 << plus_un_2 << false;

    // 14. Второй узел есть вычитаемое, первый узел больше второго
    QTest::newRow("14.The second node is a subtractible, the first node is greater than the second") << plus_un_2 << minus_1 << true;

    // 15. Второй узел есть вычитаемое, второй узел больше первого
    QTest::newRow("15.The second node is a subtractible, the second node is greater than the first") << plus_1 << minus_2 << false;

    // 16. Оба узла есть вычитаемые, первый узел больше второго

    QTest::newRow("16.Both nodes are subtractible, the first node is larger than the second") << minus_2 << minus_1 << true;

    // 17. Оба узла есть вычитаемые, второй узел больше первого
    QTest::newRow("17.Both nodes are subtractible, the second node is larger than the first") << minus_1 << minus_2 << false;

    // 18. Первый узел есть первый элемент дерева выражения, второй имеет родителя «+», первый － больше второго
    OperandOfExpr only_1 = {equal_node, _1, true};
    OperandOfExpr only_2 = {equal_node, _2, true};
    QTest::newRow("18.The first node is the first element of the expression tree, the second has a parent \"+\", the first is greater than the second") << only_1 << plus_2 << true;

    // 19. Первый узел есть первый элемент дерева выражения, второй имеет родителя «+», второй － больше первого
    QTest::newRow("19.The first node is the first element of the expression tree, the second has a parent \"+\", the second is larger than the first") << only_2 << plus_1 << false;

    // 20. Второй узел есть первый элемент дерева выражения, первый имеет родителя «+», первый － больше второго
    QTest::newRow("20.The second node is the first element of the expression tree, the first has a parent \"+\", the first is greater than the second") << plus_1 << only_2 << true;

    // 21. Второй узел есть первый элемент дерева выражения, первый имеет родителя «+», второй － больше первого
    QTest::newRow("21.The second node is the first element of the expression tree, the first has a parent \"+\", the second is larger than the first") << plus_2 << only_1 << false;

    // 22. Первый узел есть первый элемент дерева выражения, второй имеет родителя «*», первый － больше второго
    QTest::newRow("22.The first node is the first element of the expression tree, the second has a parent \"*\", the first is larger than the second") << only_2 << multiply_1 << true;

    // 23. Первый узел есть первый элемент дерева выражения, второй имеет родителя «*», второй － больше первого
    QTest::newRow("23.The first node is the first element of the expression tree, the second has a parent \"*\", the second is larger than the first") << only_1 << multiply_2 << false;

    // 24. Второй узел есть первый элемент дерева выражения, первый имеет родителя «*», первый － больше второго
    QTest::newRow("24.The second node is the first element of the expression tree, the first has a parent \"*\", the first is larger than the second") << multiply_2 << only_1 << true;

    // 25. Второй узел есть первый элемент дерева выражения, первый имеет родителя «*», второй － больше первого
    QTest::newRow("25.The second node is the first element of the expression tree, the first has a parent \"*\", the second is larger than the first") << multiply_1 << only_1 << false;

    // 26. Первый узел есть первый элемент дерева выражения, второй имеет родителя «/»
    QTest::newRow("26.The first node is the first element of the expression tree, the second has a parent \"/\"") << only_1 << division_2 << true;

    // 27. Второй узел есть первый элемент дерева выражения, первый имеет родителя «/»
    QTest::newRow("27.The second node is the first element of the expression tree, the first has a parent \"/\"") << division_2 << only_1 << false;

    // 28. Второй узел есть первый элемент дерева выражения, первый имеет родителя «-», первый － больше второго
    QTest::newRow("28.The second node is the first element of the expression tree, the first has a parent \"-\", the first is larger than the second") << minus_2 << only_1 << true;

    // 29. Второй узел есть первый элемент дерева выражения, первый имеет родителя «-», второй － больше первого
    OperandOfExpr only_un_2 = {equal_node, un_2, true};
    QTest::newRow("29.The second node is the first element of the expression tree, the first has a parent \"-\", the second is larger than the first") << minus_1 << only_un_2 << false;

    // 30. Первый узел есть первый элемент дерева выражения, второй имеет родителя «-», первый － больше второго
    QTest::newRow("30.The first node is the first element of the expression tree, the second has a parent \"-\", the first is greater than the second") << only_un_2 << minus_1 << true;

    // 31. Первый узел есть первый элемент дерева выражения, второй имеет родителя «-», второй － больше первого
    QTest::newRow("31.The first node is the first element of the expression tree, the second has a parent \"-\", the second is larger than the first") << only_1 << minus_2 << false;
}
