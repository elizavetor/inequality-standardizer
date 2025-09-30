/*!
* \file
* \brief Файл содержит реализацию методов класса функций, использующихся в ходе работы программы inequalityStandardizer.
*/

#include "nodeofexprtree.h"
#include "test_iscurrentorderofmultipliers.h"
#include "test_postfixtotree.h"
#include "test_getdegreeofexpr.h"
#include "test_getlistofnodesofsameprecedencelevel.h"
#include "test_getnodesofsameprecedencewithparenthesesopening.h"
#include "test_listtotree.h"
#include "test_treetoinfix.h"
#include "test_operatorgt.h"
#include "test_getsortedlist.h"
#include "test_sortoperandsalphabetically.h"
#include "test_iscurrentorderofsummands.h"
#include "test_iscurrentorderofparenthesisedexpressions.h"

/*!
 * \brief Запустить все тесты
 */
void runTests()
{
    Test_isCurrentOrderOfMultipliers test1;
    QTest::qExec(&test1);

    Test_postfixToTree test2;
    QTest::qExec(&test2);

    Test_getDegreeOfExpr test_3;
    QTest::qExec(&test_3);

    Test_getListOfNodesOfSamePrecedenceLevel test_4;
    QTest::qExec(&test_4);

    Test_getNodesOfSamePrecedenceWithParenthesesOpening test_5;
    QTest::qExec(&test_5);

    Test_listToTree test_6;
    QTest::qExec(&test_6);

    Test_treeToInfix test_7;
    QTest::qExec(&test_7);

    Test_operatorGt test_8;
    QTest::qExec(&test_8);

    Test_getSortedList test_9;
    QTest::qExec(&test_9);

    Test_sortOperandsAlphabetically test_10;
    QTest::qExec(&test_10);

    Test_isCurrentOrderOfSummands test_11;
    QTest::qExec(&test_11);

    Test_isCurrentOrderOfParenthesisedExpressions test_12;
    QTest::qExec(&test_12);
}

/*!
 * \brief Из постфиксной записи выражения получить дерево этого выражения
 * \param [in] expr － строка выражения в постфиксной записи
 * \param [out] errors － обнаруженные ошибки в постфиксной записи
 * \return указатель на корень построенного дерева
 */
