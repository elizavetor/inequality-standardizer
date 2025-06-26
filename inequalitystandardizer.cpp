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

    // Проверяем наличие некорректных разделителей
    if (expr.contains('\t') || expr.contains('\n'))
    {
        errors.insert(Error(INCORRECT_DELIMITER));
    }

    // Разбить строку на токены
    QStringList tokens = expr.split(QRegularExpression("[ \\n\\t]"), Qt::SkipEmptyParts);

    // ...Считать, что не было найдено ошибок
    bool errors_found = false;
    for(int i = 0; i < tokens.size(); i++) // Для каждого токена
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
    if (errors_found) { return nullptr; }

    int count_of_tokens = tokens.size();
    for(int i = 0; i < count_of_tokens; i++) // Для каждого токена
    {
        // Создать узел для текущего токена
        NodeOfExprTree* new_node = new NodeOfExprTree(tokens[i]);

        // Добавить узел в стек узлов, eсли тип созданного узла есть переменная или число
        if (isVar(tokens[i]) || isNum(tokens[i]))
        {
            nodes.push(new_node);
            nodes_pos_in_expr.push(i + 1);
        }

        // ИначеЕсли тип созданного узла есть оператор
        else
        {
            // Если созданный узел типа оператора сравнения и текущий токен не яляется последним
            if (isComparisonOperator(tokens[i]) && i != count_of_tokens - 1)
            {
                // Считать, что найдена ошибка COMPARISON_OPERATOR_IN_PARENTHESES, добавить её в список ошибок
                errors.insert(Error(COMPARISON_OPERATOR_IN_PARENTHESES, i + 1, QStringList(tokens[i])));
            }

            // Если в стеке есть необходимое кол-во узлов для текущего типа узла
            if(tokens[i] == "~" && nodes.size() >= 1 || tokens[i] != "~" && nodes.size() >= 2)
            {
                // Вытащить необходимое кол-во узлов из стека и считать их операндами созданного узла
                new_node->setRightOperand(nodes.pop());
                nodes_pos_in_expr.pop();
                if(tokens[i] != "~")
                {
                    new_node->setLeftOperand(nodes.pop());
                    nodes_pos_in_expr.pop();
                }
                // Добавить созданный узел в стек
                nodes.push(new_node);
                nodes_pos_in_expr.push(i + 1);
            }
            // Иначе считать, что найдена ошибка NOT_ENOUGH_OPERANDS, добавить её в список ошибок и вернуть пустой корень дерева
            else
            {
                errors.insert(Error(NOT_ENOUGH_OPERANDS, i + 1, QStringList(tokens[i])));
                delete new_node;
                clearStackNodes(nodes);
                return nullptr;
            }
        }
    }

    // Если в стеке больше одного узла
    if(nodes.size() > 1)
    {
        for(int i = 0; i < nodes.size() - 1; i++)
        {
            // Считать, что найдена ошибка MISSING_OPERATOR, добавить её в список ошибок и вернуть пустой корень дерева
            errors.insert(Error(MISSING_OPERATOR, nodes_pos_in_expr[i], QStringList(tokens[nodes_pos_in_expr[i] - 1])));
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
bool isNum(QString token)
{
    // ...Считать, что заданный токен есть число
    bool is_num = true;

    /* Если первый символ заданного токена есть цифра 0 и второй символ - не есть плавающая запятая
     или первый символ есть НЕцифра */
    if (token[0] == '0' && token[1] != ',' || !token[0].isNumber())
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

    // Вернуть результат - заданный токен число или нет
    return is_num;
}

/*!
 * \brief Определить является ли токен переменной
 * \param [in] token - проверяемый токен
 * \return true, если токен есть переменная, иначе - false
 */
bool isVar(QString token)
{
    QString latin_alphabet("ABCDIFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxwz");
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
        if (!token[i].isNumber() && token[0] != '_' && latin_alphabet.indexOf(token[i]) == -1)
        {
            // Считать, что заданный токен не является именем переменной
            is_var = false;
        }
    }

    return is_var;
}

/*!
 * \brief Определить является ли токен оператором
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isOperator(QString token)
{
    // Если токен является
    if (token == "~" || token == "*" || token == "/"
        || token == "+" || token == "-" || token == ">"
        || token == "<" || token == ">=" || token == "<="
        || token == "=" || token == "!=")
        return true;

    return false;
}

/*!
 * \brief Определить является ли токен оператором сравнения
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isComparisonOperator(QString token)
{
    // Если токен является
    if (token == ">" || token == "<"
        || token == ">=" || token == "<="
        || token == "=" || token == "!=")
        return true;

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
    // Для каждой пары n-ых переменных списков
    int count_pairs = 0;
    int count_vars_1 = vars_1.size();
    int count_vars_2 = vars_2.size();
    count_vars_1 >= count_vars_2 ? count_pairs = count_vars_2 : count_pairs = count_vars_1;
    for(int i = 0; i < count_pairs; i++)
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
 * \brief Определить, равны ли имена переменные в списке
 * \param [in] var - список переменных
 * \return true, если в списке одинаковые имена переменных, falst - иначе
 */
bool areEqualVariableIDs(QList<NodeOfExprTree*> vars)
{
    //...Считать, что имена переменных в списке одинаковы
    bool is_equal = true;
    int count_vars = vars.size();
    for(int i = 0; i < count_vars && is_equal; i++) // Для каждого элемента в списке переменных, начиная со второго, пока они одинаковы
    {
        // Если текущее имя переменной не равно с первым
        if(vars[0]->getValue() != vars[i]->getValue())
        {
            // Считать, что имена переменныч в списке различны
            is_equal = false;
        }
    }

    // Вернуть получившийся результат
    return is_equal;
}
