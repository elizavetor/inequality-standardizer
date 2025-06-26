#include "nodeofexprtree.h"

NodeOfExprTree::NodeOfExprTree()
{
    type = UNDEFINED;
    value = "";
    left_operand = nullptr;
    right_operand = nullptr;
}

NodeOfExprTree::NodeOfExprTree(QString _value, NodeOfExprTree* _left_operand, NodeOfExprTree* _right_operand)
{
    // Установить значение узла
    value = _value;

    // Установить тип узла
    if (value == "~")
        type = UN_MINUS;
    else if (value == "*")
        type = MULTIPLICATION;
    else if (value == "/")
        type = DIVISION;
    else if (value == "+")
        type = PLUS;
    else if (value == "-")
        type = BIN_MINUS;
    else if (value == ">")
        type = GREATER;
    else if (value == "<")
        type = LESS;
    else if (value == ">=")
        type = GREATER_OR_EQUAL;
    else if (value == "<=")
        type = LESS_OR_EQUAL;
    else if (value == "=")
        type = EQUAL;
    else if (value == "!=")
        type = NOT_EQUAL;
    else if (isVar(value))
        type = VAR;
    else if (isNum(value))
        type = NUM;
    else
        type = UNDEFINED;

    // Установить левый операнд
    left_operand = _left_operand;

    // Установить правый операнд
    right_operand = _right_operand;
}

/*!
 * \brief Вернуть тип узла
 * \return тип узла (0-5 в зависимости от приоритета), -1 - ошибка
 */
int NodeOfExprTree::getPrecedenceType()
{
    switch (type) {
    case NUM:
    case VAR:
        return 0;
        break;
    case UN_MINUS:
        return 1;
        break;
    case MULTIPLICATION:
    case DIVISION:
        return 2;
        break;
    case PLUS:
    case BIN_MINUS:
        return 3;
        break;
    case GREATER:
    case LESS:
    case GREATER_OR_EQUAL:
    case LESS_OR_EQUAL:
        return 4;
        break;
    case EQUAL:
    case NOT_EQUAL:
        return 5;
        break;
    default:
        return -1;
        break;
    }
}

/*!
 * \brief Получить строку значения узла для инфикной записи
 * \return строка для инфикной записи
 */
QString NodeOfExprTree::valueToStr()
{
    if(type == UN_MINUS)
        return "-";
    if(type == EQUAL)
        return "==";

    return value;
}

/*!
     * \brief Перегрузка оператора равенства для NodeOfExprTree
     */
bool NodeOfExprTree::operator==(const NodeOfExprTree& other) const
{
    if (value == other.value && type == other.type)
        return true;

    return false;
}

/*!
 * \brief Удалить дерево
 * \param [in] root - корень дерева
 */
void NodeOfExprTree::delTree(NodeOfExprTree* root)
{
    if (root == nullptr) return;
    if (root->left_operand != nullptr) delTree(root->left_operand);
    if (root->right_operand != nullptr) delTree(root->right_operand);

    delete root;
}

/*!
 * \brief Получить узел, пропустив все унарные минусы и посчитав их кол-во
 * \param [in,out] node - искомый узел
 * \return кол-во пропущенных унарных минусов
 */
int NodeOfExprTree::getNodeBySkippingUnaryMinus(NodeOfExprTree** node)
{
    // Считать, что не пропущен ни один узел типа оператора унарный минус
    int count_of_un_minus = 0;

    NodeOfExprTree* intended_desire_node = this;
    while (intended_desire_node->type == UN_MINUS) // Пока предполагаемый искомый узел унарный минус
    {
        // Считать правый операнд предполагаемого искомого узла новым предполагаемым искомым узлом
        intended_desire_node = intended_desire_node->right_operand;
        // Увеличить кол-во пропущенных узлов типа оператора унарный минус на единицу
        count_of_un_minus += 1;
    }

    // Вернуть кол-во пропущенных унарных минусов
    *node = intended_desire_node;
    return count_of_un_minus;
}

/*!
 * \brief Расставить все элементы в дереве выражения по алфавиту, начиная с заданного узла
 * \return указатель на корень отсортированного дерева
 */