NodeOfExprTree* postfixToTree(QString expr, QSet<Error>& errors)
{
    if(expr.isEmpty()) { return nullptr; }

    // ...Считать стек узлов пустым
    QStack<NodeOfExprTree*> nodes;
    QStack<int> nodes_pos_in_expr;

    // Проверить наличие некорректных разделителей
    if (expr.contains('\t') || expr.contains('\n'))
    {
        errors.insert(Error(INCORRECT_DELIMITER));
    }

    // Разбить строку на токены
    QStringList tokens = expr.split(QRegularExpression("[ \\n\\t]"), Qt::SkipEmptyParts);

    // ...Считать, что не было найдено ошибок
    bool errors_found = false;
    int count_of_tokens = tokens.size();
    for(int i = 0; i < count_of_tokens; i++) // Для каждого токена
    {
        // Если текущий токен некорректен
        if (!isVar(tokens[i]) && !isNum(tokens[i]) && !isOperator(tokens[i]))
        {
            // Считать, что найдена ошибка INVALID_SEQUENCE для текущего токена, добавить её в список ошибок
            errors.insert(Error(INVALID_SEQUENCE, i + 1, QStringList(tokens[i])));
            errors_found = true;
        }
    }

    // Вернуть пустой корень дерева, eсли были найдены ошибки
    if (errors_found)
    {
        return nullptr;
    }

    // Построить дерево...
    // ...Считать, что дерево построено корректно
    bool tree_is_correct = true;
    for(int i = 0; i < count_of_tokens; i++) // Для каждого токена
    {
        // Создать узел для текущего токена
        NodeOfExprTree* new_node = new NodeOfExprTree(tokens[i]);

        // Если тип созданного узла есть оператор
        if(isOperator(tokens[i]))
        {
            // Если текущий токен есть оператор сравнения
            if(isComparisonOperator(tokens[i]))
            {
                // Для каждого токена после текущего и пока текущий токен есть последний оператор выражения
                bool current_token_is_last_operator = true;
                for(int j = i + 1; j < count_of_tokens && current_token_is_last_operator; j++)
                {
                    // Считать, что текущий токен не последний оператор, если найден оператор после него
                    if(isOperator(tokens[j]))
                    {
                        current_token_is_last_operator = false;
                    }
                }
                // Считать, что найдена ошибка COMPARISON_OPERATOR_IN_PARENTHESES, если текущий оператор не последний
                if (!current_token_is_last_operator)
                {
                    errors.insert(Error(COMPARISON_OPERATOR_IN_PARENTHESES, i + 1, QStringList(tokens[i])));
                }
            }

            // Считать, что найдена ошибка NOT_ENOUGH_OPERANDS, если в стеке нет необходимого кол-ва узлов для текущего типа узла
            if(!(tokens[i] == "~" && nodes.size() >= 1 || tokens[i] != "~" && nodes.size() >= 2))
            {
                errors.insert(Error(NOT_ENOUGH_OPERANDS, i + 1, QStringList(tokens[i])));
                tree_is_correct = false;
            }

            // Вытащить необходимое кол-во узлов из стека и считать их операндами созданного узла
            if(!nodes.isEmpty())
            {
                new_node->setRightOperand(nodes.pop());
                nodes_pos_in_expr.pop();
                if(tokens[i] != "~" && !nodes.isEmpty())
                {
                    new_node->setLeftOperand(nodes.pop());
                    nodes_pos_in_expr.pop();
                }
            }
        }

        // Добавить созданный узел в стек
        nodes.push(new_node);
        nodes_pos_in_expr.push(i + 1);
    }

    // Если в стеке больше одного узла или дерево некорректно
    int count_of_remaining_elems = nodes.size();
    if(count_of_remaining_elems > 1 || !tree_is_correct)
    {
        // Если в стеке больше одного узла
        if (count_of_remaining_elems > 1)
        {
            for(int i = 0; i < count_of_remaining_elems; i++) // для каждого элемента стека
            {
                // Считать, что найдена ошибка MISSING_OPERATOR, если найден опернад, добавить её в список ошибок
                if(isNum(nodes[i]->getValue()) || isVar(nodes[i]->getValue()))
                {
                    errors.insert(Error(MISSING_OPERATOR, nodes_pos_in_expr[i], QStringList(tokens[nodes_pos_in_expr[i] - 1])));
                }
            }
        }
        clearStackNodes(nodes);
        return nullptr;
    }

    return nodes.pop();
}


/*!
 * \brief Удалить узлы стека
 * \param [in] stack - стек
 */
void clearStackNodes(QStack<NodeOfExprTree*>& stack)
{
    while(!stack.isEmpty())
    {
        NodeOfExprTree::delTree(stack.pop());
    }
}

/*!
 * \brief Определить является ли строка числом
 * \param [in] token - проверяемый токен
 * \return true, если токен есть число, иначе - false
 */
bool isNum(const QString token)
{
    // ...Считать, что заданный токен есть число
    bool is_num = true;

    /* Если первый символ заданного токена есть цифра 0 и второй символ - НЕ есть плавающая запятая
     или первый символ есть НЕ цифра */
    if (token[0] == '0' && token.length() > 1 && token[1] != ',' || !token[0].isNumber())
    {
        // Считать, что заданный токен не число, и завершить работу функции
        is_num = false;
    }

    // Считать, что в токене нет плавающей запятой
    bool has_comma = false;
    int num_of_symbol = token.length();
    for(int i = 1; i < num_of_symbol && is_num; i++) // Для каждого символа токена, кроме первого, и пока заданный токен число
    {
        // Если текущий символ есть запятая и она не была ещё найдена
        if (token[i] == ',' && has_comma == false)
        {
            // Считать, что в токене есть плавающая запятая
            has_comma = true;
        }
        // ИначеЕсли текущий символ есть запятая и она уже была найдена или текущий символ не есть цифра
        else if (token[i] == ',' && has_comma == true || !token[i].isNumber())
        {
            // Считать, что заданный токен не число
            is_num = false;
        }
    }

    // Вернуть результат
    return is_num;
}

/*!
 * \brief Определить является ли токен переменной
 * \param [in] token - проверяемый токен
 * \return true, если токен есть переменная, иначе - false
 */
