#include "test_postfixtotree.h"

Test_postfixToTree::Test_postfixToTree(QObject *parent)
    : QObject{parent}
{}

void Test_postfixToTree::testPostfixToTree()
{
    QFETCH(QString, postfix_notation);
    QFETCH(QSet<Error>, starting_errors);
    QFETCH(QSet<Error>, final_errors);
    QFETCH(NodeOfExprTree*, exp_tree);

    // Получить результат сравнения
    QSet<Error> real_errors = starting_errors;
    NodeOfExprTree* real_tree = postfixToTree(postfix_notation, real_errors);

    // Сравнить полученное дерево с ожидаемым
    QString error_message;
    QStringList path;
    QVERIFY2(compareTrees(exp_tree, real_tree, path, error_message), error_message.toUtf8());

    // Сравнить полученные ошибки с ожидаемыми
    QString differences_in_errors = compareErrorSets(real_errors, final_errors);
    QVERIFY2(differences_in_errors.isEmpty(), qPrintable(differences_in_errors));

}

void Test_postfixToTree::testPostfixToTree_data()
{
    // Добавить столбцы
    QTest::addColumn<QString>("postfix_notation");
    QTest::addColumn<QSet<Error>>("starting_errors");
    QTest::addColumn<QSet<Error>>("final_errors");
    QTest::addColumn<NodeOfExprTree*>("exp_tree");

    // Набор базовых узлов и деревьев для тестирования
    NodeOfExprTree* a = new NodeOfExprTree("a");
    NodeOfExprTree* b = new NodeOfExprTree("b");
    NodeOfExprTree* c = new NodeOfExprTree("c");
    NodeOfExprTree* f = new NodeOfExprTree("f");
    NodeOfExprTree* _1 = new NodeOfExprTree("1");
    NodeOfExprTree* _2 = new NodeOfExprTree("2");
    NodeOfExprTree* _3 = new NodeOfExprTree("3");
    NodeOfExprTree* equal_node = nullptr;


    // Пустой список ошибок
    QSet<Error> equal_list_of_errors = {};

    // 1. Только переменные
    QString postfix_notation_1 = "a b +";
    NodeOfExprTree* a_plus_b = new NodeOfExprTree("+", a, b);
    QTest::newRow("1. Operation + with 2 var operand: a + b") << postfix_notation_1 << equal_list_of_errors << equal_list_of_errors << a_plus_b;

    // 2. Только числа
    QString postfix_notation_2 = "1 2 +";
    NodeOfExprTree* _1_plus_2 = new NodeOfExprTree("+", _1, _2);
    QTest::newRow("2. Operation + with 2 num operand: 1 + 2") << postfix_notation_2 << equal_list_of_errors << equal_list_of_errors << _1_plus_2;

    // 3. Оператор умножения
    QString postfix_notation_3 = "a b *";
    NodeOfExprTree* a_multiply_b = new NodeOfExprTree("*", a, b);
    QTest::newRow("3. Operation * with 2 var operand: a * b") << postfix_notation_3 << equal_list_of_errors << equal_list_of_errors << a_multiply_b;

    // 4. Оператор деления
    QString postfix_notation_4 = "a b /";
    NodeOfExprTree* a_division_b = new NodeOfExprTree("/", a, b);
    QTest::newRow("4. Operation / with 2 var operand: a / b") << postfix_notation_4 << equal_list_of_errors << equal_list_of_errors << a_division_b;

    // 5. Оператор бинарного минуса
    QString postfix_notation_5 = "a b -";
    NodeOfExprTree* a_minus_b = new NodeOfExprTree("-", a, b);
    QTest::newRow("5. Operation / with 2 var operand: a - b") << postfix_notation_5 << equal_list_of_errors << equal_list_of_errors << a_minus_b;

    // 6. Оператор унарного минуса
    QString postfix_notation_6 = "a ~";
    NodeOfExprTree* un_a = new NodeOfExprTree("~", nullptr, a);
    QTest::newRow("6. Operation ~ with var operand: ~a") << postfix_notation_6 << equal_list_of_errors << equal_list_of_errors << un_a;

    // 7. Оператор сравнения «>»
    QString postfix_notation_7 = "a b >";
    NodeOfExprTree* a_greater_b = new NodeOfExprTree(">", a, b);
    QTest::newRow("7. Operation > with 2 var operand: a > b") << postfix_notation_7 << equal_list_of_errors << equal_list_of_errors << a_greater_b;

    // 8. Оператор сравнения «<»
    QString postfix_notation_8 = "a b <";
    NodeOfExprTree* a_less_b = new NodeOfExprTree("<", a, b);
    QTest::newRow("8. Operation < with 2 var operand: a < b") << postfix_notation_8 << equal_list_of_errors << equal_list_of_errors << a_less_b;

    // 9. Оператор сравнения «>=»
    QString postfix_notation_9 = "a b >=";
    NodeOfExprTree* a_greater_or_equal_b = new NodeOfExprTree(">=", a, b);
    QTest::newRow("9. Operation >= with 2 var operand: a >= b") << postfix_notation_9 << equal_list_of_errors << equal_list_of_errors << a_greater_or_equal_b;

    // 10. Оператор сравнения «<=»
    QString postfix_notation_10 = "a b >=";
    NodeOfExprTree* a_less_or_equal_b = new NodeOfExprTree("<=", a, b);
    QTest::newRow("10. Operation <= with 2 var operand: a <= b") << postfix_notation_10 << equal_list_of_errors << equal_list_of_errors << a_less_or_equal_b;

    // 11. Оператор сравнения «==»
    QString postfix_notation_11 = "a b =";
    NodeOfExprTree* a_equal_b = new NodeOfExprTree("=", a, b);
    QTest::newRow("11. Operation == with 2 var operand: a == b") << postfix_notation_11 << equal_list_of_errors << equal_list_of_errors << a_equal_b;

    // 12. Оператор сравнения «!=»
    QString postfix_notation_12 = "a b !=";
    NodeOfExprTree* a_not_equal_b = new NodeOfExprTree("!=", a, b);
    QTest::newRow("12. Operation != with 2 var operand: a != b") << postfix_notation_12 << equal_list_of_errors << equal_list_of_errors << a_not_equal_b;

    // 13. Усложнённая левая ветка дерева
    QString postfix_notation_13 = "1 2 + b +";
    NodeOfExprTree* _1_plus_2_plus_b = new NodeOfExprTree("+", _1_plus_2, b);
    QTest::newRow("13. The complicated left branch of the tree: (1 + 2) + b") << postfix_notation_13 << equal_list_of_errors << equal_list_of_errors << _1_plus_2_plus_b;

    // 14. Усложнённая правая ветка дерева
    QString postfix_notation_14 = "a 1 2 + +";
    NodeOfExprTree* a_plus_1_plus_2 = new NodeOfExprTree("+", a, _1_plus_2);
    QTest::newRow("14. The complicated right branch of the tree: a + (1 + 2)") << postfix_notation_14 << equal_list_of_errors << equal_list_of_errors << a_plus_1_plus_2;

    // 15. Обе ветки усложнены
    QString postfix_notation_15 = "a b + 1 2 + +";
    NodeOfExprTree* a_plus_b_plus_1_plus_2 = new NodeOfExprTree("+", a_plus_b, _1_plus_2);
    QTest::newRow("15. Both branches of the tree are complicated: (a + b) + (1 + 2)") << postfix_notation_15 << equal_list_of_errors << equal_list_of_errors << a_plus_b_plus_1_plus_2;

    // 16. Выражение с унарным минусом
    QString postfix_notation_16 = "a b + ~ 1 2 + ~ +";
    NodeOfExprTree* un_a_plus_b = new NodeOfExprTree("~", nullptr, a_plus_b);
    NodeOfExprTree* un_1_plus_2 = new NodeOfExprTree("~", nullptr, _1_plus_2);
    NodeOfExprTree* un_expr_plus_un_expr = new NodeOfExprTree("+", un_a_plus_b, un_1_plus_2);
    QTest::newRow("16. Expressions with a unary minus: -(a + b) + (-(1 + 2))") << postfix_notation_16 << equal_list_of_errors << equal_list_of_errors << un_expr_plus_un_expr;

    // 17. Внутри выражения унарные минусы
    QString postfix_notation_17 = "a ~ b ~ + 1 ~ 2 ~ + ~ +";
    NodeOfExprTree* un_b = new NodeOfExprTree("~", nullptr, b);
    NodeOfExprTree* un_1 = new NodeOfExprTree("~", nullptr, _1);
    NodeOfExprTree* un_2 = new NodeOfExprTree("~", nullptr, _2);
    NodeOfExprTree* un_a_plus_un_b = new NodeOfExprTree("+", un_a, un_b);
    NodeOfExprTree* un_1_plus_un_2 = new NodeOfExprTree("+", un_1, un_2);
    NodeOfExprTree* un_a_plus_un_b_plus_un_1_plus_un_2 = new NodeOfExprTree("+", un_a_plus_un_b, un_1_plus_un_2);
    QTest::newRow("17. There are unary minus inside the expression: -a + (-b) + (-1) + (-2)") << postfix_notation_17 << equal_list_of_errors << equal_list_of_errors << un_a_plus_un_b_plus_un_1_plus_un_2;

    // 18. Отсутствует оператор
    QString postfix_notation_18 = "a b";
    QSet<Error> its_missing_operator = {{Error(MISSING_OPERATOR, 1, QStringList() = {"a"}) }};
    QTest::newRow("18. The operator is missing: a b") << postfix_notation_18 << equal_list_of_errors << its_missing_operator << equal_node;

    // 19. Отсутствует операнд
    QString postfix_notation_19 = "a +";
    QSet<Error> its_not_enough_operands = {{Error(NOT_ENOUGH_OPERANDS, 2, QStringList() = {"+"}) }};
    QTest::newRow("19. An operand is missing: a +") << postfix_notation_19 << equal_list_of_errors << its_not_enough_operands << equal_node;

    // 20. Наличие иных символов
    QString postfix_notation_20 = "a b ^";
    QSet<Error> its_invalid_operator = {{Error(INVALID_SEQUENCE, 3, QStringList() = {"^"}) }};
    QTest::newRow("20. The presence of other symbols: a ^ b") << postfix_notation_20 << equal_list_of_errors << its_invalid_operator << equal_node;

    // 21. Некорректно число
    QString postfix_notation_21 = "12,34,56";
    QSet<Error> its_invalid_num = {{Error(INVALID_SEQUENCE, 1, QStringList() = {"12,34,56"}) }};
    QTest::newRow("21. The number is incorrect: 12,34,56") << postfix_notation_21 << equal_list_of_errors << its_invalid_num << equal_node;

    // 22. Некорректно имя переменной
    QString postfix_notation_22 = "ab-cd";
    QSet<Error> its_invalid_var_1 = {{Error(INVALID_SEQUENCE, 1, QStringList() = {"ab-cd"}) }};
    QTest::newRow("22. The variable name is incorrect: ab-cd") << postfix_notation_22 << equal_list_of_errors << its_invalid_var_1 << equal_node;

    // 23. Цифра на первом месте у переменной
    QString postfix_notation_23 = "1abc";
    QSet<Error> its_invalid_var_2 = {{Error(INVALID_SEQUENCE, 1, QStringList() = {"1abc"}) }};
    QTest::newRow("23. The number comes first for the variable: ab-cd") << postfix_notation_23 << equal_list_of_errors << its_invalid_var_2 << equal_node;

    // 24. Оператор сравнения не является корнем дерева
    QString postfix_notation_24 = "a b = 2 +";
    QSet<Error> its_comparison_operator_in_parentheses = {{Error(COMPARISON_OPERATOR_IN_PARENTHESES, 3, QStringList() = {"="}) }};
    NodeOfExprTree* a_equal_b_plus_2 = new NodeOfExprTree("+", a_equal_b, _2);
    QTest::newRow("24. The comparison operator is not the root of the tree: (a == b) + 2") << postfix_notation_24 << equal_list_of_errors << its_comparison_operator_in_parentheses << a_equal_b_plus_2;

    // 25. Наличие табуляции
    QString postfix_notation_25 = "a\tb";
    QSet<Error> its_incorrect_delimiter = {{Error(INCORRECT_DELIMITER) }};
    QTest::newRow("25. The presence of tabs: a[\t]b") << postfix_notation_25 << equal_list_of_errors << its_incorrect_delimiter << equal_node;

    // 26. Наличие перевода строки
    QString postfix_notation_26 = "a\nb";
    QTest::newRow("26. The presence of a newline: a[\n]b") << postfix_notation_26 << equal_list_of_errors << its_incorrect_delimiter << equal_node;

    // 27. Несколько ошибок некорректного ввода данных: некорректные число и имя переменной
    QString postfix_notation_27 = "12,34,56 ab-cd";
    QSet<Error> its_incorrect_num_and_var = {{Error(INVALID_SEQUENCE, 1, QStringList() = {"12,34,56"}) }, {Error(INVALID_SEQUENCE, 2, QStringList() = {"ab-cd"}) }};
    QTest::newRow("27. Several incorrect data entry errors: incorrect number and variable name: 12,34,56 ab-cd") << postfix_notation_27 << equal_list_of_errors << its_incorrect_num_and_var << equal_node;

    // 28. Несколько ошибок некорректного ввода данных: оператор сравнения не является корнем дерева, отсутствует операнд для операции
    QString postfix_notation_28 = "a = b +";
    QSet<Error> its_incorrect_root_and_not_enough_operands = {{Error(COMPARISON_OPERATOR_IN_PARENTHESES, 2, QStringList() = {"="}) }, {Error(NOT_ENOUGH_OPERANDS, 2, QStringList() = {"="}) }};
    QTest::newRow("28. There are several incorrect data entry errors: the comparison operator is not the root of the tree, and there is no operand for the operation: 12,34,56 ab-cd") << postfix_notation_28 << equal_list_of_errors << its_incorrect_root_and_not_enough_operands << equal_node;

    // 29. Уже есть ошибка, дерево построено
    QString postfix_notation_29 = "a b +";
    QSet<Error> its_no_compsrison_operator = {{Error(NO_COMPARISON_OPERATOR) }};
    QTest::newRow("29. There is already a mistake, the tree is built: a + b") << postfix_notation_29 << its_no_compsrison_operator << its_no_compsrison_operator << a_plus_b;

    // 30. Уже есть ошибка + возникла ошибка при построении деревa
    QString postfix_notation_30 = "ab-cd";
    QTest::newRow("29. There is already an error + an error occurred when building the tree: ab-cd") << postfix_notation_30 << its_no_compsrison_operator << its_no_compsrison_operator + its_invalid_var_1 << equal_node;

    // 31. Одна переменная
    QString postfix_notation_31 = "a";
    QTest::newRow("31. Only variable: a") << postfix_notation_31 << equal_list_of_errors << equal_list_of_errors << a;

    // 32. Пустая строка
    QString postfix_notation_32 = "";
    QTest::newRow("32. Equal str") << postfix_notation_32 << equal_list_of_errors << equal_list_of_errors << equal_node;

    // 33. Комплексный тест
    QString postfix_notation_33 = "a b + c * f / 1 2 3 + - <";
    NodeOfExprTree* a_plus_b_multiply_c = new NodeOfExprTree("*", a_plus_b, c);
    NodeOfExprTree* a_plus_b_multiply_c_div_f = new NodeOfExprTree("/", a_plus_b_multiply_c, f);
    NodeOfExprTree* _2_plus_3 = new NodeOfExprTree("+", _2, _3);
    NodeOfExprTree* _1_minus_expr = new NodeOfExprTree("-", _1, _2_plus_3);
    NodeOfExprTree* a_plus_b_multiply_c_div_f_less_1_minus_expr = new NodeOfExprTree("<", a_plus_b_multiply_c_div_f, _1_minus_expr);
    QTest::newRow("33. Complex test: ((a + b) * c) / f < 1 - (2 + 3)") << postfix_notation_33 << equal_list_of_errors << equal_list_of_errors << a_plus_b_multiply_c_div_f_less_1_minus_expr;
}