NodeOfExprTree* NodeOfExprTree::sortOperandsAlphabetically()
{
    // ...Считать корень перестроенного дерева равным заданному узлу
    // Получить список для сортировки

    // Для каждого элемента списка сортировки
    {
        // Если текущий сортировочный элемент не является листом дерева
        // Расставить все элементы в дереве по алфавиту, начиная с текущего элемента сортировки, получив корень этого элемента
        // Если операнд текущего элемента сортировки отличен от полученного корня
        // Изменить операнд текущего элемента сортировки на полученный корень
    }

    // Расставить элементы сортировочного списка по алфавиту...
    // Если в сортировочном списке больше одного элемента
    // Для каждой пары соседних элементов списка сортировки и пока не произошло ни одного изменения
    {
        // Для всех пар соседних неотсортированных элементов сортировки
        {
            // Поменять местами элементы пары, если они нарушают порядок сортировки
        }
    }
    // Перестроить дерево по отсортированным элементам в списке и получить корень перестроенного дерева

    // Вернуть корень дерева
    NodeOfExprTree* left_operand = new NodeOfExprTree("1");
    return left_operand;
}

/*!
 * \brief Получить список операндов, родители которых одного приоритета, начиная с заданного корня
 * \return список операндов
 */
QList<OperandOfExpr> NodeOfExprTree::getListOfNodesOfSamePrecedenceLevel()
{
    // ...Считать список операндов пустым
    QList<OperandOfExpr> list;

    // Если заданный узел есть унарная операция
    if (type == UN_MINUS)
    {
        // Добавить в список операндов заданный узел и его операнд как родитель и операнд элемента соответственно
        list += OperandOfExpr{this, right_operand, false};
        // Вернуть список
        return list;
    }

    // Если заданный узел лист дерева
    if (type == NUM || type == VAR)
    {
        // Добавить в список узлов заданный узел
        list += OperandOfExpr{nullptr, this, true};
        // Вернуть список
        return list;
    }

    // ...Считать списки элементов левого и правого операндов пустыми
    QList<OperandOfExpr> list_of_left_operand;
    QList<OperandOfExpr> list_of_right_operand;

    // Если левый операнд заданного узла того же приоритета, что и заданный узел
    if(left_operand->getPrecedenceType() == getPrecedenceType())
    {
        /* Получить список элементов операторов одного приоритета, начиная с левого операнда заданного узла, без родителя у первого элемента
         * Добавить полученный список в список элементов левого операнда */
        list_of_left_operand += left_operand->getListOfNodesOfSamePrecedenceLevel();
    }
    else
    {
        // Добавить левый операнд в список элементов левого операнда
        list_of_left_operand.append(OperandOfExpr{nullptr, left_operand, true});
    }

    // Если правый операнд заданного узла того же приоритета, что и заданный узел, и заданный узел - симметричный
    if(right_operand->getPrecedenceType() == getPrecedenceType() && isSymmetricOperator())
    {
        /* Получить список элементов операторов одного приоритета, начиная с правого операнда заданного узла, без родителя у первого элемента
         * Добавить полученный список в список элементов правого операнда */
        list_of_right_operand += right_operand->getListOfNodesOfSamePrecedenceLevel();
    }
    else
    {
        // Добавить правый операнд в список правого операнда элементов
        list_of_right_operand.append(OperandOfExpr{nullptr, right_operand, true});
    }

    // Считать заданный узел родителем первого элемента списка элементов правого операнда
    list_of_right_operand[0].parent = this;
    list_of_right_operand[0].is_first_elem = false;

    // Добавить в список операндов списки левого и правого операндов заданного узла
    list += list_of_left_operand + list_of_right_operand;

    // Вернуть список операндов
    return list;
}

/*!
 * \brief Получить список операндов, родители которых одного приоритета, начиная с заданного узла, раскрывая скобки
 * \param [in] is_invert - флаг: true - значение заданного узла необходимо поменять на противоположный операнд, false - иначе
 * \return список операндов
 */
