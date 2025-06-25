#include "test_sortoperandsalphabetically.h"

Test_sortOperandsAlphabetically::Test_sortOperandsAlphabetically(QObject *parent)
    : QObject{parent}
{}

void Test_sortOperandsAlphabetically::testSortOperandsAlphabetically()
{
    QFETCH(NodeOfExprTree*, start_tree);
    QFETCH(NodeOfExprTree*, exp_final_tree);

    // Получить дерево
    NodeOfExprTree* real_final_tree = start_tree->sortOperandsAlphabetically();

    // Сравнить полученное дерево с ожидаемым
    QString error_message;
    QStringList path;
    QVERIFY2(compareTrees(exp_final_tree, real_final_tree, path, error_message), error_message.toUtf8());
}

void Test_sortOperandsAlphabetically::testSortOperandsAlphabetically_data()
{
    // Добавить столбцы
    QTest::addColumn<NodeOfExprTree*>("start_tree");
    QTest::addColumn<NodeOfExprTree*>("exp_final_tree");

    // Создать список ошибок для вызова функции создания дерева
    QSet<Error> errors;

    // 1. Простые выражения

    // 1.1 Число
    NodeOfExprTree* start_tree_1_1 = postfixToTree("1", errors);
    QTest::newRow("1.1 Number") << start_tree_1_1 << start_tree_1_1;

    // 1.2 Переменная
    NodeOfExprTree* start_tree_1_2 = postfixToTree("a", errors);
    QTest::newRow("1.2 Variable") << start_tree_1_2 << start_tree_1_2;

    // 1.3 Унарный минус и переменная
    NodeOfExprTree* start_tree_1_3 = postfixToTree("a ~", errors);
    QTest::newRow("1.3 Unary minus and variable") << start_tree_1_3 << start_tree_1_3;

    // 1.4 Пустое выражение
    NodeOfExprTree* start_tree_1_4 = nullptr;
    QTest::newRow("1.4 Equal tree") << start_tree_1_4 << start_tree_1_4;

    // 2.Тесты для множителей

    // 2.1 Проверка на первое правило: сначала числа, потом переменные, далее - выражения в скобках
    NodeOfExprTree* start_tree_2_1 = postfixToTree("a 1 *", errors);
    NodeOfExprTree* final_tree_2_1 = postfixToTree("1 a *", errors);
    QTest::newRow("2.1 Checking for a rule for miltipliers: numbers first, then variables, then expressions in parentheses. ( a * b -> 1 * a )") << start_tree_2_1 << final_tree_2_1;

    // 2.2 Проверка на второе правило: первый множитель меньше второго с учётом знака (для узлов типа число)
    NodeOfExprTree* start_tree_2_2 = postfixToTree("1 2 ~ *", errors);
    NodeOfExprTree* final_tree_2_2 = postfixToTree("2 ~ 1 *", errors);
    QTest::newRow("2.2 Checking for the rule for miltipliers: the first multiplier is less than the second, taking into account the sign. ( 1 * (~2) -> (~2) * 1 )") << start_tree_2_2 << final_tree_2_2;

    // 2.3 Проверка на третье правило: первый множитель меньше второго (для узлов типа переменная)
    NodeOfExprTree* start_tree_2_3 = postfixToTree("b a *", errors);
    NodeOfExprTree* final_tree_2_3 = postfixToTree("a b *", errors);
    QTest::newRow("2.3 Checking for the rule for miltipliers: the first multiplier is less than the second. ( b * a -> a * b )") << start_tree_2_3 << final_tree_2_3;

    // 2.4 Проверка на четвёртое правило: верный порядок выражений в скобках
    NodeOfExprTree* start_tree_2_4 = postfixToTree("b 1 + a 2 + *", errors);
    NodeOfExprTree* final_tree_2_4 = postfixToTree("a 2 + b 1 + *", errors);
    QTest::newRow("2.4 Checking for the rule for miltipliers: correct order of expressions in parentheses. ( (b + 1) * (a + 2) -> (a + 2) * (b + 1) )") << start_tree_2_4 << final_tree_2_4;

    // 2.5 Унарный минус
    NodeOfExprTree* start_tree_2_5 = postfixToTree("b a ~ *", errors);
    NodeOfExprTree* final_tree_2_5 = postfixToTree("a ~ b *", errors);
    QTest::newRow("2.5 For miltipliers: unary minus. ( b * (~a) -> (~a) * b )") << start_tree_2_5 << final_tree_2_5;

    // 2.6 Знак деления
    NodeOfExprTree* start_tree_2_6 = postfixToTree("b a /", errors);
    QTest::newRow("2.6 For miltipliers: division. ( b / a )") << start_tree_2_6 << start_tree_2_6;

    // 2.7 Выражение в скобке от знака деления
    NodeOfExprTree* start_tree_2_7 = postfixToTree("b a 2 * /", errors);
    NodeOfExprTree* final_tree_2_7 = postfixToTree("b 2 a * /", errors);
    QTest::newRow("2.7 For miltipliers: expression in parenthesis from the division sign. ( b / (a * 2) -> b / (2 * a) )") << start_tree_2_7 << final_tree_2_7;

    // 2.8 Все правила
    NodeOfExprTree* start_tree_2_8 = postfixToTree("b c / 4 5 + 2 ~ * * 1 2 3 - + a * * 1 *", errors);
    NodeOfExprTree* final_tree_2_8 = postfixToTree("2 ~ 1 * a * b * 1 2 + 3 - * 4 5 + * c /", errors);
    QTest::newRow("2.8 For miltipliers: all rules. ( b / c * (4 + 5) * (~2) * (1 + 2 - 3) * a * 1  -> ~2 * 1 * a * b * (1 + 2 - 3) * (4 + 5) / c )") << start_tree_2_8 << final_tree_2_8;

    // 3. Тесты для слагаемых

    // 3.1 Проверка на первое правило: сначала слагаемое с одинаковыми внутри себя именами переменных, потом - с различными
    NodeOfExprTree* start_tree_3_1 = postfixToTree("a b b * +", errors);
    NodeOfExprTree* final_tree_3_1 = postfixToTree("b b * a +", errors);
    QTest::newRow("3.1 Checking for the rule for terms: first comes a term with the same variable names inside it. ( a + b * b  -> b * b + a )") << start_tree_3_1 << final_tree_3_1;

    // 3.2 Проверка на второе правило: сначала слагаемое с большей степенью переменных
    NodeOfExprTree* start_tree_3_2 = postfixToTree("a b c * +", errors);
    NodeOfExprTree* final_tree_3_2 = postfixToTree("b c * a +", errors);
    QTest::newRow("3.2 Checking for the rule for terms: first comes the term with a higher degree of variables. ( a + b * c  -> b * c + a )") << start_tree_3_2 << final_tree_3_2;

    // 3.3 Проверка на третье правило: по алфавиту, учитывая только имена переменные
    NodeOfExprTree* start_tree_3_3 = postfixToTree("b a +", errors);
    NodeOfExprTree* final_tree_3_3 = postfixToTree("a b +", errors);
    QTest::newRow("3.3 Checking for the rule for terms: alphabetically, considering only the names of the variables. ( b + a  -> a + b )") << start_tree_3_3 << final_tree_3_3;

    // 3.4 Проверка на четвёртое правило: от большего количества элементов слагаемого к меньшему
    NodeOfExprTree* start_tree_3_4 = postfixToTree("a 2 a * +", errors);
    NodeOfExprTree* final_tree_3_4 = postfixToTree("2 a * a +", errors);
    QTest::newRow("3.4 Checking for the rule for terms: from more elements of the summand to fewer. ( a + 2 * a  -> 2 * a + a )") << start_tree_3_4 << final_tree_3_4;

    // 3.5 Проверка на пятое правило: от большего количества выражений в скобках в слагаемом к меньшему
    NodeOfExprTree* start_tree_3_5 = postfixToTree("2 a b * * a b 1 + * +", errors);
    NodeOfExprTree* final_tree_3_5 = postfixToTree("a b 1 + * 2 a * b * +", errors);
    QTest::newRow("3.5 Checking for the rule for terms: ffrom more expressions in parentheses in the summand to fewer. ( 2 * a * b + a * (b + 1)  -> a * (b + 1) + 2 * a * b )") << start_tree_3_5 << final_tree_3_5;

    // 3.6 Проверка на шестое правило: от большего числа к меньшему (если слагаемые состоят из одного числа)
    NodeOfExprTree* start_tree_3_6 = postfixToTree("2 ~ 1 +", errors);
    NodeOfExprTree* final_tree_3_6 = postfixToTree("1 2 ~ +", errors);
    QTest::newRow("3.6 Checking for the rule for terms: from more to less. ( (~2) + 1  -> 1 + (~2) )") << start_tree_3_6 << final_tree_3_6;

    // 3.7 Все правила
    NodeOfExprTree* start_tree_3_7 = postfixToTree("b c * 1 2 + 3 * 1 + + a b * 1 2 + 3 4 + * + + x y z * * 2 a a * + + +", errors);
    NodeOfExprTree* final_tree_3_7 = postfixToTree("a a * x y * z * + a b * + b c * + 1 2 + 3 4 + * + 1 2 + 3 * + 2 + 1 +", errors);
    QTest::newRow("3.6 Checking for the rule for terms: all rules.") << start_tree_3_7 << final_tree_3_7;

    // 4. Тесты на составление и построение дерева

    // 4.1 Одинаковые операторы «*»
    NodeOfExprTree* start_tree_4_1 = postfixToTree("a 1 * 2 b * *", errors);
    NodeOfExprTree* final_tree_4_1 = postfixToTree("1 2 * a * b *", errors);
    QTest::newRow("4.1 Identical operators: \"*\"") << start_tree_4_1 << final_tree_4_1;

    // 4.2 Одинаковые операторы «/»
    NodeOfExprTree* start_tree_4_2 = postfixToTree("a 1 / b 2 / /", errors);
    QTest::newRow("4.2 Identical operators: \"/\"") << start_tree_4_2 << start_tree_4_2;

    // 4.3 Одинаковые операторы «+»
    NodeOfExprTree* start_tree_4_3 = postfixToTree("a 1 + 2 b + +", errors);
    NodeOfExprTree* final_tree_4_3 = postfixToTree("1 2 * a * b *", errors);
    QTest::newRow("4.3 Identical operators: \"+\"") << start_tree_4_3 << final_tree_4_3;

    // 4.4 Одинаковые операторы «-»
    NodeOfExprTree* start_tree_4_4 = postfixToTree("a 1 - 2 b - -", errors);
    NodeOfExprTree* final_tree_4_4 = postfixToTree("a b + 1 - 2 -", errors);
    QTest::newRow("4.4 Identical operators: \"-\"") << start_tree_4_4 << final_tree_4_4;

    // 4.5 Операторы «+» и «*»
    NodeOfExprTree* start_tree_4_5 = postfixToTree("b 2 * 1 a * +", errors);
    NodeOfExprTree* final_tree_4_5 = postfixToTree("1 a * 2 b * +", errors);
    QTest::newRow("4.5 Operators: \"+\", \"*\"") << start_tree_4_5 << final_tree_4_5;

    // 4.6 Операторы «*» и «+»
    NodeOfExprTree* start_tree_4_6 = postfixToTree("b 2 + 1 a + *", errors);
    NodeOfExprTree* final_tree_4_6 = postfixToTree("a 1 + b 2 + *", errors);
    QTest::newRow("4.6 Operators: \"*\", \"+\"") << start_tree_4_6 << final_tree_4_6;

    // 4.7 Операторы «-» и «/»
    NodeOfExprTree* start_tree_4_7 = postfixToTree("1 a / b 2 / -", errors);
    NodeOfExprTree* final_tree_4_7 = postfixToTree("b 2 / ~ 1 a / +", errors);
    QTest::newRow("4.7 Operators: \"-\", \"/\"") << start_tree_4_7 << final_tree_4_7;

    // 4.8 Операторы «/» и «-»
    NodeOfExprTree* start_tree_4_8 = postfixToTree("a 1 - 2 b - /", errors);
    NodeOfExprTree* final_tree_4_8 = postfixToTree("a 1 - b ~ 2 + /", errors);
    QTest::newRow("4.8 Operators: \"/\", \"-\"") << start_tree_4_8 << final_tree_4_8;

    // 4.9 Унарные минусы «снаружи»
    NodeOfExprTree* start_tree_4_9 = postfixToTree("2 b + ~ 1 a + ~ +", errors);
    NodeOfExprTree* final_tree_4_9 = postfixToTree("a 1 + ~ b 2 + ~ +", errors);
    QTest::newRow("4.9 Unary cons of \"outside\"") << start_tree_4_9 << final_tree_4_9;

    // 4.10 Унарные минусы «внутри»
    NodeOfExprTree* start_tree_4_10 = postfixToTree("1 ~ a ~ + 2 ~ b ~ + +", errors);
    NodeOfExprTree* final_tree_4_10= postfixToTree("a ~ b ~ + 1 ~ + 2 ~ +", errors);
    QTest::newRow("4.10 Unary cons of \"outside\"") << start_tree_4_10 << final_tree_4_10;

    // 4.11 Унарные минусы «внутри»
    NodeOfExprTree* start_tree_4_11 = postfixToTree("c b +3 + 2 a 1 * + - -", errors);
    NodeOfExprTree* final_tree_4_11= postfixToTree("1 a * b - c + 2 + 3 -", errors);
    QTest::newRow("4.11 Nested parentheses due to binary minus") << start_tree_4_11 << final_tree_4_11;

    // 5. Тесты на сортировку дерева

    // 5.1 Одинаковые операторы «*»
    NodeOfExprTree* start_tree_5_1 = postfixToTree("b a + 2 1 + +", errors);
    NodeOfExprTree* final_tree_5_1 = postfixToTree("a b + 2 + 1 +", errors);
    QTest::newRow("5.1 The first elements need to be changed") << start_tree_5_1 << final_tree_5_1;

    // 5.2 Одинаковые операторы «/»
    NodeOfExprTree* start_tree_5_2 = postfixToTree("a 1 / b 2 / /", errors);
    NodeOfExprTree* final_tree_5_2 = postfixToTree("a 1 / b 2 / /", errors);
    QTest::newRow("2.2 The middle elements need to be changed") << start_tree_5_2 << final_tree_5_2;

    // 5.3 Одинаковые операторы «+»
    NodeOfExprTree* start_tree_5_3 = postfixToTree("a b + 1 2 + +", errors);
    NodeOfExprTree* final_tree_5_3 = postfixToTree("a b + 2 + 1 +", errors);
    QTest::newRow("5.3 The last elements need to be changed") << start_tree_5_3 << final_tree_5_3;

    // 5.4 Первый и последний элементы необходимо поменять
    NodeOfExprTree* start_tree_5_4 = postfixToTree("1 b + 2 a + +", errors);
    NodeOfExprTree* final_tree_5_4 = postfixToTree("a b + 2 + 1 +", errors);
    QTest::newRow("5.4 The first and last elements need to be changed") << start_tree_5_4 << final_tree_5_4;

    // 5.5 Первый и средний элементы необходимо поменять
    NodeOfExprTree* start_tree_5_5 = postfixToTree("b 2 * 1 a * +", errors);
    NodeOfExprTree* final_tree_5_5 = postfixToTree("1 a * 2 b * +", errors);
    QTest::newRow("5.5 The first and middle elements need to be changed") << start_tree_5_5 << final_tree_5_5;

    // 5.6 Последний и средний элементы необходимо поменять
    NodeOfExprTree* start_tree_5_6 = postfixToTree("a 1 + 2 b + +", errors);
    NodeOfExprTree* final_tree_5_6 = postfixToTree("a b + 2 + 1 +", errors);
    QTest::newRow("5.6 The last and middle elements need to be changed") << start_tree_5_6 << final_tree_5_6;

    // 5.7 Элементы в обратном порядке
    NodeOfExprTree* start_tree_5_7 = postfixToTree("1 2 + b a + +", errors);
    NodeOfExprTree* final_tree_5_7 = postfixToTree("a b + 2 + 1 +", errors);
    QTest::newRow("5.7 The elements are in reverse order") << start_tree_5_7 << final_tree_5_7;
}