/*!
 * \brief Сравнивает ожидаемое дерево с полученным и формирует сообщение о различиях
 * \param [in] exp_node - ожидаемое дерево
 * \param [in] real_node - полученное дерево
 * \param [in,out] path - путь проверки деревьев
 * \param [out] error_message - сообщение об различиях
 * \return равны ли два дерева
 */
bool compareTrees(const NodeOfExprTree* exp_node, const NodeOfExprTree* real_node, QStringList& path, QString& error_message)
{
    // Проверить текущие полученный и ожидаемый узлы...
    // Если узлы пустые
    if (real_node == nullptr && exp_node == nullptr)
    {
        // Считать, что узлы равны (вернут true)
        return true;
    }

    // Добавить текущий узел получившегося дерева в путь
    if (!path.isEmpty())
        path.append("->");
    if (real_node != nullptr)
        path.append(real_node->getValue());
    else path.append("nullptr");

    // Если один из узлов пустой
    if (real_node == nullptr || exp_node == nullptr)
    {
        // Считать, что узлы неравны и вернут false
        if(exp_node == nullptr)
        {
            error_message += "\nThe real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: nullptr\n";
        }
        else
            error_message += "\nThe real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: " + exp_node->getValue() + "\n";

        return false;
    }

    // Если узлы различны
    if (*exp_node != *real_node)
    {
        // Считать, что узлы неравны и вернут false
        error_message += "\nThe real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: " + exp_node->getValue() + "\n";
        return false;
    }

    // Считать, что ошибка найдена, если левые или правые операнды полученного и ожидаемого узлов различны
    if (!compareTrees(exp_node->getLeftOperand(), real_node->getLeftOperand(), path, error_message) ||
        !compareTrees(exp_node->getRightOperand(), real_node->getRightOperand(), path, error_message))
    {
        return false;
    }

    // Удаление текущего узла из пути при отсутствии ошибок
    path.removeLast();
    if (!path.isEmpty())
        path.removeLast();

    return true;
}