QList<OperandOfExpr> NodeOfExprTree::getNodesOfSamePrecedenceWithParenthesesOpening(bool is_invert)
{
    // ...Считать список операндов пустым
    QList<OperandOfExpr> list;

    // Если заданный узел есть унарная операция
    if (type == UN_MINUS)
    {
        // Добавить в список операндов заданный узел и его операнд как родитель и операнд элемента соответственно
        list += OperandOfExpr{this, right_operand, false};
        // Вернуть список
        return list;
    }

    // Если заданный узел лист дерева
    if (type == NUM || type == VAR)
    {
        // Добавить в список узлов заданный узел
        list += OperandOfExpr{nullptr, this, true};
        // Вернуть список
        return list;
    }

    // ...Считать списки элементов левого и правого операндов пустыми
    QList<OperandOfExpr> list_of_left_operand;
    QList<OperandOfExpr> list_of_right_operand;

    // Если левый операнд заданного узла того же приоритета, что и заданный узел
    if(left_operand->getPrecedenceType() == getPrecedenceType())
    {
        /* Получить список элементов операторов одного приоритета с учётом инвертации, начиная с левого операнда заданного узла, без родителя у первого элемента
         * Добавить полученный список в список элементов левого операнда */
        list_of_left_operand += left_operand->getNodesOfSamePrecedenceWithParenthesesOpening(is_invert);
    }
    else
    {
        // Добавить левый операнд в список элементов левого операнда
        list_of_left_operand.append(OperandOfExpr{nullptr, left_operand, true});
    }

    // Инвертировать тип заданного узла, если флаг установлен
    if(is_invert)
    {
        switch (type) {
        case PLUS:
            type = BIN_MINUS;
            value = "-";
            break;
        case BIN_MINUS:
            type = PLUS;
            value = "+";
            break;
        case MULTIPLICATION:
            type = DIVISION;
            value = "/";
            break;
        case DIVISION:
            type = MULTIPLICATION;
            value = "*";
            break;
        default:
            break;
        }
    }
    // Установить флаг инвертации, eсли заданный узел несимметричный оператор и флаг инвертации не установлен
    if(!isSymmetricOperator() && !is_invert)
    {
        is_invert = true;
    }
    else if (isSymmetricOperator() && is_invert) // ИначеЕсли заданный узел симметричный оператор и флаг инвертации установлен, убрать флаг инвертации
    {
        is_invert = false;
    }

    // Если правый операнд заданного узла того же приоритета, что и заданный узел
    if(right_operand->getPrecedenceType() == getPrecedenceType())
    {
        /* Получить список элементов операторов одного приоритета с учётом инвертации, начиная с левого операнда заданного узла, без родителя у первого элемента
         * Добавить полученный список в список элементов правого операнда */
        list_of_right_operand += right_operand->getNodesOfSamePrecedenceWithParenthesesOpening(is_invert);
    }
    else
    {
        // Добавить правый операнд в список правого операнда элементов
        list_of_right_operand.append(OperandOfExpr{nullptr, right_operand, true});
    }

    // Считать заданный узел родителем первого элемента списка элементов правого операнда
    list_of_right_operand[0].parent = this;
    list_of_right_operand[0].is_first_elem = false;

    // Добавить в список операндов списки левого и правого операндов заданного узла
    list += list_of_left_operand + list_of_right_operand;

    // Вернуть список операндов
    return list;
}

/*!
 * \brief Построить дерево выражения по элементам в списке
 * \param [in] list - список
 * \return указатель на корень дерева
 */
NodeOfExprTree* NodeOfExprTree::listToTree(QList<OperandOfExpr>& list)
{
    if(list.size() == 0) return nullptr;

    // Если первый элемент списка не является первым элементом дерева
    if (!list[0].is_first_elem)
    {
        // Сделать первый элемент списка первым элементом дерева
        if(list[0].parent->type == BIN_MINUS)
        {
            list[0].parent = nullptr;
            list[0].operand = new NodeOfExprTree("~", nullptr, list[0].operand);
            list[0].is_first_elem = true;
        }
        else if(list[0].parent->type == DIVISION)
        {
            list.prepend(OperandOfExpr{nullptr, new NodeOfExprTree("1"), true});
        }
    }

    // Считать операнд первого элемента списка left_operand
    NodeOfExprTree* _left_operand = list[0].operand;
    int list_len = list.size();
    for (int i = 1; i < list_len; i++)// Для каждого элемента списка кроме первого
    {
        // Если текущий элемент является первым элементом дерева
        if (list[i].is_first_elem)
        {
            // Создать симметричный узел того же приоритета и считать его родителем текущего узла
            if(type == PLUS || type == BIN_MINUS)
            {
                NodeOfExprTree* plus = new NodeOfExprTree("+", nullptr, list[i].operand);
                list[i].parent = plus;
            }
            else if(type == DIVISION || type == MULTIPLICATION)
            {
                NodeOfExprTree* multiply = new NodeOfExprTree("*", nullptr, list[i].operand);
                list[i].parent = multiply;
            }
        }

        // Считать правым операндом родителя текущего элемента операнд текущего элемента
        list[i].parent->right_operand = list[i].operand;

        // Установить left_operand как левый операнд родителя текущего элемента списка
        list[i].parent->left_operand = _left_operand;

        // Считать родителя текущего элемента списка left_operand
        _left_operand = list[i].parent;
    }

    // Вернуть родителя последнего элемента
    return list.last().parent;
}

