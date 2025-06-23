#include "test_getdegreeofexpr.h"

Test_getDegreeOfExpr::Test_getDegreeOfExpr(QObject *parent)
    : QObject{parent}
{}

void Test_getDegreeOfExpr::testGetDegreeOfExpr()
{
    QFETCH(NodeOfExprTree*, expr);
    QFETCH(int, exp_degree);

    // Получить результат сравнения
    int real_degree = expr->getDegreeOfExpr();

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_degree, exp_degree);
}

void Test_getDegreeOfExpr::testGetDegreeOfExpr_data()
{
    // Добавить столбцы
    QTest::addColumn<NodeOfExprTree*>("expr");
    QTest::addColumn<int>("exp_degree");

    // Создать список ошибок для вызова функции создания дерева
    QSet<Error> errors;

    // 1. Базовые тесты

    // 1.1 Переменная
    NodeOfExprTree* node_1_1 = postfixToTree("a", errors);
    QTest::newRow("1.1 Only variable") << node_1_1 << 1;

    // 1.2 Число
    NodeOfExprTree* node_1_2 = postfixToTree("1", errors);
    QTest::newRow("1.2 Only number") << node_1_2 << 0;
}