/*!
 * \brief Сравнивает ожидаемое множество ошибок с полученным и формирует сообщение о различиях
 * \param [in] errors - множество полученных ошибок
 * \param [in] expErrors - множество ожидаемых ошибок
 * \return сообщение о различиях во множествах
 */
QString compareErrorSets(const QSet<Error>& errors, const QSet<Error>& exp_errors)
{
    // Получаем множества пропущенных и непредвиденных ошибок
    QSet<Error> missingErrors = exp_errors - errors;
    QSet<Error> unexpectedErrors = errors - exp_errors;

    QString differencesInErrors; // Итоговая строка с отличиями во множествах ошибок

    if (!missingErrors.isEmpty() || !unexpectedErrors.isEmpty())
    {
        // Записываем пропущенные ошибки
        if (!missingErrors.isEmpty())
        {
            differencesInErrors += "Missing errors:\n";

            QSet<Error>::const_iterator i1;
            for (i1 = missingErrors.constBegin(); i1 != missingErrors.constEnd(); i1++)
                differencesInErrors += i1->toString() + "\n";
        }

        // Записываем непредвиденные ошибки
        if (!unexpectedErrors.isEmpty())
        {
            differencesInErrors += "Unexpected errors returned:\n";

            QSet<Error>::const_iterator i2;
            for (i2 = unexpectedErrors.constBegin(); i2 != unexpectedErrors.constEnd(); i2++)
                differencesInErrors += i2->toString() + "\n";
        }
    }

    return differencesInErrors;
}