/*!
 * \brief Получить список элементов сортировки в дереве, начиная с заданного узла
 * \return список элементов сортировки
 */
QList<OperandOfExpr> NodeOfExprTree::getSortedList()
{
    //... Считать список узлов одного уровня приоритета пустым
    QList<OperandOfExpr> list;

    // Если заданный узел есть узел типа оператора слагаемаго
    if(type == PLUS || type == BIN_MINUS)
    {
        // Получить список слагаемых и добавить его в список узлов одного уровня приоритета
        list += getNodesOfSamePrecedenceWithParenthesesOpening();
    }
    else
    {
        // Получить список и добавить его в список узлов одного уровня приоритета
        list += getListOfNodesOfSamePrecedenceLevel();
    }

    // Вернуть список узлов одного уровня приоритета
    return list;
}

/*!
 * \brief Получить инфиксную запись выражения из дерева этого выражения
 * \param [in] is_first_elem - флаг: true - указанный узел является первым операндом родителя, false - иначе
 * \return строка инфиксной записи выражения
 */
QString NodeOfExprTree::treeToInfix(bool is_first_elem)
{
    bool is_first_elem_for_operand = false;
    bool is_expr_in_parentheses = false;

    // ...Считать строку инфиксной записи пустой
    QString infix;
    QString infix_of_left_operand;
    QString infix_of_right_operand;

    // Если у заданного узла есть левый операнд
    if(left_operand != nullptr)
    {
        // Получить инфиксную запись левого операнда заданного узла, установив флаг первого элемента, если заданный оператор большего приоритета, чем левый операнд, или он уже установлен
        if(getPrecedenceType() < left_operand->getPrecedenceType() || is_first_elem) is_first_elem_for_operand = true;
        infix_of_left_operand = left_operand->treeToInfix(is_first_elem_for_operand);

        /* Если левый операнд заданного узла типа оператора унарный минус и не является первым элементом выражения
         или является узлом типа оператора меньшего приоритета, чем приоритет типа оператора заданного узла*/
        is_expr_in_parentheses = (left_operand->type == UN_MINUS && !is_first_elem_for_operand)
                                 || (getPrecedenceType() < left_operand->getPrecedenceType() && left_operand->type != NUM
                                     && left_operand->type != VAR && !isComparisonOperator(value));
        if(is_expr_in_parentheses)
        {
            // Взять полученную запись в скобки
            infix_of_left_operand = "(" + infix_of_left_operand + ")";
            is_expr_in_parentheses = false;
        }
        // Добавить в инфиксную запись выражения получившуюся инфиксную запись левого операнда заданного узла
        infix += infix_of_left_operand + " ";
        is_first_elem_for_operand = false;
    }

    // Добавить в инфиксную запись выражения значение заданного узла
    infix += valueToStr();
    if(type != NUM && type != VAR && type != UN_MINUS) infix += " ";

    // Если у заданного узла есть правый операнд
    if(right_operand != nullptr)
    {
        // Получить инфиксную запись правого операнда заданного узла, установив флаг первого элемента, если заданный оператор большего приоритета, чем правый операнд
        if(getPrecedenceType() < right_operand->getPrecedenceType() || isComparisonOperator(value)) is_first_elem_for_operand = true;
        infix_of_right_operand = right_operand->treeToInfix(is_first_elem_for_operand);

        /* Если правый операнд заданного узла типа унарный минус или
        заданный узел есть несимметричный узел, а правый операнд типа оператора приоритета не больше заданного узла */
        is_expr_in_parentheses = right_operand->type == UN_MINUS
                                 || ((getPrecedenceType() < right_operand->getPrecedenceType()
                                    || (!isSymmetricOperator() && right_operand->getPrecedenceType() == getPrecedenceType()))
                                     && right_operand->type != NUM && right_operand->type != VAR && !isComparisonOperator(value));
        if(is_expr_in_parentheses)
        {
            // Взять полученную запись в скобки
            infix_of_right_operand = "(" + infix_of_right_operand + ")";
        }
        // Добавить в инфиксную запись выражения получившуюся инфиксную запись правого операнда заданного узла
        infix += infix_of_right_operand;
    }

    // Вернуть инфиксную запись выражения
    return infix;
}

