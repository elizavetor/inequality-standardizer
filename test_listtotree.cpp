#include "test_listtotree.h"

Test_listToTree::Test_listToTree(QObject *parent)
    : QObject{parent}
{}

void Test_listToTree::testListToTree()
{
    QFETCH(QList<OperandOfExpr>, list);
    QFETCH(NodeOfExprTree*, exp_tree);

    // Установыть связи внутри каждого элемента списка
    for(int i=0; i < list.size(); i++)
    {
        if (list[i].parent) list[i].parent->setRightOperand(list[i].operand);
    }

    // Установить связи между элементами списка
    NodeOfExprTree* real_tree = exp_tree->listToTree(list);

    // Сравнить полученное и ожидаемое деревья
    QStringList path;
    QString error;
    QVERIFY2(compareTrees(exp_tree, real_tree, path, error), error.toUtf8());
}

void Test_listToTree::testListToTree_data()
{
    // Добавить столбцы
    QTest::addColumn<QList<OperandOfExpr>>("list");
    QTest::addColumn<NodeOfExprTree*>("expr_tree");

    // Создать список ошибок для вызова функции создания дерева
    QSet<Error> errors;

    // Создать узлы
    NodeOfExprTree* plus = new NodeOfExprTree("+");
    NodeOfExprTree* minus = new NodeOfExprTree("-");
    NodeOfExprTree* multiply = new NodeOfExprTree("*");
    NodeOfExprTree* division = new NodeOfExprTree("/");
    NodeOfExprTree* _1 = new NodeOfExprTree("1");
    NodeOfExprTree* _2 = new NodeOfExprTree("2");
    NodeOfExprTree* _3 = new NodeOfExprTree("3");

    // 1. Список слагаемых
    QList<OperandOfExpr> list_1 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{minus, _3, false}};
    QTest::newRow("1. List of summands") << list_1 << postfixToTree("1 2 + 3 -", errors);

    // 2. Список множителей
    QList<OperandOfExpr> list_2 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{multiply, _2, false},
                                   OperandOfExpr{division, _3, false}};
    QTest::newRow("2. List of multipliers") << list_2 << postfixToTree("1 2 * 3 /", errors);

    // 3. Первое слагаемое дерева в середине списка
    QList<OperandOfExpr> list_3 = {OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{minus, _3, false}};
    QTest::newRow("3. The first term of the tree in the middle of the list") << list_3 << postfixToTree("2 1 + 3 -", errors);

    // 4. Первое слагаемое дерева в конце списка
    QList<OperandOfExpr> list_4 = {OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{minus, _3, false},
                                   OperandOfExpr{nullptr, _1, true}};
    QTest::newRow("4. The first term of the tree at the end of the list") << list_4 << postfixToTree("2 3 - 1 +", errors);

    // 5. Первый элемент списка имеет родителя типа оператора бинарный минус
    QList<OperandOfExpr> list_5 = {OperandOfExpr{minus, _3, false},
                                   OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{nullptr, _1, true}};
    QTest::newRow("5. The first element of the list has a parent of the binary minus operator type.") << list_5 << postfixToTree("3 ~ 2 + 1 +", errors);

    // 6. Первый элемент списка имеет родителя типа оператора деление
    QList<OperandOfExpr> list_6 = {OperandOfExpr{division, _3, false},
                                   OperandOfExpr{multiply, _2, false},
                                   OperandOfExpr{nullptr, new NodeOfExprTree("4"), true}};
    QTest::newRow("6. The first element of the list has a parent of the division operator type.") << list_6 << postfixToTree("1 3 / 2 * 4 *", errors);

    // 7. Первый элемент списка имеет составной операнд
    QList<OperandOfExpr> list_7 = {OperandOfExpr{nullptr, postfixToTree("1 a *", errors), true},
                                   OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{minus, _3, false}};
    QTest::newRow("7. The first element of the list has a compound operand.") << list_7 << postfixToTree("1 a * 2 + 3 -", errors);

    // 8. Средний элемент списка имеет составной операнд
    QList<OperandOfExpr> list_8 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{plus, postfixToTree("2 b *", errors), false},
                                   OperandOfExpr{minus, _3, false}};
    QTest::newRow("8. The middle element of the list has a compound operand.") << list_8 << postfixToTree("1 2 b * + 3 -", errors);

    // 9. Последний элемент списка имеет составной операнд
    QList<OperandOfExpr> list_9 = {OperandOfExpr{nullptr, _1, true},
                                   OperandOfExpr{plus, _2, false},
                                   OperandOfExpr{minus, postfixToTree("3 c *", errors), false}};
    QTest::newRow("9. The last element of the list has a compound operand.") << list_9 << postfixToTree("1 2 + 3 c * -", errors);

    // 10. Комплексный тест
    QList<OperandOfExpr> list_10 = {OperandOfExpr{multiply, postfixToTree("a 1 +", errors), false},
                                    OperandOfExpr{nullptr, postfixToTree("b c * ~", errors), true}};
    QTest::newRow("10. Complex test.") << list_10 << postfixToTree("a 1 + b c * ~ *", errors);
}