bool isVar(const QString token)
{
    QString latin_alphabet("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    // Считать, что заданный токен является именем переменной
    bool is_var = true;

    // Если первый символ не является буквой латинского алфавита и нижним подчёркиванием
    if (latin_alphabet.indexOf(token[0]) == -1 && token[0] != '_')
    {
        // Считать, что заданный токен не является переменной
        is_var = false;
    }

    int num_of_symbol = token.length();
    for(int i = 1; i < num_of_symbol && is_var; i++)// Для каждого символа токена, начиная со второго, и пока заданный токен является переменной
    {
        // Если символ не является буквой латинского алфавита, цифрой и символом нижнего подчёркивания
        if (!token[i].isNumber() && token[i] != '_' && latin_alphabet.indexOf(token[i]) == -1)
        {
            // Считать, что заданный токен не является именем переменной
            is_var = false;
        }
    }

    // Вернуть результат
    return is_var;
}

/*!
 * \brief Определить является ли токен оператором
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isOperator(const QString token)
{
    if (token == "~" || token == "*" || token == "/"
        || token == "+" || token == "-" || token == ">"
        || token == "<" || token == ">=" || token == "<="
        || token == "=" || token == "!=")
    {
        return true;
    }

    return false;
}

/*!
 * \brief Определить является ли токен оператором сравнения
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isComparisonOperator(const QString token)
{
    if (token == ">" || token == "<"
        || token == ">=" || token == "<="
        || token == "=" || token == "!=")
    {
        return true;
    }

    return false;
}

/*!
 * \brief Определить правильность расстановки двух списков имён переменных по алфавиту
 * \param [in] var_1 - первый список имён переменных
 * \param [in] var_2 - второй список имён переменных
 * \return 1 - порядок верный, 0 - порядок неверный, -1 - списки одинаковы или порядок определить невозможно
 */
int isCurentOrderOfListOfVariableIDs(QList<NodeOfExprTree*> vars_1, QList<NodeOfExprTree*> vars_2)
{
    // Определить кол-во пар
    int count_pairs = 0;
    int count_vars_1 = vars_1.size();
    int count_vars_2 = vars_2.size();
    count_vars_1 >= count_vars_2 ? count_pairs = count_vars_2 : count_pairs = count_vars_1;
    for(int i = 0; i < count_pairs; i++) // Для каждой пары n-ых переменных списков
    {
        // Определить порядок: первая переменная меньше второй, и вернуть результат, если порядок определился
        if(vars_1[i]->getValue() < vars_2[i]->getValue())
        {
            return 1;
        }
        else if(vars_1[i]->getValue() > vars_2[i]->getValue())
        {
            return 0;
        }
    }

    return -1;
}

/*!
 * \brief Определить, равны ли имена переменных в списке
 * \param [in] var - список переменных
 * \return true, если в списке одинаковые имена переменных, false - иначе
 */
bool areEqualVariableIDs(QList<NodeOfExprTree*> vars)
{
    //...Считать, что имена переменных в списке одинаковы
    bool is_equal = true;
    int count_vars = vars.size();
    // Считать, что имена переменных различны, если в списке одна или ни одной переменной
    if (count_vars < 2)
    {
        is_equal = false;
    }
    for(int i = 1; i < count_vars && is_equal; i++) // Для каждого элемента в списке переменных, начиная со второго, пока они одинаковы
    {
        // Если текущее имя переменной не равно с первым
        if(vars[0]->getValue() != vars[i]->getValue())
        {
            // Считать, что имена переменныч в списке различны
            is_equal = false;
        }
    }

    // Вернуть результат
    return is_equal;
}

/*!
 * \brief Получить список операторов сравнения строки с разделителями (пробел, табуляция, перевод строки)
 * \return список операторов сравнения
 */
QStringList getListOfComparisonOperator(QString expr)
{
    // ...Считать список операторов пустым
    QStringList comparison_operator_list;

    // Разбить строку на токены
    QStringList tokens = expr.split(QRegularExpression("[ \\n\\t]"), Qt::SkipEmptyParts);

    int tokens_count = tokens.size();
    for(int i = 0; i < tokens_count; i++) // Для каждого токена
    {
        // Добавить в список текущий токен, если этот токен является оператором сравнения
        if(isComparisonOperator(tokens[i]))
        {
            comparison_operator_list.append(tokens[i]);
        }
    }

    // Вернуть список операторов сравнения
    return comparison_operator_list;
}
