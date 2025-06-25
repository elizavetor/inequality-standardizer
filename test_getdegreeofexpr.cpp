#include "test_getdegreeofexpr.h"

Test_getDegreeOfExpr::Test_getDegreeOfExpr(QObject *parent)
    : QObject{parent}
{}

void Test_getDegreeOfExpr::testGetDegreeOfExpr()
{
    QFETCH(NodeOfExprTree*, expr);
    QFETCH(int, exp_degree);

    // Получить результат
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
    QTest::newRow("1.1 Only variable") << postfixToTree("a", errors) << 1;

    // 1.2 Число
    QTest::newRow("1.2 Only number") << postfixToTree("1", errors) << 0;


    // 2. Множители

    // 2.1 Число и переменная
    QTest::newRow("2.1 Number and variable") << postfixToTree("1 a *", errors) << 1;

    // 2.2 Два разных имени переменных
    QTest::newRow("2.2 Two different variables' names") << postfixToTree("a b *", errors) << 2;

    // 2.3 Два одинаковых имени переменных
    QTest::newRow("2.3 Two equal variables' names") << postfixToTree("a a *", errors) << 2;

    // 2.4 Переменная-делимое и переменная-делитель
    QTest::newRow("2.4 Variable-divisable and variable-divisor") << postfixToTree("a b /", errors) << 0;

    // 2.5 Число-делимое и переменная-делитель
    QTest::newRow("2.5 Number-divisable and variable-divisor") << postfixToTree("1 a /", errors) << -1;

    // 2.6 Переменная-делимое и число-делитель
    QTest::newRow("2.6 Variable-divisable and number-divisor") << postfixToTree("a 1 /", errors) << 1;

    // 2.7 Число-делимое и делитель - выражение в скобках
    QTest::newRow("2.7 Number-divisable and expression in parentheses-divisor") << postfixToTree("1 a b * /", errors) << -2;


    // 3. Слагаемые

    // 3.1 Число и переменная
    QTest::newRow("3.1 Number and variable") << postfixToTree("1 a +", errors) << 1;

    // 3.2 Переменная и число
    QTest::newRow("3.2 Variable and number") << postfixToTree("a 1 +", errors) << 1;

    // 3.3 Переменная и переменная
    QTest::newRow("3.3 Variable and variable") << postfixToTree("a b +", errors) << 1;

    // 3.4 Выражение, элемент с максимальной степенью в начале выражения
    QTest::newRow("3.4 Expression, element with max degree at start of expression") << postfixToTree("a 1 2 + +", errors) << 1;

    // 3.5 Выражение, элемент с максимальной степенью в середине выражения
    QTest::newRow("3.5 Expression, element with max degree at middle of expression") << postfixToTree("1 a 2 + +", errors) << 1;

    // 3.6 Выражение, элемент с максимальной степенью в конце выражения
    QTest::newRow("3.6 Expression, element with max degree in end of expression") << postfixToTree("1 2 a + +", errors) << 1;

    // 3.7 Все элементы в выражении с одинаковой степенью
    QTest::newRow("3.7 All elements in expression of one degree") << postfixToTree("a b + c +", errors) << 1;

    // 3.8 Множители и переменная
    QTest::newRow("3.8 Multipliers and variable") << postfixToTree("a a * b +", errors) << 2;

    // 3.9 Переменная и множители
    QTest::newRow("3.9 Variable and multipliers") << postfixToTree("a b b * +", errors) << 2;

    // 3.10 Переменная-уменьшаемое и переменная-вычитаемое
    QTest::newRow("3.10 Variable-reduced and variable-subtracted") << postfixToTree("a b -", errors) << 1;

    // 3.11 Число-уменьшаемое и переменная-вычитаемое
    QTest::newRow("3.11 Number-reduced and variable-subtracted") << postfixToTree("1 a -", errors) << 1;

    // 3.12 Переменная-уменьшаемое и число-вычитаемое
    QTest::newRow("3.12 Variable-reduced and number-subtracted") << postfixToTree("a 1 -", errors) << 1;

    // 3.13 Число-уменьшаемое и число-вычитаемое
    QTest::newRow("3.13 Number-reduced and number-subtracted") << postfixToTree("2 1 -", errors) << 0;

    // 3.14 Вычитаемое в скобках － вычитаемое
    QTest::newRow("3.14 Subtracted in parentheses is subtracted") << postfixToTree("1 2 a + -", errors) << 1;

    // 3.15 Слагаемые как делитель
    QTest::newRow("3.15 Summands as divisor") << postfixToTree("1 a b b * + /", errors) << -2;


    // 4. Унарные минусы

    // 4.1 Переменная с унарным минусом
    QTest::newRow("4.1 Variable with unary minus") << postfixToTree("a ~", errors) << 1;

    // 4.2 Число с унарным минусом
    QTest::newRow("4.2 Number with unary minus") << postfixToTree("1 ~", errors) << 0;

    // 4.3 Переменная с двумя унарными минусами
    QTest::newRow("4.3 Variable with two unary minuses") << postfixToTree("a ~ ~", errors) << 1;

    // 4.4 Число с двумя унарными минусами
    QTest::newRow("4.4 Number with two unary minuses") << postfixToTree("1 ~ ~", errors) << 0;

    // 4.5 Унарный минус перед слагаемыми
    QTest::newRow("4.5 Unary minus before summands") << postfixToTree("a b + ~", errors) << 1;

    // 4.6 Унарный минус перед множителями
    QTest::newRow("4.6 Unary minus before multipliers") << postfixToTree("a b * ~", errors) << 2;


    // 5. Вложенные скобки

    // 5.1 Первые элементы в каждой скобке имеют максимальную степень
    QTest::newRow("5.1 First elements in all parentheses have max degree") << postfixToTree("a b c 1 + * 2 + *", errors) << 3;

    // 5.2 Средние элементы в каждой скобке имеют максимальную степень
    QTest::newRow("5.2 Average elements in all parentheses have max degree") << postfixToTree("a 1 b 2 c 3 + + * + 4 + *", errors) << 3;

    // 5.3 Последние элементы в каждой скобке имеют максимальную степень
    QTest::newRow("5.3 Last elements in all parentheses have max degree") << postfixToTree("a 1 b 2 c + * + *", errors) << 3;

    // 5.4 Внутренняя скобка с наибольшей степенью
    QTest::newRow("5.4 Nested parentheses has max degree") << postfixToTree("a 1 b c * 2 + * d + *", errors) << 3;


    // 6. Комплексный тест
    QTest::newRow("6 Complex test") << postfixToTree("a 1 b 2 с + * + ~ * 3 d e + * -", errors) << 3;
}
