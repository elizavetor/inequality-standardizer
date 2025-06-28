/*!
* \file
* \brief Файл содержит реализацию методов класса Test_getSortedList для тестирования метода NodeOfExprTree::getSortedList программы inequalityStandardizer.
*/

#include "test_getsortedlist.h"

Test_getSortedList::Test_getSortedList(QObject *parent)
    : QObject{parent}
{}

void Test_getSortedList::testGetSortedList()
{
    QFETCH(NodeOfExprTree*, root);
    QFETCH(QList<OperandOfExpr>, exp_list);

    // Получить результат
    QList<OperandOfExpr> real_list = root->getSortedList();

    // Сравнить полученный и ожидаемый списки
    QString error = compareListsOfNodes(exp_list, real_list);
    QVERIFY2(error.isEmpty(), qPrintable(error));
}

void Test_getSortedList::testGetSortedList_data()
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

    // 1. Слагаемые без выражения в скобках
    QList<OperandOfExpr> list_1 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{plus, a, false},
                                   OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{plus, b, false}};
    QTest::newRow("1. Summands without expression in parentheses") << postfixToTree("1 a + 2 b + +", errors) << list_1;

    // 2. Слагаемые с выражением в скобках, заданный узел есть бинарный минус
    QList<OperandOfExpr> list_2 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{plus, a, false},
                                   OperandOfExpr{minus, _2, false},
                                   OperandOfExpr{plus, b, false}};
    QTest::newRow("2. Terms with an expression in parentheses, a given node is a binary minus") << postfixToTree("1 a + 2 b - -", errors) << list_2;

    // 3. Слагаемые с выражением в скобках, заданный узел есть плюс
    QTest::newRow("3. Terms with expressions in parentheses, this node is a plus") << postfixToTree("1 a 2 b - - +", errors) << list_2;

    // 4. Множители без выражений в скобках
    QList<OperandOfExpr> list_4 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{multiply, a, false},
                                   OperandOfExpr{multiply, _2, false},
                                   OperandOfExpr{multiply, b, false}};
    QTest::newRow("4. Multipliers without expressions in parentheses") << postfixToTree("1 a * 2 b * *", errors) << list_4;

    // 5. Множители с выражением в скобках
    QList<OperandOfExpr> list_5 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{division, a, false},
                                   OperandOfExpr{division, new NodeOfExprTree("/", _2, b), false}};
    QTest::newRow("5. Multipliers expressed in parentheses") << postfixToTree("1 a / 2 b / /", errors) << list_5;

    // 6. Унарный минус
    QList<OperandOfExpr> list_6 = {OperandOfExpr{new NodeOfExprTree("~"), _1, false}};
    QTest::newRow("6. Unary minus") << postfixToTree("1 ~", errors) << list_6;

    // 7. Комплексный текст
    QList<OperandOfExpr> list_7 = {OperandOfExpr{nullptr, new NodeOfExprTree("~", nullptr, a), true},
                                    OperandOfExpr{plus, b, false},
                                    OperandOfExpr{minus, new NodeOfExprTree("c"), false},
                                    OperandOfExpr{plus, new NodeOfExprTree("d"), false},
                                    OperandOfExpr{minus, new NodeOfExprTree("e"), false},
                                    OperandOfExpr{plus, postfixToTree("1 2 + 3 *", errors), false}};
    QTest::newRow("7. Complex text") << postfixToTree("a ~ b + c d e - - - 1 2 + 3 * +", errors) << list_7;
}