/*!
 * \brief Получить степень выражения
 * \return степень выражения
 */
int NodeOfExprTree::getDegreeOfExpr()
{
    // Считать степень выражения нулевой
    int degree = 0;
    // Считать степень левого и правого операндов заданного узла нулевой
    int degree_of_left_operand = 0;
    int degree_of_right_operand = 0;

    // Считать степень равную единице, если заданный узел есть узел типа переменная, и вернуть её
    if(type == VAR) return 1;
    // Считать степень равную нулю, если заданный узел есть узел типа число, и вернуть её
    if(type == NUM) return 0;

    // Получить степени левого и правого операндов заданного узла
    if(left_operand) degree_of_left_operand = left_operand->getDegreeOfExpr();
    if(right_operand) degree_of_right_operand = right_operand->getDegreeOfExpr();

    // Если заданный узел есть типа оператора сложения или сравнения
    if(type == PLUS || type == BIN_MINUS || isComparisonOperator(value))
    {
        // Считать степень выражения максимальной среди степеней левого и правого операндов заданного узла
        if(degree_of_left_operand >= degree_of_right_operand)
            degree += degree_of_left_operand;
        else
            degree += degree_of_right_operand;
    }
    else
    {
        // Прибавить к степени выражения степень левого операнда заданного узла
        degree += degree_of_left_operand;
        // Если заданный узел типа оператора деление
        if(type == DIVISION)
        {
            // Отнять от степени выражения степень правого операнда заданного узла
            degree -= degree_of_right_operand;
        }
        else
        {
            // Прибавить от степени выражения степень правого операнда заданного узла
            degree += degree_of_right_operand;
        }
    }

    // Вернуть степень выражения
    return degree;
}

/*!
 * \brief Получить список листьев дерева, корнем которого является заданный узел
 * \return список листьев дерева
 */
QList<NodeOfExprTree*> NodeOfExprTree::getLeavesOfTree()
{
    // ... Считать список листьев пустым
    QList<NodeOfExprTree*> leaves;

    // Если заданный узел лист дерева
    if (type == VAR || type == NUM)
    {
        // Добавить заданный узел в список листьев деревьев
        leaves.append(this);
        // Вернуть список листьев
        return leaves;
    }

    // Получить список листьев операндов заданного листа
    if(left_operand != nullptr)
    {
        leaves += left_operand->getLeavesOfTree();
    }
    if(right_operand != nullptr)
    {
        leaves += right_operand->getLeavesOfTree();
    }

    // Вернуть список листьев
    return leaves;
}

/*!
 * \brief Получить список имён переменных из списка листов дерева
 * \param [in] leaves - список элементов
 * \return спосок переменных
 */
QList<NodeOfExprTree*> NodeOfExprTree::getListOfVariableIDs(QList<NodeOfExprTree*> leaves)
{
    //...Считать список переменных пустым
    QList<NodeOfExprTree*> vars;

    // Для кожного элемента списка
    int count_leaves = leaves.size();
    for(int i = 0; i < count_leaves; i++)
    {
        // Если текущий элемент есть переменная - добавить его в список
        if (leaves[i]->type == VAR)
        {
            vars.append(leaves[i]);
        }
    }

    // Вернуть список переменных
    return vars;
}

/*!
 * \brief Определить кол-во выражений в скобках в текущем выражении
 * \return кол-во выражений в скобках
 */
int NodeOfExprTree::getNumOfParentheses()
{
    // Считать, что кол-во найденных выражений в скобках равно 0
    int count_of_expr = 0;

    // Получить список элементов на одном уровне заданного узла
    QList<OperandOfExpr> list = getListOfNodesOfSamePrecedenceLevel();

    int list_len = list.size();
    for(int i = 0; i < list_len; i++) // Для каждого элемента полученного списка
    {
        // Пропутить унарные минусы текущего элемента
        NodeOfExprTree* elem = nullptr;
        list[i].operand->getNodeBySkippingUnaryMinus(&elem);
        // Если текущий элемент оператор
        if(isOperator(elem->value))
        {
            // Считать, что найдено новое выражение в скобках
            count_of_expr++;
        }
    }

    // Вернуть кол-во найденных выражений в скобках
    return count_of_expr;

}
