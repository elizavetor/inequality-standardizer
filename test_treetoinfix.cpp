#include "test_treetoinfix.h"

Test_treeToInfix::Test_treeToInfix(QObject *parent)
    : QObject{parent}
{}

void Test_treeToInfix::testTreeToInfix()
{
    QFETCH(NodeOfExprTree*, tree);
    QFETCH(QString, exp_infix);

    // Получить инфиксную запись дерева
    QString real_infix = tree->treeToInfix();

    // Сравнить полученную строку с ожидаемой
    QCOMPARE(real_infix, exp_infix);
}

void Test_treeToInfix::testTreeToInfix_data()
{
    QTest::addColumn<NodeOfExprTree*>("tree");
    QTest::addColumn<QString>("exp_infix");

    // Пустой список ошибок
    QSet<Error> errors;

    // 1. Сложение
    QTest::newRow("1. Addition") << postfixToTree("a b +", errors) << "a + b";

    // 2. Вычитание
    QTest::newRow("2. Subtraction") << postfixToTree("a b -", errors) << "a - b";

    // 3. Деление
    QTest::newRow("3. Division") << postfixToTree("a b /", errors) << "a / b";

    // 4. Умножение
    QTest::newRow("4. Multiplication") << postfixToTree("a b *", errors) << "a * b";

    // 5. Унарный минус
    QTest::newRow("5. Unary minus") << postfixToTree("a ~", errors) << "-a";

    // 6. Оператор больше
    QTest::newRow("6. Greater operator") << postfixToTree("a b >", errors) << "a > b";

    // 7. Оператор меньше
    QTest::newRow("7. Less operator") << postfixToTree("a b <", errors) << "a < b";

    // 8. Оператор больше или равно
    QTest::newRow("8. Greater or equal operator") << postfixToTree("a b >=", errors) << "a >= b";

    // 9. Оператор меньше или равно
    QTest::newRow("9. Less or equal operator") << postfixToTree("a b <=", errors) << "a <= b";

    // 10. Оператор сравнения равно
    QTest::newRow("10. Equal operator") << postfixToTree("a b =", errors) << "a == b";

    // 11. Переменная
    QTest::newRow("11. Only variable") << postfixToTree("a", errors) << "a";

    // 12. Число
    QTest::newRow("12. Only number") << postfixToTree("1", errors) << "1";

    // 13. Оператор неравно
    QTest::newRow("13. Not equal operatorr") << postfixToTree("a b !=", errors) << "a != b";

    // 14. Одинаковые операторы «*»
    QTest::newRow("14. Identical operators: \"*\"") << postfixToTree("1 a * 2 b * *", errors) << "1 * a * 2 * b";

    // 15. Одинаковые операторы «/»
    QTest::newRow("15. Identical operators: \"/\"") << postfixToTree("1 a / 2 b / /", errors) << "1 / a / (2 / b)";

    // 16. Одинаковые операторы «+»
    QTest::newRow("16. Identical operators: \"+\"") << postfixToTree("1 a + 2 b + +", errors) << "1 + a + 2 + b";

    // 17. Одинаковые операторы «-»
    QTest::newRow("17. Identical operators: \"-\"") << postfixToTree("1 a - 2 b - -", errors) << "1 - a - (2 - b)";

    // 18. Операторы «+» и «*»
    QTest::newRow("18. Operators: \"+\", \"*\"") << postfixToTree("1 a * 2 b * +", errors) << "1 * a + 2 * b";

    // 19. Операторы «*» и «+»
    QTest::newRow("19. Operators: \"*\", \"+\"") << postfixToTree("1 a + 2 b + *", errors) << "(1 + a) * (2 + b)";

    // 20. Операторы «-» и «/»
    QTest::newRow("20. Operators: \"-\", \"/\"") << postfixToTree("1 a / 2 b / -", errors) << "1 / a - 2 / b";

    // 21. Операторы «/» и «-»
    QTest::newRow("21. Operators: \"/\", \"-\"") << postfixToTree("1 a - 2 b - /", errors) << "(1 - a) / (2 - b)";

    // 22. Унарные минусы «снаружи»
    QTest::newRow("22. Unary cons of \"outside\"") << postfixToTree("1 a * ~ 2 b * ~ +", errors) << "-(1 * a) + (-(2 * b))";

    // 23. Унарные минусы «внутри»
    QTest::newRow("23. Unary cons of \"inside\"") << postfixToTree("1 ~ a ~ * 2 ~ b ~ * +", errors) << "-1 * (-a) + (-2) * (-b)";

    // 24. Много унарных минусов
    QTest::newRow("24. A lot of unary cons") << postfixToTree("1 a * ~ ~ 2 b * ~ ~ +", errors) << "-(-(1 * a)) + (-(-(2 * b)))";

    // 25. Унарный минус у первого элемента в выражении в скобках
    QTest::newRow("25. The unary minus sign of the first element in the expression is in parentheses.") << postfixToTree("1 ~ a ~ + 2 ~ b ~ + *", errors) << "(-1 + (-a)) * (-2 + (-b))";

    // 26. Вложенные скобки из-за бинарного минуса
    QTest::newRow("26. Nested parentheses due to binary minus.") << postfixToTree("1 2 3 4 + - -", errors) << "1 - (2 - (3 + 4))";

    // 27. Вложенные скобки из-за деления
    QTest::newRow("27. Nested brackets due to division.") << postfixToTree("1 2 3 4 + / /", errors) << "1 / (2 / (3 + 4))";

    // 28. Комплексный тест
    QTest::newRow("28. Complex test.") << postfixToTree("1 3 4 * / 5 ~ * 6 ~ 7 8 * - <", errors) << "1 / (3 * 4) * (-5) < (-6) - 7 * 8";
}
