/*!
* \file
* \brief Файл содержит реализацию методов класса Test_isCurrentOrderOfParenthesisedExpressions для тестирования метода NodeOfExprTree::isCurrentOrderOfParenthesisedExpressions программы nequalityStandardizer.
*/

#include "test_iscurrentorderofparenthesisedexpressions.h"

Test_isCurrentOrderOfParenthesisedExpressions::Test_isCurrentOrderOfParenthesisedExpressions(
    QObject *parent)
    : QObject{parent}
{}

void Test_isCurrentOrderOfParenthesisedExpressions::testIsCurrentOrderOfParenthesisedExpressions()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить результат сравнения
    bool real_result = elem_1.isCurrentOrderOfParenthesisedExpressions(elem_2);

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_result, exp_result);
}

void Test_isCurrentOrderOfParenthesisedExpressions::testIsCurrentOrderOfParenthesisedExpressions_data()
{
    QTest::addColumn<OperandOfExpr>("elem_1");
    QTest::addColumn<OperandOfExpr>("elem_2");
    QTest::addColumn<bool>("exp_result");

    // Создать список ошибок для вызова функции создания списка
    QSet<Error> errors;
    // Создать родителей для множителя : "*"
    NodeOfExprTree* parent = new NodeOfExprTree("*");

    // 1. Проверка на правило: от большей степени переменной n-ого слагаемого к меньшей (где n = 1, 2, 3… до тех пор, пока не установится неравенство или слагаемые такого номера не существуют)

    // 1.1 При проверке первой пары слагаемых определился верный порядок
    OperandOfExpr elem_1_1_1 = OperandOfExpr{parent, postfixToTree("a x * b d + +", errors), false};
    OperandOfExpr elem_1_1_2 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    QTest::newRow("1.1 Correct order: from a higher degree of the nth term variable to a lower one.\nWhen checking the first pair of terms, the correct order was determined.") << elem_1_1_1 << elem_1_1_2 << true;

    // 1.2 При проверке первой пары слагаемых определился неверный порядок
    OperandOfExpr elem_1_2_1 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    OperandOfExpr elem_1_2_2 = OperandOfExpr{parent, postfixToTree("a x * b d + +", errors), false};
    QTest::newRow("1.2 Correct order: from a higher degree of the nth term variable to a lower one.\nWhen checking the first pair of terms, the incorrect order was determined.") << elem_1_2_1 << elem_1_2_2 << false;

    // 1.3 При проверке средней пары слагаемых определился верный порядок
    OperandOfExpr elem_1_3_1 = OperandOfExpr{parent, postfixToTree("a b x * + d +", errors), false};
    OperandOfExpr elem_1_3_2 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    QTest::newRow("1.3 Correct order: from a higher degree of the nth term variable to a lower one.\nWhen checking the average pair of terms, the correct order was determined.") << elem_1_3_1 << elem_1_3_2 << true;

    // 1.4 При проверке средней пары слагаемых определился неверный порядок
    OperandOfExpr elem_1_4_1 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    OperandOfExpr elem_1_4_2 = OperandOfExpr{parent, postfixToTree("a b x * + d +", errors), false};
    QTest::newRow("1.4 Correct order: from a higher degree of the nth term variable to a lower one.\nWhen checking the average pair of terms, the incorrect order was determined.") << elem_1_4_1 << elem_1_4_2 << false;

    // 1.5 При проверке последней пары слагаемых определился верный порядок
    OperandOfExpr elem_1_5_1 = OperandOfExpr{parent, postfixToTree("a b + c x * +", errors), false};
    OperandOfExpr elem_1_5_2 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    QTest::newRow("1.5 Correct order: from a higher degree of the nth term variable to a lower one.\nWhen checking the last pair of terms, the correct order was determined.") << elem_1_5_1 << elem_1_5_2 << true;

    // 1.6 При проверке последней пары слагаемых определился неверный порядок
    OperandOfExpr elem_1_6_1 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    OperandOfExpr elem_1_6_2 = OperandOfExpr{parent, postfixToTree("a b + c x * +", errors), false};
    QTest::newRow("1.6 Correct order: from a higher degree of the nth term variable to a lower one.\nWhen checking the last pair of terms, the incorrect order was determined.") << elem_1_6_1 << elem_1_6_2 << false;

    // 1.7 Выражения состоят из множителей, порядок верный
    OperandOfExpr elem_1_7_1 = OperandOfExpr{parent, postfixToTree("a b * c d * *", errors), false};
    OperandOfExpr elem_1_7_2 = OperandOfExpr{parent, postfixToTree("a b c * *", errors), false};
    QTest::newRow("1.7 Correct order: from a higher degree of the nth term variable to a lower one.\nExpressions consist of multipliers, the order is correct") << elem_1_7_1 << elem_1_7_2 << true;

    // 1.8 Выражения состоят из множителей, порядок неверный
    OperandOfExpr elem_1_8_1 = OperandOfExpr{parent, postfixToTree("a b c * *", errors), false};
    OperandOfExpr elem_1_8_2 = OperandOfExpr{parent, postfixToTree("a b * c d * *", errors), false};
    QTest::newRow("1.8 Correct order: from a higher degree of the nth term variable to a lower one.\nExpressions consist of multipliers, the order is incorrect") << elem_1_8_1 << elem_1_8_2 << false;

    // 1.9 Вложенные выражения в скобках, порядок верный
    OperandOfExpr elem_1_9_1 = OperandOfExpr{parent, postfixToTree("a b 1 + * c d + +", errors), false};
    OperandOfExpr elem_1_9_2 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    QTest::newRow("1.9 Correct order: from a higher degree of the nth term variable to a lower one.\nNested expressions in parentheses, the order is correct") << elem_1_9_1 << elem_1_9_2 << true;

    // 1.10 Вложенные выражения в скобках, порядок неверный
    OperandOfExpr elem_1_10_1 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    OperandOfExpr elem_1_10_2 = OperandOfExpr{parent, postfixToTree("a b 1 + * c d + +", errors), false};
    QTest::newRow("1.10 Correct order: from a higher degree of the nth term variable to a lower one.\nNested expressions in parentheses, the order is incorrect") << elem_1_10_1 << elem_1_10_2 << false;


    // 2. Проверка на правило: по алфавиту, учитывая только переменные

    // 2.1 Отличны первые переменные, порядок верный
    OperandOfExpr elem_2_1_1 = OperandOfExpr{parent, postfixToTree("a b + c a + +", errors), false};
    OperandOfExpr elem_2_1_2 = OperandOfExpr{parent, postfixToTree("x b + c +", errors), false};
    QTest::newRow("2.1 Correct order: alphabetically, considering only variables.\nThe first variables are difficult, the order is correct") << elem_2_1_1 << elem_2_1_2 << true;

    // 2.2 Отличны первые переменные, порядок неверный
    OperandOfExpr elem_2_2_1 = OperandOfExpr{parent, postfixToTree("x b + c a + +", errors), false};
    OperandOfExpr elem_2_2_2 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    QTest::newRow("2.2 Correct order: alphabetically, considering only variables.\nThe first variables are difficult, the order is incorrect") << elem_2_2_1 << elem_2_2_2 << false;

    // 2.3 Отличны вторые переменные, порядок верный
    OperandOfExpr elem_2_3_1 = OperandOfExpr{parent, postfixToTree("a b + c a + +", errors), false};
    OperandOfExpr elem_2_3_2 = OperandOfExpr{parent, postfixToTree("a x + c +", errors), false};
    QTest::newRow("2.3 Correct order: alphabetically, considering only variables.\nThe second variables are difficult, the order is correct") << elem_2_3_1 << elem_2_3_2 << true;

    // 2.4 Отличны вторые переменные, порядок неверный
    OperandOfExpr elem_2_4_1 = OperandOfExpr{parent, postfixToTree("a x + c a + +", errors), false};
    OperandOfExpr elem_2_4_2 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    QTest::newRow("2.4 Correct order: alphabetically, considering only variables.\nThe second variables are difficult, the order is incorrect") << elem_2_4_1 << elem_2_4_2 << false;

    // 2.5 Отличны последние переменные, порядок верный
    OperandOfExpr elem_2_5_1 = OperandOfExpr{parent, postfixToTree("a b + c a + +", errors), false};
    OperandOfExpr elem_2_5_2 = OperandOfExpr{parent, postfixToTree("a b + x +", errors), false};
    QTest::newRow("2.5 Correct order: alphabetically, considering only variables.\nThe last variables are difficult, the order is correct") << elem_2_5_1 << elem_2_5_2 << true;

    // 2.6 Отличны последние переменные, порядок неверный
    OperandOfExpr elem_2_6_1 = OperandOfExpr{parent, postfixToTree("a b + x a + +", errors), false};
    OperandOfExpr elem_2_6_2 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    QTest::newRow("2.6 Correct order: alphabetically, considering only variables.\nThe last variables are difficult, the order is incorrect") << elem_2_6_1 << elem_2_6_2 << false;

    // 2.7 Выражения состоят из множителей, порядок верный
    OperandOfExpr elem_2_7_1 = OperandOfExpr{parent, postfixToTree("a b * c a * *", errors), false};
    OperandOfExpr elem_2_7_2 = OperandOfExpr{parent, postfixToTree("a x * c *", errors), false};
    QTest::newRow("2.7 Correct order: alphabetically, considering only variables.\nExpressions consist of multipliers, the order is correct") << elem_2_7_1 << elem_2_7_2 << true;

    // 2.8 Выражения состоят из множителей, порядок верный
    OperandOfExpr elem_2_8_1 = OperandOfExpr{parent, postfixToTree("a x * c a * *", errors), false};
    OperandOfExpr elem_2_8_2 = OperandOfExpr{parent, postfixToTree("a b * c *", errors), false};
    QTest::newRow("2.8 Correct order: alphabetically, considering only variables.\nExpressions consist of multipliers, the order is incorrect") << elem_2_8_1 << elem_2_8_2 << false;

    // 2.9 Вложенные выражения в скобках, порядок верный
    OperandOfExpr elem_2_9_1 = OperandOfExpr{parent, postfixToTree("a b 1 + * c d + +", errors), false};
    OperandOfExpr elem_2_9_2 = OperandOfExpr{parent, postfixToTree("a x 1 + * b c + +", errors), false};
    QTest::newRow("2.9 Correct order: alphabetically, considering only variables.\nNested expressions in parentheses, the order is correct") << elem_2_9_1 << elem_2_9_2 << true;

    // 2.10 Вложенные выражения в скобках, порядок неверный
    OperandOfExpr elem_2_10_1 = OperandOfExpr{parent, postfixToTree("a x 1 + * b c + +", errors), false};
    OperandOfExpr elem_2_10_2 = OperandOfExpr{parent, postfixToTree("a b 1 + * c d + +", errors), false};
    QTest::newRow("2.10 Correct order: alphabetically, considering only variables.\nNested expressions in parentheses, the order is incorrect") << elem_2_10_1 << elem_2_10_2 << false;


    // 3. Проверка на правило: от большего количества переменных в выражении к меньшему

    // 3.1 В первом выражении больше переменных, чем во втором
    OperandOfExpr elem_3_1_1 = OperandOfExpr{parent, postfixToTree("a b + c x + +", errors), false};
    OperandOfExpr elem_3_1_2 = OperandOfExpr{parent, postfixToTree("a b c + + 2 1 + +", errors), false};
    QTest::newRow("3.1 Correct order: from more variables in an expression to fewer.\nThere are more variables in the first expression than in the second") << elem_3_1_1 << elem_3_1_2 << true;

    // 3.2 Во втором выражении больше переменных, чем в первом
    OperandOfExpr elem_3_2_1 = OperandOfExpr{parent, postfixToTree("a b c + + 2 1 + +", errors), false};
    OperandOfExpr elem_3_2_2 = OperandOfExpr{parent, postfixToTree("a b + c x + +", errors), false};
    QTest::newRow("3.2 Correct order: from more variables in an expression to fewer.\nThere are more variables in the second expression than in the first") << elem_3_2_1 << elem_3_2_2 << false;

    // 3.3 Оба выражения имеют выражение в скобках, порядок верный
    OperandOfExpr elem_3_3_1 = OperandOfExpr{parent, postfixToTree("a b + c x + *", errors), false};
    OperandOfExpr elem_3_3_2 = OperandOfExpr{parent, postfixToTree("a b + c 1 + *", errors), false};
    QTest::newRow("3.3 Correct order: from more variables in an expression to fewer.\nBoth expressions have expression in parentheses, the order is correct") << elem_3_3_1 << elem_3_3_2 << true;

    // 3.4 Оба выражения имеют выражение в скобках, порядок неверный
    OperandOfExpr elem_3_4_1 = OperandOfExpr{parent, postfixToTree("a b + c 1 + *", errors), false};
    OperandOfExpr elem_3_4_2 = OperandOfExpr{parent, postfixToTree("a b + c x + *", errors), false};
    QTest::newRow("3.4 Correct order: from more variables in an expression to fewer.\nBoth expressions have expression in parentheses, the order is incorrect") << elem_3_4_1 << elem_3_4_2 << false;

    // 3.5 Выражения состоят из множителей, порядок верный
    OperandOfExpr elem_3_5_1 = OperandOfExpr{parent, postfixToTree("a b * c x * *", errors), false};
    OperandOfExpr elem_3_5_2 = OperandOfExpr{parent, postfixToTree("1 a * b c * *", errors), false};
    QTest::newRow("3.5 Correct order: from more variables in an expression to fewer.\nExpressions consist of multipliers, the order is correct") << elem_3_5_1 << elem_3_5_2 << true;

    // 3.6 Выражения состоят из множителей, порядок неверный
    OperandOfExpr elem_3_6_1 = OperandOfExpr{parent, postfixToTree("1 a * b c * *", errors), false};
    OperandOfExpr elem_3_6_2 = OperandOfExpr{parent, postfixToTree("a b * c x * *", errors), false};
    QTest::newRow("3.6 Correct order: from more variables in an expression to fewer.\nExpressions consist of multipliers, the order is incorrect") << elem_3_6_1 << elem_3_6_2 << false;

    // 3.7 Вложенные выражения в скобках, порядок верный
    OperandOfExpr elem_3_7_1 = OperandOfExpr{parent, postfixToTree("a b c x + * /", errors), false};
    OperandOfExpr elem_3_7_2 = OperandOfExpr{parent, postfixToTree("a b c 1 + * +", errors), false};
    QTest::newRow("3.7 Correct order: from more variables in an expression to fewer.\nNested expressions in parentheses, the order is correct") << elem_3_7_1 << elem_3_7_2 << true;

    // 3.8 Вложенные выражения в скобках, порядок неверный
    OperandOfExpr elem_3_8_1 = OperandOfExpr{parent, postfixToTree("a b c 1 + * +", errors), false};
    OperandOfExpr elem_3_8_2 = OperandOfExpr{parent, postfixToTree("a b c x + * /", errors), false};
    QTest::newRow("3.8 Correct order: from more variables in an expression to fewer.\nNested expressions in parentheses, the order is incorrect") << elem_3_8_1 << elem_3_8_2 << false;


    // 4. Проверка на правило: от большего количества слагаемых к меньшему

    // 4.1 В первом выражении больше слагаемых, чем во втором
    OperandOfExpr expr_4_1_1 = OperandOfExpr{parent, postfixToTree("a b + c 1 + +", errors), false};
    OperandOfExpr expr_4_1_2 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    QTest::newRow("4.1 Correct order: from more terms to fewer.\nThere are more terms in the first expression than in the second") << expr_4_1_1 << expr_4_1_2 << true;

    // 4.2 Во втором выражении меньше слагаемых, чем в первом
    OperandOfExpr expr_4_2_1 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    OperandOfExpr expr_4_2_2 = OperandOfExpr{parent, postfixToTree("a b + c 1 + +", errors), false};
    QTest::newRow("4.2 Correct order: from more terms to fewer.\nThere are more terms in the second expression than in the first") << expr_4_2_1 << expr_4_2_2 << false;

    // 4.3 Первое выражение имеет выражение в скобках, порядок верный
    OperandOfExpr expr_4_3_1 = OperandOfExpr{parent, postfixToTree("a b 2 + - c 1 + +", errors), false};
    OperandOfExpr expr_4_3_2 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    QTest::newRow("4.3 Correct order: from more terms to fewer.\nFirst expression has expression in parentheses, the order is correct") << expr_4_3_1 << expr_4_3_2 << true;

    // 4.4 Первое выражение имеет выражение в скобках, порядок неверный
    OperandOfExpr expr_4_4_1 = OperandOfExpr{parent, postfixToTree("a b c + 2 1 + + -", errors), false};
    OperandOfExpr expr_4_4_2 = OperandOfExpr{parent, postfixToTree("a b + c 1 + +", errors), false};
    QTest::newRow("4.4 Correct order: from more terms to fewer.\nFirst expression has expression in parentheses, the order is incorrect") << expr_4_4_1 << expr_4_4_2 << false;

    // 4.5 Второе выражение имеет выражение в скобках, порядок верный
    OperandOfExpr expr_4_5_1 = OperandOfExpr{parent, postfixToTree("a b + c 1 + +", errors), false};
    OperandOfExpr expr_4_5_2 = OperandOfExpr{parent, postfixToTree("a b c + 2 1 + + -", errors), false};
    QTest::newRow("4.5 Correct order: from more terms to fewer.\nSecond expression has expression in parentheses, the order is correct") << expr_4_5_1 << expr_4_5_2 << true;

    // 4.6 Второе выражение имеет выражение в скобках, порядок неверный
    OperandOfExpr expr_4_6_1 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    OperandOfExpr expr_4_6_2 = OperandOfExpr{parent, postfixToTree("a b 2 + - c 1 + +", errors), false};
    QTest::newRow("4.6 Correct order: from more terms to fewer.\nSecond expression has expression in parentheses, the order is incorrect") << expr_4_6_1 << expr_4_6_2 << false;

    // 4.7 Оба выражения имеют выражение в скобках, порядок верный
    OperandOfExpr expr_4_7_1 = OperandOfExpr{parent, postfixToTree("a b 2 + - c 1 + +", errors), false};
    OperandOfExpr expr_4_7_2 = OperandOfExpr{parent, postfixToTree("a b c + 2 1 + + -", errors), false};
    QTest::newRow("4.7 Correct order: from more terms to fewer.\nBoth expressions have expression in parentheses, the order is correct") << expr_4_7_1 << expr_4_7_2 << true;

    // 4.8 Оба выражения имеют выражение в скобках, порядок неверный
    OperandOfExpr expr_4_8_1 = OperandOfExpr{parent, postfixToTree("a b c + 2 1 + + -", errors), false};
    OperandOfExpr expr_4_8_2 = OperandOfExpr{parent, postfixToTree("a b 2 + - c 1 + +", errors), false};
    QTest::newRow("4.8 Correct order: from more terms to fewer.\nBoth expressions have expression in parentheses, the order is incorrect") << expr_4_8_1 << expr_4_8_2 << false;


    // 5. Унарные минусы, не влияющие на порядок

    // 5.1 Унарный минус у слагаемого, порядок верный
    OperandOfExpr expr_5_1_1 = OperandOfExpr{parent, postfixToTree("a b ~ + c x 1 + * +", errors), false};
    OperandOfExpr expr_5_1_2 = OperandOfExpr{parent, postfixToTree("a b c 1 + * ~ +", errors), false};
    QTest::newRow("5.1 Unary cons that do not affect the order.\nSummand has unary minus, the order is correct") << expr_5_1_1 << expr_5_1_2 << false;

    // 5.2 Унарный минус у слагаемого, порядок неверный
    OperandOfExpr expr_5_2_1 = OperandOfExpr{parent, postfixToTree("a b c 1 + * ~ +", errors), false};
    OperandOfExpr expr_5_2_2 = OperandOfExpr{parent, postfixToTree("a b ~ + c x 1 + * +", errors), false};
    QTest::newRow("5.2 Unary cons that do not affect the order.\nSummand has unary minus, the order is incorrect") << expr_5_2_1 << expr_5_2_2 << true;

    // 5.3 Унарный минус у множителя, порядок верный
    OperandOfExpr expr_5_3_1 = OperandOfExpr{parent, postfixToTree("a b c + + x 1 + ~ *", errors), false};
    OperandOfExpr expr_5_3_2 = OperandOfExpr{parent, postfixToTree("a b ~ + c 1 + *", errors), false};
    QTest::newRow("5.3 Unary cons that do not affect the order.\nMultiplier has unary minus, the order is correct") << expr_5_3_1 << expr_5_3_2 << true;

    // 5.4 Унарный минус у множителя, порядок неверный
    OperandOfExpr expr_5_4_1 = OperandOfExpr{parent, postfixToTree("a b ~ + c 1 + *", errors), false};
    OperandOfExpr expr_5_4_2 = OperandOfExpr{parent, postfixToTree("a b c + + x 1 + ~ *", errors), false};
    QTest::newRow("5.4 Unary cons that do not affect the order.\nMultiplier has unary minus, the order is incorrect") << expr_5_4_1 << expr_5_4_2 << false;

    // 5.5 Несколько унарных минусов, порядок верный
    OperandOfExpr expr_5_5_1 = OperandOfExpr{parent, postfixToTree("a b ~ ~ + c x 1 + * +", errors), false};
    OperandOfExpr expr_5_5_2 = OperandOfExpr{parent, postfixToTree("a b ~ + c 1 + *", errors), false};
    QTest::newRow("5.5 Unary cons that do not affect the order.\nSeveral unary minuses, the order is correct") << expr_5_5_1 << expr_5_5_2 << true;

    // 5.6 Несколько унарных минусов, порядок неверный
    OperandOfExpr expr_5_6_1 = OperandOfExpr{parent, postfixToTree("a b ~ ~ + c 1 + *", errors), false};
    OperandOfExpr expr_5_6_2 = OperandOfExpr{parent, postfixToTree("a b c + + x 1 + ~ ~ *", errors), false};
    QTest::newRow("5.6 Unary cons that do not affect the order.\nSeveral unary minuses, the order is incorrect") << expr_5_6_1 << expr_5_6_2 << false;


    // 6. Равные выражения в скобках

    // 6.1 Различные операнды между слагаемыми выражения: «+», «-»
    OperandOfExpr expr_6_1_1 = OperandOfExpr{parent, postfixToTree("a b +", errors), false};
    OperandOfExpr expr_6_1_2 = OperandOfExpr{parent, postfixToTree("a b -", errors), false};
    QTest::newRow("6.1 Equal expressions in parentheses.\nDifferent operands between the terms of the expression: \"+\", \"-\"") << expr_6_1_1 << expr_6_1_2 << true;

    // 6.2 Различные операнды между слагаемыми выражения: «-», «+»
    OperandOfExpr expr_6_2_1 = OperandOfExpr{parent, postfixToTree("a b -", errors), false};
    OperandOfExpr expr_6_2_2 = OperandOfExpr{parent, postfixToTree("a b +", errors), false};
    QTest::newRow("6.2 Equal expressions in parentheses.\nDifferent operands between the terms of the expression: \"-\", \"+\"") << expr_6_2_1 << expr_6_2_2 << true;

    // 6.3 Тождественно равные выражения: с бинарным и унарным минусами
    OperandOfExpr expr_6_3_1 = OperandOfExpr{parent, postfixToTree("a b -", errors), false};
    OperandOfExpr expr_6_3_2 = OperandOfExpr{parent, postfixToTree("a b ~ +", errors), false};
    QTest::newRow("6.3 Equal expressions in parentheses.\nEqual expressions: with binary and unary minuses") << expr_6_3_1 << expr_6_3_2 << true;

    // 6.4 Тождественно равные выражения: с унарным и бинарным минусами
    OperandOfExpr expr_6_4_1 = OperandOfExpr{parent, postfixToTree("a b ~ +", errors), false};
    OperandOfExpr expr_6_4_2 = OperandOfExpr{parent, postfixToTree("a b -", errors), false};
    QTest::newRow("6.4 Equal expressions in parentheses.\nEqual expressions: with unary and binary minuses") << expr_6_4_1 << expr_6_4_2 << true;
}
