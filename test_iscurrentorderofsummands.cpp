#include "test_iscurrentorderofsummands.h"

Test_isCurrentOrderOfSummands::Test_isCurrentOrderOfSummands(QObject *parent)
    : QObject{parent}
{}

void Test_isCurrentOrderOfSummands::testIsCurrentOrderOfSummands()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить результат сравнения
    bool real_result = elem_1.isCurrentOrderOfMultipliers(elem_2);

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_result, exp_result);
}

void Test_isCurrentOrderOfSummands::testIsCurrentOrderOfSummands_data()
{
    QTest::addColumn<OperandOfExpr>("elem_1");
    QTest::addColumn<OperandOfExpr>("elem_2");
    QTest::addColumn<bool>("exp_result");

    // Создать список ошибок для вызова функции создания списка
    QSet<Error> errors;
    // Создать родителей для слагаемого : "+", "-", ""
    NodeOfExprTree* parent_plus = new NodeOfExprTree("+");
    NodeOfExprTree* parent_bin_minus = new NodeOfExprTree("-");
    NodeOfExprTree* parent_is_equal = new NodeOfExprTree();

    // 1. Проверка на правило: сначала слагаемое с одинаковыми внутри себя именами переменных, потом - с различными

    // 1.1 Правильный порядок
    OperandOfExpr elem_1_1_1 = OperandOfExpr{parent_plus, postfixToTree("x x *", errors), false};
    OperandOfExpr elem_1_1_2 = OperandOfExpr{parent_plus, postfixToTree("y z *", errors), false};
    QTest::newRow("1.1 Correct order: the first one is a summand with the same variable names inside it. The current order is correct") << elem_1_1_1 << elem_1_1_2 << true;

    // 1.2 Неправильный порядок
    QTest::newRow("1.2 Correct order: the first one is a summand with the same variable names inside it. The current order is uncorrect") << elem_1_1_2 << elem_1_1_1 << false;

    // 1.3 Первое слагаемое имеет выражение в скобках, порядок верный
    OperandOfExpr elem_1_3_1 = OperandOfExpr{parent_plus, postfixToTree("x x 1 + *", errors), false};
    QTest::newRow("1.3 Correct order: the first one is a summand with the same variable names inside it.\nThe first term has an expression in parentheses, the order is correct") << elem_1_3_1 << elem_1_1_2 << true;

    // 1.4 Первое слагаемое имеет выражение в скобках, порядок неверный
    OperandOfExpr elem_1_4_1 = OperandOfExpr{parent_plus, postfixToTree("y z 1 + *", errors), false};
    QTest::newRow("1.4 Correct order: the first one is a summand with the same variable names inside it.\nThe first term has an expression in parentheses, the order is uncorrect") << elem_1_4_1 << elem_1_1_1 << false;

    // 1.5 Второе слагаемое имеет выражение в скобках, порядок верный
    QTest::newRow("1.5 Correct order: the first one is a summand with the same variable names inside it.\nThe second term has an expression in parentheses, the order is correct") << elem_1_1_1 << elem_1_4_1 << true;

    // 1.6 Первый узел есть выражение в скобках, второй - число
    QTest::newRow("1.6 Correct order: the first one is a summand with the same variable names inside it.\nThe second term has an expression in parentheses, the order is uncorrect") << elem_1_1_2 << elem_1_3_1 << false;

    // 1.7 Оба слагаемых имеют выражение в скобках, порядок верный
    QTest::newRow("1.7 Correct order: the first one is a summand with the same variable names inside it.\nBoth term have expression in parentheses, the order is correct") << elem_1_3_1 << elem_1_4_1 << true;

    // 1.8 Оба слагаемых имеют выражение в скобках, порядок неверный
    QTest::newRow("1.8 Correct order: the first one is a summand with the same variable names inside it.\nBoth term have expression in parentheses, the order is incorrect") << elem_1_4_1 << elem_1_3_1 << false;

    // 1.9 Различная степень переменных, порядок верный
    OperandOfExpr elem_1_9_1 = OperandOfExpr{parent_plus, postfixToTree("x y * z *", errors), false};
    QTest::newRow("1.9 Correct order: the first one is a summand with the same variable names inside it.\nDifferent variables' degrees, the order is correct") << elem_1_1_1 << elem_1_9_1 << true;

    // 1.10 Различная степень переменных, порядок неверный
    QTest::newRow("1.10 Correct order: the first one is a summand with the same variable names inside it.\nDifferent variables' degrees, the order is incorrect") << elem_1_1_2 << elem_1_1_1 << false;

    // 1.11 Много вложенных скобок, порядок верный
    OperandOfExpr elem_1_11_1 = OperandOfExpr{parent_plus, postfixToTree("x x * x x + * x +", errors), false};
    OperandOfExpr elem_1_11_2 = OperandOfExpr{parent_plus, postfixToTree("x x * x y + * x +", errors), false};
    QTest::newRow("1.11 Correct order: the first one is a summand with the same variable names inside it.\nMany nested parentheses, the order is correct") << elem_1_11_1 << elem_1_11_2 << true;

    // 1.12 Много вложенных скобок, порядок неверный
    QTest::newRow("1.12 Correct order: the first one is a summand with the same variable names inside it.\nMany nested parentheses, the order is incorrect") << elem_1_11_2 << elem_1_11_1 << false;

    // 1.13 Равные слагаемые
    QTest::newRow("1.13 Correct order: the first one is a summand with the same variable names inside it.\nEqual terms, the order is correct") << elem_1_1_1 << elem_1_1_1 << true;

    // 2.Проверка на правило: сначала слагаемое с большей степенью переменных

    // 2.1 В первом слагаемом переменных больше, чем во втором
    OperandOfExpr elem_2_1_1 = OperandOfExpr{parent_plus, postfixToTree("a b c * *", errors), false};
    OperandOfExpr elem_2_1_2 = OperandOfExpr{parent_plus, postfixToTree("x y *", errors), false};
    QTest::newRow("2.1 Correct order: first comes the term with a higher degree of variables.\nThere are more variables in the first term than in the second") << elem_2_1_1 << elem_2_1_2 << true;

    // 2.2 Во втором слагаемом переменных больше, чем в первом
    QTest::newRow("2.2 Correct order: first comes the term with a higher degree of variables.\nThere are more variables in the second term than in the first") << elem_2_1_2 << elem_2_1_1 << false;

    // 2.3 Второе слагаемое без переменных
    OperandOfExpr elem_2_3_1 = OperandOfExpr{parent_plus, postfixToTree("1", errors), false};
    QTest::newRow("2.3 Correct order: first comes the term with a higher degree of variables.\nSecond term without variables") << elem_2_1_2 << elem_2_3_1 << true;

    // 2.4 Первое слагаемое  без переменных
    QTest::newRow("2.4 Correct order: first comes the term with a higher degree of variables.\First term without variables") << elem_2_3_1 << elem_2_1_2 << false;

    // 2.5 Первое слагаемое имеет выражение в скобках, порядок верный
    OperandOfExpr elem_2_5_1 = OperandOfExpr{parent_plus, postfixToTree("a b c * 1 + *", errors), false};
    QTest::newRow("2.5 Correct order: first comes the term with a higher degree of variables.\nFirst term has expression in parentheses, the order is correct") << elem_2_5_1 << elem_2_1_2 << true;

    // 2.6 Первое слагаемое имеет выражение в скобках, порядок неверный
    OperandOfExpr elem_2_6_1 = OperandOfExpr{parent_plus, postfixToTree("x y 1 + *", errors), false};
    OperandOfExpr elem_2_6_2 = OperandOfExpr{parent_plus, postfixToTree("a b c * *", errors), false};
    QTest::newRow("2.6 Correct order: first comes the term with a higher degree of variables.\nFirst term has expression in parentheses, the order is incorrect") << elem_2_6_1 << elem_2_6_2 << false;

    // 2.7 Второе слагаемое имеет выражение в скобках, порядок верный
    QTest::newRow("2.7 Correct order: first comes the term with a higher degree of variables.\nSecond term has expression in parentheses, the order is correct") << elem_2_6_2 << elem_2_6_1 << true;

    // 2.8 Второе слагаемое имеет выражение в скобках, порядок неверный
    QTest::newRow("2.8 Correct order: first comes the term with a higher degree of variables.\nSecond term has expression in parentheses, the order is incorrect") << elem_2_1_2 << elem_2_5_1 << false;

    // 2.9 Оба слагаемых имеют выражение в скобках, порядок верный
    QTest::newRow("2.9 Correct order: first comes the term with a higher degree of variables.\nBoth terms have expression in parentheses, the order is correct") << elem_2_5_1 << elem_2_6_1 << true;

    // 2.10 Оба слагаемых имеют выражение в скобках, порядок неверный
    QTest::newRow("2.10 Correct order: first comes the term with a higher degree of variables.\nBoth terms have expression in parentheses, the order is incorrect") << elem_2_6_1 << elem_2_5_1 << false;

    // 2.11 Несколько слагаемых, порядок верный
    OperandOfExpr elem_2_11_1 = OperandOfExpr{parent_plus, postfixToTree("a b 1 + * c 2 + *", errors), false};
    OperandOfExpr elem_2_11_2 = OperandOfExpr{parent_plus, postfixToTree("x y 1 + * 3 2 + *", errors), false};
    QTest::newRow("2.11 Correct order: first comes the term with a higher degree of variables.\nSeveral terms, the order is correct") << elem_2_11_1 << elem_2_11_2 << true;

    // 2.12 Несколько слагаемых, порядок неверный
    QTest::newRow("2.12 Correct order: first comes the term with a higher degree of variables.\nSeveral terms, the order is incorrect") << elem_2_11_2 << elem_2_11_1 << false;

    // 2.13 Вложенные выражения в скобках, порядок верный
    OperandOfExpr elem_2_13_1 = OperandOfExpr{parent_plus, postfixToTree("x 1 y z 2 + * + *", errors), false};
    OperandOfExpr elem_2_13_2 = OperandOfExpr{parent_plus, postfixToTree("a b 1 + *", errors), false};
    QTest::newRow("2.13 Correct order: first comes the term with a higher degree of variables.\nNested expressions in parentheses, the order is correct") << elem_2_13_1 << elem_2_13_2 << true;

    // 2.14 Вложенные выражения в скобках, порядок неверный
    QTest::newRow("2.14 Correct order: first comes the term with a higher degree of variables.\nNested expressions in parentheses, the order is incorrect") << elem_2_13_2 << elem_2_13_1 << false;

    // 2.15 Имена переменные одинаковые, порядок верный
    OperandOfExpr elem_2_15_1 = OperandOfExpr{parent_plus, postfixToTree("x x x * *", errors), false};
    OperandOfExpr elem_2_15_2 = OperandOfExpr{parent_plus, postfixToTree("y y *", errors), false};
    QTest::newRow("2.15 Correct order: first comes the term with a higher degree of variables.\nVariables' names are equal, the order is correct") << elem_2_15_1 << elem_2_15_2 << true;

    // 2.16 Имена переменные одинаковые, порядок неверный
    QTest::newRow("2.16 Correct order: first comes the term with a higher degree of variables.\nVariables' names are equal, the order is incorrect") << elem_2_15_2 << elem_2_15_1 << false;

    // 3.Проверка на правило: по алфавиту, учитывая только имена переменные

    // 3.1 Отличны первые переменные, порядок верный
    OperandOfExpr elem_3_1_1 = OperandOfExpr{parent_plus, postfixToTree("x b c * *", errors), false};
    QTest::newRow("3.1 Correct order: alphabetically, considering only the names of the variables.\nThe first variables are excellent, the order is correct") << elem_2_1_1 << elem_3_1_1 << true;

    // 3.2 Отличны первые переменные, порядок неверный
    QTest::newRow("3.2 Correct order: alphabetically, considering only the names of the variables.\nThe first variables are excellent, the order is uncorrect") << elem_3_1_1 << elem_2_1_1 << false;

    // 3.3 Отличны вторые переменные, порядок верный
    OperandOfExpr elem_3_3_1 = OperandOfExpr{parent_plus, postfixToTree("a x c * *", errors), false};
    QTest::newRow("3.3 Correct order: alphabetically, considering only the names of the variables.\nThe second variables are different, the order is correct") << elem_2_1_1 << elem_3_3_1 << true;

    // 3.4 Отличны вторые переменные, порядок неверный
    QTest::newRow("3.4 Correct order: alphabetically, considering only the names of the variables.\nThe second variables are different, the order is incorrect") << elem_3_3_1 << elem_2_1_1 << false;

    // 3.5 Отличны последние переменные, порядок верный
    OperandOfExpr elem_3_5_1 = OperandOfExpr{parent_plus, postfixToTree("a b * x *", errors), false};
    QTest::newRow("3.5 Correct order: alphabetically, considering only the names of the variables.\nThe last variables are different, the order is correct") << elem_2_1_1 << elem_3_5_1 << true;

    // 3.6 Отличны последние переменные, порядок неверный
    QTest::newRow("3.6 Correct order: alphabetically, considering only the names of the variables.\nThe last variables are different, the order is incorrect") << elem_3_5_1 << elem_2_1_1 << false;

    // 3.7 Первое слагаемое имеет выражение в скобках, порядок верный
    OperandOfExpr elem_3_7_1 = OperandOfExpr{parent_plus, postfixToTree("a b c + *", errors), false};
    QTest::newRow("3.7 Correct order: alphabetically, considering only the names of the variables.\nFirst term has expression in parentheses, the order is correct") << elem_3_7_1 << elem_3_5_1 << true;

    // 3.8 Первое слагаемое имеет выражение в скобках, порядок неверный
    QTest::newRow("3.8 Correct order: alphabetically, considering only the names of the variables.\nFirst term has expression in parentheses, the order is incorrect") << elem_3_5_1 << elem_3_7_1 << false;

    // 3.9 Второе слагаемое имеет выражение в скобках, порядок верный
    OperandOfExpr elem_3_9_1 = OperandOfExpr{parent_plus, postfixToTree("a b x + *", errors), false};
    QTest::newRow("3.9 Correct order: alphabetically, considering only the names of the variables.\nSecond term has expression in parentheses, the order is correct") << elem_2_6_2 << elem_3_9_1 << true;

    // 3.10 Второе слагаемое имеет выражение в скобках, порядок неверный
    QTest::newRow("3.10 Correct order: alphabetically, considering only the names of the variables.\nSecond term has expression in parentheses, the order is incorrect") << elem_3_9_1 << elem_2_6_2 << false;

    // 3.11 Оба слагаемых имеют выражение в скобках, порядок верный
    OperandOfExpr elem_3_11_1 = OperandOfExpr{parent_plus, postfixToTree("a b c + *", errors), false};
    QTest::newRow("3.11 Correct order: alphabetically, considering only the names of the variables.\nBoth terms have expression in parentheses, the order is correct") << elem_3_11_1 << elem_3_9_1 << true;

    // 3.12 Оба слагаемых имеют выражение в скобках, порядок неверный
    QTest::newRow("3.12 Correct order: alphabetically, considering only the names of the variables.\nBoth terms have expression in parentheses, the order is incorrect") << elem_3_9_1 << elem_3_11_1 << false;

    // 3.13 Вложенные выражения в скобках, порядок верный
    OperandOfExpr elem_3_13_1 = OperandOfExpr{parent_plus, postfixToTree("a b c d 1 + * + *", errors), false};
    OperandOfExpr elem_3_13_2 = OperandOfExpr{parent_plus, postfixToTree("a b c x 1 + * + *", errors), false};
    QTest::newRow("3.13 Correct order: alphabetically, considering only the names of the variables.\nNested expressions in parentheses, the order is correct") << elem_3_13_1 << elem_3_13_2 << true;

    // 3.14 Вложенные выражения в скобках, порядок неверный
    QTest::newRow("3.14 Correct order: alphabetically, considering only the names of the variables.\nNested expressions in parentheses, the order is incorrect") << elem_3_13_2 << elem_3_13_1 << false;

    // 3.15 Равные слагаемые
    QTest::newRow("3.15 Correct order: alphabetically, considering only the names of the variables.\nEqual terms, the order is correct") << elem_2_1_1 << elem_2_1_1 << true;

    // 4.Проверка на правило: от большего количества элементов слагаемого к меньшему

    // 4.1 В первом слагаемом больше элементов, чем во втором
    OperandOfExpr expr_4_1_1 = OperandOfExpr{parent_plus, postfixToTree("2 3 * a b * *", errors), false};
    OperandOfExpr expr_4_1_2 = OperandOfExpr{parent_plus, postfixToTree("4 a b * *", errors), false};
    QTest::newRow("4.1 Correct order: from more elements of the summand to fewer.\nThere are more elements in the first term than in the second") << expr_4_1_1 << expr_4_1_2 << true;

    // 4.2 Во втором слагаемом больше элементов, чем в первом
    QTest::newRow("4.2 Correct order: from more elements of the summand to fewer.\nThere are more elements in the second term than in the first") << expr_4_1_2 << expr_4_1_1 << false;

    // 4.3 Первое слагаемое имеет выражение в скобках, порядок верный
    OperandOfExpr expr_4_3_1 = OperandOfExpr{parent_plus, postfixToTree("2 a b * 3 + *", errors), false};
    QTest::newRow("4.3 Correct order: from more elements of the summand to fewer.\nFirst term has expression in parentheses, the order is correct") << expr_4_3_1 << expr_4_1_2 << true;

    // 4.4 Первое слагаемое имеет выражение в скобках, порядок неверный
    OperandOfExpr expr_4_4_1 = OperandOfExpr{parent_plus, postfixToTree("4 a b + *", errors), false};
    QTest::newRow("4.4 Correct order: from more elements of the summand to fewer.\nFirst term has expression in parentheses, the order is incorrect") << expr_4_4_1 << expr_4_1_1 << false;

    // 4.5 Второе слагаемое имеет выражение в скобках, порядок верный
    QTest::newRow("4.5 Correct order: from more elements of the summand to fewer.\nSecond term has expression in parentheses, the order is correct") << expr_4_1_1 << expr_4_4_1 << true;

    // 4.6 Второе слагаемое имеет выражение в скобках, порядок неверный
    QTest::newRow("4.6 Correct order: from more elements of the summand to fewer.\nSecond term has expression in parentheses, the order is incorrect") << expr_4_1_2 << expr_4_3_1 << false;

    // 4.7 Оба слагаемых имеют выражение в скобках, порядок верный
    QTest::newRow("4.7 Correct order: from more elements of the summand to fewer.\nBoth terms have expression in parentheses, the order is correct") << expr_4_3_1 << expr_4_4_1 << true;

    // 4.8 Оба слагаемых имеют выражение в скобках, порядок неверный
    QTest::newRow("4.8 Correct order: from more elements of the summand to fewer.\nBoth terms have expression in parentheses, the order is incorrect") << expr_4_4_1 << expr_4_3_1 << false;

    // 4.9 Вложенные выражения в скобках, порядок верный
    OperandOfExpr expr_4_9_1 = OperandOfExpr{parent_plus, postfixToTree("4 a c d + * b + *", errors), false};
    QTest::newRow("4.9 Correct order: from more elements of the summand to fewer.\nNested expressions in parentheses, the order is correct") << expr_4_9_1 << expr_4_3_1 << true;

    // 4.10 Вложенные выражения в скобках, порядок неверный
    QTest::newRow("4.10 Correct order: from more elements of the summand to fewer.\nNested expressions in parentheses, the order is incorrect") << expr_4_3_1 << expr_4_9_1 << false;

    // 4.11 Равные слагаемые, разные множители
    OperandOfExpr expr_4_11_1 = OperandOfExpr{parent_plus, postfixToTree("1 a * b c * *", errors), false};
    OperandOfExpr expr_4_11_2 = OperandOfExpr{parent_plus, postfixToTree("2 a * b c * *", errors), false};
    QTest::newRow("4.11 Correct order: from more elements of the summand to fewer.\nEqual terms, different multipliers") << expr_4_11_1 << expr_4_11_2 << true;

    // 5.Проверка на правило: от большего количества выражений в скобках в слагаемом к меньшему

    // 5.1 В первом слагаемом больше выражений в скобках, чем во втором
    OperandOfExpr expr_5_1_1 = OperandOfExpr{parent_plus, postfixToTree("a b c + * 2 1 + *", errors), false};
    OperandOfExpr expr_5_1_2 = OperandOfExpr{parent_plus, postfixToTree("a b c + 2 1 + + *", errors), false};
    QTest::newRow("5.1 Correct order: from more expressions in parentheses in the summand to fewer.\nThere are more expressions in parentheses in the first term than in the second") << expr_5_1_1 << expr_5_1_2 << true;

    // 5.2 Во втором слагаемом больше выражений в скобках, чем в первом
    QTest::newRow("5.2 Correct order: from more expressions in parentheses in the summand to fewer.\nThere are more expressions in parentheses in the second term than in the first one.") << expr_5_1_2 << expr_5_1_1 << false;

    // 5.3 Слагаемые состоят только из скобок, порядок верный
    OperandOfExpr expr_5_3_1 = OperandOfExpr{parent_plus, postfixToTree("b c + 2 1 + * d 3 + *", errors), false};
    OperandOfExpr expr_5_3_2 = OperandOfExpr{parent_plus, postfixToTree("b c + 2 1 + + d 3 + *", errors), false};
    QTest::newRow("5.3 Correct order: from more expressions in parentheses in the summand to fewer.\nTerms are exist of parentheses only, the order is correct") << expr_5_3_1 << expr_5_3_2 << true;

    // 5.4 Слагаемые состоят только из скобок, порядок неверный
    QTest::newRow("5.4 Correct order: from more expressions in parentheses in the summand to fewer.\nTerms are exist of parentheses only, the order is incorrect") << expr_5_3_2 << expr_5_3_1 << false;

    // 5.5 Вложенные выражения в скобках, порядок верный
    OperandOfExpr expr_5_5_1 = OperandOfExpr{parent_plus, postfixToTree("b c + 2 1 + *", errors), false};
    OperandOfExpr expr_5_5_2 = OperandOfExpr{parent_plus, postfixToTree("b c 2 1 + * +", errors), false};
    QTest::newRow("5.5 Correct order: from more expressions in parentheses in the summand to fewer.\nNested expressions in parentheses, the order is correct") << expr_5_5_1 << expr_5_5_2 << true;

    // 5.6 Вложенные выражения в скобках, порядок неверный
    QTest::newRow("5.6 Correct order: from more expressions in parentheses in the summand to fewer.\nNested expressions in parentheses, the order is incorrect") << expr_5_5_2 << expr_5_5_1 << false;

    // 5.7 Равные слагаемые, различные операторы: «+», «-»
    OperandOfExpr expr_5_7_1 = OperandOfExpr{parent_plus, postfixToTree("1 a b + *", errors), false};
    OperandOfExpr expr_5_7_2 = OperandOfExpr{parent_plus, postfixToTree("1 a b - *", errors), false};
    QTest::newRow("5.7 Correct order: from more expressions in parentheses in the summand to fewer.\nEqual terms, different operators: «+», «-»") << expr_5_7_1 << expr_5_7_2 << true;

    // 5.8 Равные слагаемые, различные операторы: «-», «+»
    QTest::newRow("5.8 Correct order: from more expressions in parentheses in the summand to fewer.\nEqual terms, different operators: «-», «+»") << expr_5_7_2 << expr_5_7_1 << true;

    // 6. Проверка на правило: от большего числа к меньшему (если слагаемые состоят из одного числа

    OperandOfExpr p_1 = OperandOfExpr{parent_plus, postfixToTree("1", errors), false};
    OperandOfExpr p_3 = OperandOfExpr{parent_plus, postfixToTree("3", errors), false};
    OperandOfExpr p_un_1 = OperandOfExpr{parent_plus, postfixToTree("1 ~", errors), false};
    OperandOfExpr p_un_3 = OperandOfExpr{parent_plus, postfixToTree("3 ~", errors), false};
    OperandOfExpr p_un_un_1 = OperandOfExpr{parent_plus, postfixToTree("1 ~ ~", errors), false};
    OperandOfExpr p_un_un_3 = OperandOfExpr{parent_plus, postfixToTree("3 ~ ~", errors), false};
    OperandOfExpr p_un_un_un_1 = OperandOfExpr{parent_plus, postfixToTree("1 ~ ~ ~", errors), false};
    OperandOfExpr p_un_un_un_3 = OperandOfExpr{parent_plus, postfixToTree("3 ~ ~ ~", errors), false};
    OperandOfExpr m_1 = OperandOfExpr{parent_bin_minus, postfixToTree("1", errors), false};
    OperandOfExpr m_3 = OperandOfExpr{parent_bin_minus, postfixToTree("3", errors), false};
    OperandOfExpr m_un_un_1 = OperandOfExpr{parent_bin_minus, postfixToTree("1 ~ ~", errors), false};
    OperandOfExpr m_un_un_3 = OperandOfExpr{parent_bin_minus, postfixToTree("3 ~ ~", errors), false};
    OperandOfExpr p_11 = OperandOfExpr{parent_plus, postfixToTree("11", errors), false};
    OperandOfExpr p_111 = OperandOfExpr{parent_plus, postfixToTree("111", errors), false};
    OperandOfExpr p_3p1 = OperandOfExpr{parent_plus, postfixToTree("3,1", errors), false};
    OperandOfExpr p_3p2 = OperandOfExpr{parent_plus, postfixToTree("3,2", errors), false};
    OperandOfExpr p_31 = OperandOfExpr{parent_plus, postfixToTree("31", errors), false};
    OperandOfExpr p_31p2 = OperandOfExpr{parent_plus, postfixToTree("31,2", errors), false};
    OperandOfExpr n_1 = OperandOfExpr{parent_is_equal, postfixToTree("1", errors), true};

    // 6.1 Два положительных числа, первое меньше второго
    QTest::newRow("6.1 Correct order: number_1 > number_2.\nTwo positive numbers, the first one is less than the second one") << p_1 << p_3 << false;

    // 6.2 Два положительных числа, первое больше второго
    QTest::newRow("6.2 Correct order: number_1 > number_2.\nTwo positive numbers, the first is greater than the second") << p_3 << p_1 << true;

    // 6.3 Первое число отрицательное, второе - положительное
    QTest::newRow("6.3 Correct order: number_1 > number_2.\nFirst number is positive, second is negative") << p_un_3 << p_1 << false;

    // 6.4 Первое число положительное, второе - отрицательное
    QTest::newRow("6.4 Correct order: number_1 > number_2.\nFirst number is negative, second is positive") << p_1 << p_un_3 << true;

    // 6.5 Оба числа отрицательные, первое меньше второго
    QTest::newRow("6.5 Correct order: number_1 > number_2.\nBoth numbers are negative, first < second") << p_un_3 << p_un_1 << false;

    // 6.6 Оба числа отрицательные, первое больше второго
    QTest::newRow("6.6 Correct order: number_1 > number_2.\nBoth numbers are negative, first > second") << p_un_1 << p_un_3 << true;

    // 6.7 Чётное кол-во унарных минусов, первое число меньше второго
    QTest::newRow("6.7 Correct order: number_1 > number_2.\nEven number of unary minuses, first < second") << p_un_un_1 << p_un_un_3 << false;

    // 6.8 Чётное кол-во унарных минусов, первое число больше второго
    QTest::newRow("6.8 Correct order: number_1 > number_2.\nEven number of unary minuses, first > second") << p_un_un_3 << p_un_un_1 << true;

    // 6.9 Нечётное кол-во унарных минусов, первое число меньше второго
    QTest::newRow("6.9 Correct order: number_1 > number_2.\nNot even number of unary minuses, first < second") << p_un_un_un_3 << p_un_un_un_1 << false;

    // 6.10 Нечётное кол-во унарных минусов, первое число больше второго
    QTest::newRow("6.10 Correct order: number_1 > number_2.\nNot even number of unary minuses, first > second") << p_un_un_un_1 << p_un_un_un_3 << true;

    // 6.11 Перед первым числом унарный минус
    QTest::newRow("6.11 Correct order: number_1 > number_2.\nUnary minus before first number") << m_3 << p_1 << true;

    // 6.12 Перед вторым числом унарный минус
    QTest::newRow("6.12 Correct order: number_1 > number_2.\nUnary minus before second number") << p_1 << m_3 << false;

    // 6.13 Перед обоими числами бинарный минус, порядок верный
    QTest::newRow("6.13 Correct order: number_1 > number_2.\nUnary minus before both numbers, the order is correct") << m_3 << m_1 << true;

    // 6.14 Перед обоими числами бинарный минус, порядок неверный
    QTest::newRow("6.14 Correct order: number_1 > number_2.\nUnary minus before both numbers, the order is incorrect") << m_1 << m_3 << false;

    // 6.15 Бинарный минус с унарным, порядок верный
    QTest::newRow("6.15 Correct order: number_1 > number_2.\nBinary minus with unary minus, the order is correct") << m_un_un_3 << m_un_un_1 << true;

    // 6.16 Бинарный минус с унарным, порядок неверный
    QTest::newRow("6.16 Correct order: number_1 > number_2.\nBinary minus with unary minus, the order is incorrect") << m_un_un_1 << m_un_un_3 << false;

    // 6.17 Одинаковые цифры в числах, порядок верный
    QTest::newRow("6.17 Correct order: number_1 > number_2.\nEqual digits in numbers, the order is correct") << p_11 << p_111 << false;

    // 6.18 Одинаковые цифры в числах, порядок неверный
    QTest::newRow("6.18 Correct order: number_1 > number_2.\nEqual digits in numbers, the order is incorrect") << p_111 << p_11 << true;

    // 6.19 Первый множитель с плавающей запятой, порядок верный
    QTest::newRow("6.19 Correct order: number_1 > number_2.\nFirst float multiplier, the order is correct") << p_3p1 << p_31 << true;

    // 6.20 Первый множитель с плавающей запятой, порядок неверный
    QTest::newRow("6.20 Correct order: number_1 > number_2.\nFirst float multiplier, the order is incorrect") << p_31p2 << p_31 << false;

    // 6.21 Оба множителя с плавающей запятой, порядок верный
    QTest::newRow("6.21 Correct order: number_1 > number_2.\nBoth float multipliers, the order is correct") << p_3p1 << p_3p2 << true;

    // 6.22 Оба множителя с плавающей запятой, порядок неверный
    QTest::newRow("6.22 Correct order: number_1 > number_2.\nBoth float multipliers, the order is incorrect") << p_3p2 << p_3p1 << false;

    // 6.23 Равные слагаемые: целые числа
    QTest::newRow("6.23 Correct order: number_1 > number_2.\nEqual terms: integers") << p_1 << p_1 << true;

    // 6.24 Равные слагаемые: числа с плавающей точкой
    QTest::newRow("6.24 Correct order: number_1 > number_2.\nEqual terms: floats") << p_3p2 << p_3p2 << true;

    // 6.25 Равные слагаемые: числа с унарными минусами (у первого один, у второго три «~»)
    QTest::newRow("6.25 Correct order: number_1 > number_2.\nEqual terms: unary minus numbers (first has 1, second has 3)") << p_un_1 << p_un_un_un_1 << true;

    // 6.26 Равные слагаемые: числа с унарными минусами (у первого три, у второго один «~»)
    QTest::newRow("6.26 Correct order: number_1 > number_2.\nEqual terms: unary minus numbers (first has 3, second has 1)") << p_un_un_un_1 << p_un_1 << true;

    // 6.27 Равные слагаемые, различные родители: «-», «+»
    QTest::newRow("6.27 Correct order: number_1 > number_2.\nEqual terms, different parents: «-», «+»") << m_1 << p_un_1 << true;

    // 6.28 Равные слагаемые, различные родители: «+», «-»
    QTest::newRow("6.28 Correct order: number_1 > number_2.\nEqual terms, different parents: «+», «-»") << p_un_1 << m_1 << true;

    // 6.29 Равные слагаемые, различные родители: у первого слагаемого нет родителя
    QTest::newRow("6.29 Correct order: number_1 > number_2.\nEqual terms, different parents: first has no parent") << n_1 << p_1 << true;

    // 6.30 Равные слагаемые, различные родители: у второго слагаемого нет родителя
    QTest::newRow("6.30 Correct order: number_1 > number_2.\nEqual terms, different parents: second has no parent") << p_1 << n_1 << true;

    // 7.Унарные минусы, не влияющие на порядок

    // 7.1 Первое слагаемое с унарным минусом, порядок верный
    OperandOfExpr expr_7_1_1 = OperandOfExpr{parent_plus, postfixToTree("x x ~ *", errors), false};
    QTest::newRow("7.1 Unary cons that do not affect the order.\nThe first term with a unary minus, the order is correct") << expr_7_1_1 << elem_1_1_2 << true;

    // 7.2 Первое слагаемое с унарным минусом, порядок неверный
    OperandOfExpr expr_7_2_1 = OperandOfExpr{parent_plus, postfixToTree("y z ~ *", errors), false};
    QTest::newRow("7.2 Unary cons that do not affect the order.\nThe first term with a unary minus, the order is uncorrect") << expr_7_2_1 << elem_1_1_1 << false;

    // 7.3 Второе слагаемое с унарным минусом, порядок верный
    OperandOfExpr expr_7_3_1 = OperandOfExpr{parent_plus, postfixToTree("y z ~ *", errors), false};
    QTest::newRow("7.3 Unary cons that do not affect the order.\nSecond term with unary minus, the order is correct") << elem_1_1_1 << expr_7_3_1 << true;

    // 7.4 Второе слагаемое с унарным минусом, порядок неверный
    OperandOfExpr expr_7_4_1 = OperandOfExpr{parent_plus, postfixToTree("x x ~ *", errors), false};
    QTest::newRow("7.4 Unary cons that do not affect the order.\nSecond term with unary minus, the order is incorrect") << elem_1_1_2 << expr_7_4_1 << false;

    // 7.5 Несколько унарных минусов, порядок верный
    OperandOfExpr expr_7_5_1 = OperandOfExpr{parent_plus, postfixToTree("x ~ ~ x ~ ~ *", errors), false};
    OperandOfExpr expr_7_5_2 = OperandOfExpr{parent_plus, postfixToTree("y ~ ~ z ~ ~ *", errors), false};
    QTest::newRow("7.5 Unary cons that do not affect the order.\nSeveral unary minuses, the order is correct") << expr_7_5_1 << expr_7_5_2 << true;

    // 7.6 Несколько унарных минусов, порядок неверный
    QTest::newRow("7.6 Unary cons that do not affect the order.\nSeveral unary minuses, the order is incorrect") << expr_7_5_2 << expr_7_5_1 << false;

    // 7.7 Оба слагаемых есть выражение в скобках, порядок верный
    OperandOfExpr expr_7_7_1 = OperandOfExpr{parent_plus, postfixToTree("x x + ~", errors), false};
    OperandOfExpr expr_7_7_2 = OperandOfExpr{parent_plus, postfixToTree("y z + ~", errors), false};
    QTest::newRow("7.7 Unary cons that do not affect the order.\nBoth terms are expressions in parentheses, the order is correct") << expr_7_7_1 << expr_7_7_2 << true;

    // 7.8 Оба слагаемых есть выражение в скобках, порядок неверный
    QTest::newRow("7.8 Unary cons that do not affect the order.\nBoth terms are expressions in parentheses, the order is incorrect") << expr_7_7_2 << expr_7_7_1 << false;

    // 7.9 Унарный минус в выражениях в скобке, порядок верный
    OperandOfExpr expr_7_9_1 = OperandOfExpr{parent_plus, postfixToTree("2 a b ~ * 3 + *", errors), false};
    OperandOfExpr expr_7_9_2 = OperandOfExpr{parent_plus, postfixToTree("4 a b ~ + *", errors), false};
    QTest::newRow("7.9 Unary cons that do not affect the order.\nUnary minus in expressions in parentheses, the order is correct") << expr_7_9_1 << expr_7_9_2 << true;

    // 7.10 Унарный минус в выражениях в скобке, порядок неверный
    QTest::newRow("7.10 Unary cons that do not affect the order.\nUnary minus in expressions in parentheses, the order is incorrect") << expr_7_9_2 << expr_7_9_1 << false;
}
