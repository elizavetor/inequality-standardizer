#include "test_getnodesofsameprecedencewithparenthesesopening.h"

Test_getNodesOfSamePrecedenceWithParenthesesOpening::
    Test_getNodesOfSamePrecedenceWithParenthesesOpening(QObject *parent)
    : QObject{parent}
{}

void Test_getNodesOfSamePrecedenceWithParenthesesOpening::testGetNodesOfSamePrecedenceWithParenthesesOpening()
{
    QFETCH(NodeOfExprTree*, root);
    QFETCH(QList<OperandOfExpr>, exp_list);
    QFETCH(bool, is_invert);

    // Получить результат
    QList<OperandOfExpr> real_list = root->getNodesOfSamePrecedenceWithParenthesesOpening(is_invert);

    // Сравнить полученный и ожидаемый списки
    QString error = compareListsOfNodes(exp_list, real_list);
    QVERIFY2(error.isEmpty(), qPrintable(error));

}

void Test_getNodesOfSamePrecedenceWithParenthesesOpening::testGetNodesOfSamePrecedenceWithParenthesesOpening_data()
{
    // Добавить столбцы
    QTest::addColumn<NodeOfExprTree*>("root");
    QTest::addColumn<QList<OperandOfExpr>>("exp_list");
    QTest::addColumn<bool>("is_invert");

    // Создать список ошибок для вызова функции создания дерева
    QSet<Error> errors;

    // 1. Одинаковые операторы «*»
    QList<OperandOfExpr> list_1 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                   OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("a"), false},
                                   OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("2"), false},
                                   OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("b"), false}};
    QTest::newRow("1. Identical operators: \"*\"") << postfixToTree("1 a * 2 b * *", errors) << list_1 << false;

    // 2. Одинаковые операторы «+»
    QList<OperandOfExpr> list_2 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                   OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("a"), false},
                                   OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("2"), false},
                                   OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("b"), false}};
    QTest::newRow("2. Identical operators: \"+\"") << postfixToTree("1 a + 2 b + +", errors) << list_2 << false;

    // 3. Одинаковые операторы «/»
    QList<OperandOfExpr> list_3 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                   OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("a"), false},
                                   OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("2"), false},
                                   OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("b"), false}};
    QTest::newRow("3. Identical operators: \"/\"") << postfixToTree("1 a / 2 b / /", errors) << list_3 << false;

    // 4. Одинаковые операторы «-»
    QList<OperandOfExpr> list_4 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                   OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("a"), false},
                                   OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("2"), false},
                                   OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("b"), false}};;
    QTest::newRow("4. Identical operators: \"-\"") << postfixToTree("1 a - 2 b - -", errors) << list_4 << false;

    // 5. Операторы «+» и «*»
    QList<OperandOfExpr> list_5 = {OperandOfExpr{nullptr, postfixToTree("1 a *", errors), true},
                                   OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("2 b *", errors), false}};
    QTest::newRow("5. Operators: \"+\", \"*\"") << postfixToTree("1 a * 2 b * +", errors) << list_5 << false;

    // 6. Операторы «*» и «+»
    QList<OperandOfExpr> list_6 = {OperandOfExpr{nullptr, postfixToTree("1 a *", errors), true},
                                   OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("2 b *", errors), false}};
    QTest::newRow("6. Operators: \"*\", \"+\"") << postfixToTree("1 a + 2 b + *", errors) << list_6 << false;

    // 7. Операторы «-» и «/»
    QList<OperandOfExpr> list_7 = {OperandOfExpr{nullptr, postfixToTree("1 a /", errors), true},
                                   OperandOfExpr{new NodeOfExprTree("-"), postfixToTree("2 b /", errors), false}};
    QTest::newRow("7. Operators: \"-\", \"/\"") << postfixToTree("1 a / 2 b / -", errors) << list_7 << false;

    // 8. Операторы «/» и «-»
    QList<OperandOfExpr> list_8 = {OperandOfExpr{nullptr, postfixToTree("1 a -", errors), true},
                                   OperandOfExpr{new NodeOfExprTree("/"), postfixToTree("2 b -", errors), false}};
    QTest::newRow("8. Operators: \"/\", \"-\"") << postfixToTree("1 a - 2 b - /", errors) << list_8 << false;

    // 9. Операторы «*» и «/»
    QList<OperandOfExpr> list_9 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                   OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("a"), false},
                                   OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("2"), false},
                                   OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("b"), false}};
    QTest::newRow("9. Operators: \"*\", \"/\"") << postfixToTree("1 a / 2 b / *", errors) << list_9 << false;

    // 10. Операторы «/» и «*»
    QList<OperandOfExpr> list_10 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("a"), false},
                                    OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("b"), false}};
    QTest::newRow("10. Operators: \"/\", \"*\"") << postfixToTree("1 a * 2 b * /", errors) << list_10 << false;

    // 11. Операторы «+» и «-»
    QList<OperandOfExpr> list_11 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("a"), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("b"), false}};
    QTest::newRow("11. Operators: \"+\", \"-\"") << postfixToTree("1 a - 2 b - +", errors) << list_11 << false;

    // 12. Операторы «-» и «+»
    QList<OperandOfExpr> list_12 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("a"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("b"), false}};
    QTest::newRow("12. Operators: \"-\", \"+\"") << postfixToTree("1 a + 2 b + -", errors) << list_12 << false;

    // 13. Унарные минусы «снаружи»
    QList<OperandOfExpr> list_13 = {OperandOfExpr{nullptr, postfixToTree("1 a + ~", errors), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("2 b + ~", errors), false}};
    QTest::newRow("13. Unary cons of \"outside\"") << postfixToTree("1 a + ~ 2 b + ~ +", errors) << list_13 << false;

    // 14. Унарные минусы «внутри»
    QList<OperandOfExpr> list_14 = {OperandOfExpr{nullptr, postfixToTree("1 ~", errors), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("a ~", errors), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("2 ~", errors), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("b ~", errors), false}};
    QTest::newRow("14. Unary cons \"inside\"") << postfixToTree("1 ~ a ~ + 2 ~ b ~ + +", errors) << list_14 << false;

    // 15. Много унарных минусов
    QList<OperandOfExpr> list_15 = {OperandOfExpr{nullptr, postfixToTree("1 a + ~ ~", errors), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("2 b + ~ ~", errors), false}};
    QTest::newRow("15. A lot of unary cons") << postfixToTree("1 a + ~ ~ 2 b + ~ ~ +", errors) << list_15  << false;

    // 16. Два слагаемых, состоящих из множителей и унарного минуса
    QList<OperandOfExpr> list_16 = {OperandOfExpr{nullptr, postfixToTree("1 a *", errors), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("b ~", errors), false}};
    QTest::newRow("16. Two terms consisting of multipliers and a unary minus") << postfixToTree("1 a * b ~ +", errors) << list_16 << false;

    // 17. Вложенные скобки из-за бинарного минуса
    QList<OperandOfExpr> list_17 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("3"), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("4"), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("5"), false}};
    QTest::newRow("17. Nested parentheses due to binary minus") << postfixToTree("1 2 3 + 4 5 + - -", errors) << list_17 << false;

    // 18. Вложенные скобки из-за деления
    QList<OperandOfExpr> list_18 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("3"), false},
                                    OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("4"), false},
                                    OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("5"), false}};
    QTest::newRow("18. Nested brackets due to division") << postfixToTree("1 2 3 * 4 5 * / /", errors) << list_18 << false;

    // 19. Вложенные скобки из-за бинарного минуса, is_inver = 1
    QList<OperandOfExpr> list_19 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("3"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("4"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("5"), false}};
    QTest::newRow("19. Nested brackets due to binary minus, is_inver = 1") << postfixToTree("1 2 3 + 4 5 + - -", errors) << list_19 << true;

    // 20. Вложенные скобки из-за деления, is_inver = 1
    QList<OperandOfExpr> list_20 = {OperandOfExpr{nullptr, new NodeOfExprTree("1"), true},
                                    OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("2"), false},
                                    OperandOfExpr{new NodeOfExprTree("*"), new NodeOfExprTree("3"), false},
                                    OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("4"), false},
                                    OperandOfExpr{new NodeOfExprTree("/"), new NodeOfExprTree("5"), false}};
    QTest::newRow("20. Nested brackets due to division, is_inver = 1 ") << postfixToTree("1 2 3 * 4 5 * / /", errors) << list_20 << true;

    // 21. Комплексный текст
    QList<OperandOfExpr> list_21 = {OperandOfExpr{nullptr, postfixToTree("a ~", errors), true},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("b"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("c"), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), new NodeOfExprTree("d"), false},
                                    OperandOfExpr{new NodeOfExprTree("-"), new NodeOfExprTree("e"), false},
                                    OperandOfExpr{new NodeOfExprTree("+"), postfixToTree("1 2 + 3 *", errors), false}};
    QTest::newRow("21. Complex text") << postfixToTree("a ~ b + c d - - 1 2 + 3 * +", errors) << list_21 << false;
}
