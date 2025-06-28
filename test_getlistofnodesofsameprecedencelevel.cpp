/*!
* \file
* \brief Файл содержит реализацию методов класса Test_getListOfNodesOfSamePrecedenceLevel для тестирования метода NodeOfExprTree::getListOfNodesOfSamePrecedenceLevel программы inequalityStandardizer.
*/

#include "test_getlistofnodesofsameprecedencelevel.h"

Test_getListOfNodesOfSamePrecedenceLevel::Test_getListOfNodesOfSamePrecedenceLevel(QObject *parent)
    : QObject{parent}
{}

void Test_getListOfNodesOfSamePrecedenceLevel::testGetListOfNodesOfSamePrecedenceLevel()
{
    QFETCH(NodeOfExprTree*, root);
    QFETCH(QList<OperandOfExpr>, exp_list);

    // Получить результат
    QList<OperandOfExpr> real_list = root->getListOfNodesOfSamePrecedenceLevel();

    // Сравнить полученный и ожидаемый списки
    QString error = compareListsOfNodes(exp_list, real_list);
    QVERIFY2(error.isEmpty(), qPrintable(error));

}

void Test_getListOfNodesOfSamePrecedenceLevel::testGetListOfNodesOfSamePrecedenceLevel_data()
{
    // Добавить столбцы
    QTest::addColumn<NodeOfExprTree*>("root");
    QTest::addColumn<QList<OperandOfExpr>>("exp_list");

    // Создать список ошибок для вызова функции создания дерева
    QSet<Error> errors;

    // Создать часто используемые узлы
    NodeOfExprTree* plus = new NodeOfExprTree("+");
    NodeOfExprTree* minus = new NodeOfExprTree("-");
    NodeOfExprTree* multiply = new NodeOfExprTree("*");
    NodeOfExprTree* division = new NodeOfExprTree("/");
    NodeOfExprTree* _1 = new NodeOfExprTree("1");
    NodeOfExprTree* _2 = new NodeOfExprTree("2");
    NodeOfExprTree* a = new NodeOfExprTree("a");
    NodeOfExprTree* b = new NodeOfExprTree("b");

    // 1. Одинаковые операторы «*»
    QList<OperandOfExpr> list_1 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{multiply, a, false},
                                   OperandOfExpr{multiply, _2, false},
                                   OperandOfExpr{multiply, b, false}};
    QTest::newRow("1. Identical operators: \"*\"") << postfixToTree("1 a * 2 b * *", errors) << list_1;

    // 2. Одинаковые операторы «+»
    QList<OperandOfExpr> list_2 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{plus, a, false},
                                   OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{plus, b, false}};
    QTest::newRow("2. Identical operators: \"+\"") << postfixToTree("1 a + 2 b + +", errors) << list_2;

    // 3. Одинаковые операторы «/»
    QList<OperandOfExpr> list_3 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{division, a, false},
                                   OperandOfExpr{division, postfixToTree("2 b /", errors), false}};
    QTest::newRow("3. Identical operators: \"/\"") << postfixToTree("1 a / 2 b / /", errors) << list_3;

    // 4. Одинаковые операторы «-»
    QList<OperandOfExpr> list_4 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{minus, a, false},
                                   OperandOfExpr{minus, postfixToTree("2 b -", errors), false}};
    QTest::newRow("4. Identical operators: \"-\"") << postfixToTree("1 a - 2 b - -", errors) << list_4;

    // 5. Операторы «+» и «*»
    QList<OperandOfExpr> list_5 = {OperandOfExpr{nullptr, postfixToTree("1 a *", errors), true},
                                   OperandOfExpr{plus, postfixToTree("2 b *", errors), false}};
    QTest::newRow("5. Operators: \"+\", \"*\"") << postfixToTree("1 a * 2 b * +", errors) << list_5;

    // 6. Операторы «*» и «+»
    QList<OperandOfExpr> list_6 = {OperandOfExpr{nullptr, postfixToTree("1 a +", errors), true},
                                   OperandOfExpr{multiply, postfixToTree("2 b +", errors), false}};
    QTest::newRow("6. Operators: \"*\", \"+\"") << postfixToTree("1 a + 2 b + *", errors) << list_6;

    // 7. Операторы «-» и «/»
    QList<OperandOfExpr> list_7 = {OperandOfExpr{nullptr, postfixToTree("1 a /", errors), true},
                                   OperandOfExpr{minus, postfixToTree("2 b /", errors), false}};
    QTest::newRow("7. Operators: \"-\", \"/\"") << postfixToTree("1 a / 2 b / -", errors) << list_7;

    // 8. Операторы «/» и «-»
    QList<OperandOfExpr> list_8 = {OperandOfExpr{nullptr, postfixToTree("1 a -", errors), true},
                                   OperandOfExpr{division, postfixToTree("2 b -", errors), false}};
    QTest::newRow("8. Operators: \"/\", \"-\"") << postfixToTree("1 a - 2 b - /", errors) << list_8;

    // 9. Операторы «*» и «/»
    QList<OperandOfExpr> list_9 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{division, a, false},
                                   OperandOfExpr{multiply, _2, false},
                                   OperandOfExpr{division, b, false}};
    QTest::newRow("9. Operators: \"*\", \"/\"") << postfixToTree("1 a / 2 b / *", errors) << list_9;

    // 10. Операторы «/» и «*»
    QList<OperandOfExpr> list_10 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{multiply, a, false},
                                   OperandOfExpr{division, postfixToTree("2 b *", errors), false}};
    QTest::newRow("10. Operators: \"/\", \"*\"") << postfixToTree("1 a * 2 b * /", errors) << list_10;

    // 11. Операторы «+» и «-»
    QList<OperandOfExpr> list_11 = {OperandOfExpr{nullptr, _1, true},
                                    OperandOfExpr{minus, a, false},
                                    OperandOfExpr{plus, _2, false},
                                    OperandOfExpr{minus, b, false}};
    QTest::newRow("11. Operators: \"+\", \"-\"") << postfixToTree("1 a - 2 b - +", errors) << list_11;

    // 12. Операторы «-» и «+»
    QList<OperandOfExpr> list_12 = {OperandOfExpr{nullptr, _1, true},
                                    OperandOfExpr{plus, a, false},
                                    OperandOfExpr{minus, postfixToTree("2 b +", errors), false}};
    QTest::newRow("12. Operators: \"-\", \"+\"") << postfixToTree("1 a + 2 b + -", errors) << list_12;

    // 13. Унарные минусы «снаружи»
    QList<OperandOfExpr> list_13 = {OperandOfExpr{nullptr, postfixToTree("1 a + ~", errors), true},
                                    OperandOfExpr{plus, postfixToTree("2 b + ~", errors), false}};
    QTest::newRow("13. Unary cons of \"outside\"") << postfixToTree("1 a + ~ 2 b + ~ +", errors) << list_13;

    // 14. Унарные минусы «внутри»
    QList<OperandOfExpr> list_14 = {OperandOfExpr{nullptr, postfixToTree("1 ~", errors), true},
                                    OperandOfExpr{plus, postfixToTree("a ~", errors), false},
                                    OperandOfExpr{plus, postfixToTree("2 ~", errors), false},
                                    OperandOfExpr{plus, postfixToTree("b ~", errors), false}};
    QTest::newRow("14. Unary cons \"inside\"") << postfixToTree("1 ~ a ~ + 2 ~ b ~ + +", errors) << list_14;

    // 15. Много унарных минусов
    QList<OperandOfExpr> list_15 = {OperandOfExpr{nullptr, postfixToTree("1 a + ~ ~", errors), true},
                                    OperandOfExpr{plus, postfixToTree("2 b + ~ ~", errors), false}};
    QTest::newRow("15. A lot of unary cons") << postfixToTree("1 a + ~ ~ 2 b + ~ ~ +", errors) << list_15;

    // 16. Два слагаемых, состоящих из множителей и унарного минуса
    QList<OperandOfExpr> list_16 = {OperandOfExpr{nullptr, postfixToTree("1 a *", errors), true},
                                    OperandOfExpr{plus, postfixToTree("b ~", errors), false}};
    QTest::newRow("16. Two terms consisting of multipliers and a unary minus") << postfixToTree("1 a * b ~ +", errors) << list_16;

    // 17. Вложенные скобки из-за бинарного минуса
    QList<OperandOfExpr> list_17 = {OperandOfExpr{nullptr, _1, true},
                                    OperandOfExpr{minus, postfixToTree("2 3 4 + -", errors), false}};
    QTest::newRow("17. Nested parentheses due to binary minus") << postfixToTree("1 2 3 4 + - -", errors) << list_17;

    // 18. Вложенные скобки из-за деления
    QList<OperandOfExpr> list_18 = {OperandOfExpr{nullptr, _1, true},
                                    OperandOfExpr{division, postfixToTree("2 3 4 * /", errors), false}};
    QTest::newRow("18. Nested brackets due to division") << postfixToTree("1 2 3 4 * / /", errors) << list_18;

    // 19. Комплексный текст
    QList<OperandOfExpr> list_19 = {OperandOfExpr{nullptr, postfixToTree("a ~", errors), true},
                                    OperandOfExpr{plus, b, false},
                                    OperandOfExpr{minus, postfixToTree("c d e - -", errors), false},
                                    OperandOfExpr{plus, postfixToTree("1 2 + 3 *", errors), false}};
    QTest::newRow("19. Complex text") << postfixToTree("a ~ b + c d e - - - 1 2 + 3 * +", errors) << list_19;
}
