#include "test_iscurrentorderofmultipliers.h"

Test_isCurrentOrderOfMultipliers::Test_isCurrentOrderOfMultipliers(QObject *parent)
    : QObject{parent}
{}

void Test_isCurrentOrderOfMultipliers::testIsCurrentOrderOfMultipliers()
{
    QFETCH(OperandOfExpr, elem_1);
    QFETCH(OperandOfExpr, elem_2);
    QFETCH(bool, exp_result);

    // Получить результат сравнения
    bool real_result = elem_1.isCurrentOrderOfMultipliers(elem_2);

    // Сравнить полученный результат с ожидаемым
    QCOMPARE(real_result, exp_result);
}

void Test_isCurrentOrderOfMultipliers::testIsCurrentOrderOfMultipliers_data()
{
    QTest::addColumn<OperandOfExpr>("elem_1");
    QTest::addColumn<OperandOfExpr>("elem_2");
    QTest::addColumn<bool>("exp_result");

    // Создать список ошибок для вызова функции создания списка
    QSet<Error> errors;
    // Создать общего родителя для множителя : "*"
    NodeOfExprTree* parent = new NodeOfExprTree("*");

    // 1. Проверка на правило: сначала числа, потом переменные, далее - выражения в скобках

    // Создать указатель на операнд типа переменная
    NodeOfExprTree* variable = new NodeOfExprTree("variable");

    // Создать указатель на операнд типа число
    NodeOfExprTree* number = new NodeOfExprTree("3");

    // Создать сравниваемые структуры
    OperandOfExpr var = OperandOfExpr{parent, variable, false};
    OperandOfExpr num = OperandOfExpr{parent, number, false};
    OperandOfExpr expr = OperandOfExpr{parent, postfixToTree("1 2 +", errors), false};
    OperandOfExpr un_var = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, variable), false};
    OperandOfExpr un_3 = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, number), false};

    // 1.1 Первый узел есть число, второй - переменная
    QTest::newRow("1.1 Correct order: number, variable, expression in parentheses. Order check: number, variable") << num << var << true;

    // 1.2 Первый узел есть переменная, второй - число
    QTest::newRow("1.2 Correct order: number, variable, expression in parentheses. Order check: variable, number") << var << num << false;

    // 1.3 Первый узел есть переменная, второй - выражение в скобках
    QTest::newRow("1.3 Correct order: number, variable, expression in parentheses. Order check: variable, expr") << var << expr << true;

    // 1.4 Первый узел есть выражение в скобках, второй - переменная
    QTest::newRow("1.4 Correct order: number, variable, expression in parentheses. Order check: expr, variable") << expr << var << false;

    // 1.5 Первый узел есть число, второй - выражение в скобках
    QTest::newRow("1.5 Correct order: number, variable, expression in parentheses. Order check: number, expr") << num << expr << true;

    // 1.6 Первый узел есть выражение в скобках, второй - число
    QTest::newRow("1.6 Correct order: number, variable, expression in parentheses. Order check: expr, number") << expr << num << false;

    // 1.7 С унарными минусами, порядок верный
    QTest::newRow("1.7 Correct order: number, variable, expression in parentheses. Order check: number with unary minus, variable unary minus") << un_3 << un_var << true;

    // 1.8 С унарными минусами, порядок верный
    QTest::newRow("1.8 Correct order: number, variable, expression in parentheses. Order check: variable unary minus, number with unary minus") << un_var << un_3 << false;

    // 1.9 Равные множители: два числа
    QTest::newRow("1.9 Equal multipliers: two numbers") << num << num << true;

    // 1.10 Равные множители: две переменные
    QTest::newRow("1.10 Equal multipliers: two variables") << var << var << true;

    // 1.11 Равные множители: два выражения в скобках
    QTest::newRow("1.11 Equal multipliers: two expr") << expr << expr << true;

    // 2. Проверка на правило: первый множитель меньше второго с учётом знака (для узлов типа число)

    // Создать сравниваемые структуры
    OperandOfExpr _1 = OperandOfExpr{parent, new NodeOfExprTree("1"), false};
    OperandOfExpr _3 = OperandOfExpr{parent, number, false};
    OperandOfExpr _11 = OperandOfExpr{parent, new NodeOfExprTree("11"), false};
    OperandOfExpr _111 = OperandOfExpr{parent, new NodeOfExprTree("111"), false};
    OperandOfExpr _31 = OperandOfExpr{parent, new NodeOfExprTree("31"), false};
    OperandOfExpr _3point1 = OperandOfExpr{parent, new NodeOfExprTree("3,1"), false};
    OperandOfExpr _3point2 = OperandOfExpr{parent, new NodeOfExprTree("3,2"), false};
    OperandOfExpr _31point2 = OperandOfExpr{parent, new NodeOfExprTree("31,2"), false};
    OperandOfExpr un_1 = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, _1.operand), false};
    OperandOfExpr un_un_1 = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, un_1.operand), false};
    OperandOfExpr un_un_un_1 = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, un_un_1.operand), false};
    OperandOfExpr un_un_3 = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, un_3.operand), false};
    OperandOfExpr un_un_un_3 = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, un_un_3.operand), false};

    // 2.1 Два положительных числа, первое меньше второго
    QTest::newRow("2.1 Correct order: number_1 < namber_2. Order check: 1, 3") << _1 << _3 << true;

    // 2.2 Два положительных числа, первое больше второго
    QTest::newRow("2.2 Correct order: number_1 < namber_2. Order check: 3, 1") << _3 << _1 << false;

    // 2.3 Первое число отрицательное, второе - положительное
    QTest::newRow("2.2 Correct order: number_1 < namber_2. Order check: ~3, 1") << un_3 << _1 << false;

    // 2.4 Первое число положительное, второе - отрицательное
    QTest::newRow("2.3. Correct order: number_1 < namber_2. Order check: 1, ~3") << _1 << un_3 << false;

    // 2.5 Оба числа отрицательные, первое меньше второго
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: ~3, ~1") << un_3 << un_1 << true;

    // 2.6 Оба числа отрицательные, первое больше второго
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: ~1, ~3") << un_1 << un_3 << false;

    // 2.7 Чётное кол-во унарных минусов, первое число меньше второго
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: ~(~1), ~(~3)") << un_un_1 << un_un_3 << true;

    // 2.8 Чётное кол-во унарных минусов, первое число больше второго
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: ~(~3), ~(~1)") << un_un_3 << un_un_1 << false;

    // 2.9 Нечётное кол-во унарных минусов, первое число меньше второго
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: ~(~(~3)), ~(~(~1))") << un_un_un_3 << un_un_un_1 << true;

    // 2.10 Нечётное кол-во унарных минусов, первое число больше второго
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: ~(~(~1)), ~(~(~3))") << un_un_un_1 << un_un_un_3 << false;

    // 2.11 Одинаковые цифры в числах, порядок верный
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: 11, 111") << _11 << _111 << true;

    // 2.12 Одинаковые цифры в числах, порядок неверный
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: 111, 11") << _111 << _11 << false;

    // 2.13 Первый множитель с плавающей запятой, порядок верный
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: 3,1, 31") << _3point1 << _31 << true;

    // 2.14 Первый множитель с плавающей запятой, порядок неверный
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: 31,2, 31") << _31point2 << _31 << false;

    // 2.15 Оба множителя с плавающей запятой, порядок верный
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: 3,1, 3,2") << _3point1 << _3point2 << true;

    // 2.16 Оба множителя с плавающей запятой, порядок неверный
    QTest::newRow("2. Correct order: number_1 < namber_2. Order check: 3,2, 3,1") << _3point2 << _3point1 << false;

    // 2.17 Равные множители: целые числа
    QTest::newRow("2. Equal multipliers: integers. Order check: 1, 1") << _1 << _1 << true;

    // 2.18 Равные множители: числа с плавающей запятой
    QTest::newRow("2. Equal multipliers: floating point numbers. Order check: 3,2, 3,2") << _3point2 << _3point2 << true;

    // 2.19 Равные множители: числа с унарными минусами (у первого один, у второго три «~»)
    QTest::newRow("2. Equal multipliers: numbers with unary cons (the first has one, the second has three \"~\"). Order check: ~1, ~(~(~1))") << un_1 << un_un_un_1 << true;

    // 2.20 Равные множители: числа с унарными минусами (у первого три, у второго один «~»)
    QTest::newRow("2. Equal multipliers: numbers with unary cons (the first one has three, the second one has one \"~\"). Order check: ~(~(~1)), ~1") << un_un_un_1 << un_1 << true;


    // 3. Проверка на правило: первый множитель меньше второго (для узлов типа переменная)
    OperandOfExpr one = OperandOfExpr{parent, new NodeOfExprTree("one"), false};
    OperandOfExpr un_one = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, one.operand), false};
    OperandOfExpr un_un_one = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, un_one.operand), false};
    OperandOfExpr two = OperandOfExpr{parent, new NodeOfExprTree("one"), false};
    OperandOfExpr un_two = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, two.operand), false};
    OperandOfExpr un_un_two = OperandOfExpr{parent, new NodeOfExprTree("~", nullptr, un_two.operand), false};
    OperandOfExpr aa = OperandOfExpr{parent, new NodeOfExprTree("aa"), false};
    OperandOfExpr aaa = OperandOfExpr{parent, new NodeOfExprTree("aaa"), false};

    // 3.1 Отличная буква в начале, порядок верный
    QTest::newRow("3.1 Correct order: variable_1 < variable_2. Order check: one, two") << one << two << true;

    // 3.2 Отличная буква в начале, порядок неверный
    QTest::newRow("3.2 Correct order: variable_1 < variable_2. Order check: two, one") << two << one << false;

    // 3.3 Первое слово длиннее второго
    QTest::newRow("3.3 Correct order: variable_1 < variable_2. Order check: aa, aaa") << aa << aaa << true;

    // 3.4 Второе слово длиннее первого
    QTest::newRow("3.4 Correct order: variable_1 < variable_2. Order check: aaa, aa") << aaa << aa << false;

    // 3.5 Унарный минус у первого множителя
    QTest::newRow("3.5 Correct order: variable_1 < variable_2. Order check: ~two, one") << un_two << one << false;

    // 3.6 Унарный минус у второго множителя
    QTest::newRow("3.6 Correct order: variable_1 < variable_2. Order check: two, ~one") << two << un_one << false;

    // 3.7 Унарный минус у каждого множителя, порядок верный
    QTest::newRow("3.7 Correct order: variable_1 < variable_2. Order check: ~one, ~two") << un_one << un_two << true;

    // 3.8 Унарный минус у каждого множителя, порядок неверный
    QTest::newRow("3.8 Correct order: variable_1 < variable_2. Order check: ~two, ~one") << un_two << un_one << false;

    // 3.9 Несколько унарных минусов, порядок верный
    QTest::newRow("3.9 Correct order: variable_1 < variable_2. Order check: ~(~one), ~(~two)") << un_un_one << un_un_two << true;

    // 3.10 Несколько унарных минусов, порядок неверный
    QTest::newRow("3.10 Correct order: variable_1 < variable_2. Order check: ~(~two), ~(~one)") << un_un_two << un_un_one << false;

    // 3.11 Равные множители, у первого больше унарных минусов
    QTest::newRow("3.11 Equal multipliers: the first one has more unary cons. Order check: ~(~one), ~one") << un_un_one << un_one << true;

    // 3.12 Равные множители, у второго больше унарных минусов
    QTest::newRow("3.12 Equal multipliers: the second one has more unary cons. Order check: ~one, ~(~one)") << un_one << un_un_one << true;



    // 4. Проверка на правило: верный порядок выражений в скобках

    // 4.1 От большей степени переменной n-ого слагаемого к меньшей, порядок верный
    OperandOfExpr expr_4_1_1 = OperandOfExpr{parent, postfixToTree("a x * c d + +", errors), false};
    OperandOfExpr expr_4_1_2 = OperandOfExpr{parent, postfixToTree("a b + c d + +", errors), false};
    QTest::newRow("4.1 From a higher degree of the nth term variable to a lower one, the order is correct: (a * x + c + d), (a + b + c + d)") << expr_4_1_1 << expr_4_1_2 << true;

    // 4.2 От большей степени переменной n-ого слагаемого к меньшей, порядок верный
    QTest::newRow("4.2 From a higher degree of the nth term variable to a lower one, the order is uncorrect: (a + b + c + d), (a * x + c + d)") << expr_4_1_2 << expr_4_1_1 << false;

    // 4.3 Отличны средние переменные, порядок верный
    OperandOfExpr expr_4_3_1 = OperandOfExpr{parent, postfixToTree("a b + c a + +", errors), false};
    OperandOfExpr expr_4_3_2 = OperandOfExpr{parent, postfixToTree("a x + c +", errors), false};
    QTest::newRow("4.3 The average variables are different, the order is correct: (a + b + c + a), (a + x + c)") << expr_4_3_1 << expr_4_3_2 << true;

    // 4.4 Отличны средние переменные, порядок неверный
    OperandOfExpr expr_4_4_1 = OperandOfExpr{parent, postfixToTree("a x + c a + +", errors), false};
    OperandOfExpr expr_4_4_2 = OperandOfExpr{parent, postfixToTree("a b + c +", errors), false};
    QTest::newRow("4.4 The average variables are different, the order is uncorrect: (a + x + c + a), (a + b + c)") << expr_4_4_1 << expr_4_4_2 << false;

    // 4.5 В первом выражении больше переменных, чем во втором
    OperandOfExpr expr_4_5_1 = OperandOfExpr{parent, postfixToTree("a b + c x + +", errors), false};
    OperandOfExpr expr_4_5_2 = OperandOfExpr{parent, postfixToTree("a b + c 1 + +", errors), false};
    QTest::newRow("4.5 There are more variables in the first expression than in the second: (a + b + c + x), (a + b + c + 1)") << expr_4_5_1 << expr_4_5_2 << true;

    // 4.6 Во втором выражении больше переменных, чем в первом
    QTest::newRow("4.6 There are more variables in the second expression than in the first: (a + b + c + 1), (a + b + c + x)") << expr_4_5_2 << expr_4_5_1 << false;

    // 4.7 В первом выражении больше слагаемых, чем во втором
    QTest::newRow("4.7 There are more terms in the first expression than in the second: (a + b + c + 1), (a + b + c)") << expr_4_5_2 << expr_4_4_2 << true;

    // 4.8 Во втором выражении больше слагаемых, чем в первом
    QTest::newRow("4.8 There are more terms in the second expression than in the first: (a + b + c), (a + b + c + 1)") << expr_4_4_2 << expr_4_5_2 << false;

    // 4.9 Унарный минус у слагаемого, порядок верный
    OperandOfExpr expr_4_9_1 = OperandOfExpr{parent, postfixToTree("a b ~ + c x 1 + * +", errors), false};
    OperandOfExpr expr_4_9_2 = OperandOfExpr{parent, postfixToTree("a b ~ c 1 + * +", errors), false};
    QTest::newRow("4.9 The unary minus sign is in the correct order.: (a + (~b) + c * (x + 1)), (a + (~b * (c + 1)))") << expr_4_9_1 << expr_4_9_2 << true;

    // 4.10 Унарный минус у слагаемого, порядок неверный
    QTest::newRow("4.10 The unary minus sign has an incorrect order: (a + (~b * (c + 1))), (a + (~b) + c * (x + 1))") << expr_4_9_2 << expr_4_9_1 << false;

    // 4.11 Равные множители, различные операторы: «+», «-»
    OperandOfExpr expr_4_11_1 = OperandOfExpr{parent, postfixToTree("a b +", errors), false};
    OperandOfExpr expr_4_11_2 = OperandOfExpr{parent, postfixToTree("a b -", errors), false};
    QTest::newRow("4.11 Equal multipliers, different operators: \" + \", \" - \". The current order is correct") << expr_4_11_1 << expr_4_11_2 << true;

    // 4.12 Равные множители, различные операторы: «-», «+»
    QTest::newRow("4.12 Equal multipliers, different operators: \" - \", \" + \". The current order is correct") << expr_4_11_2 << expr_4_11_1 << true;
}
