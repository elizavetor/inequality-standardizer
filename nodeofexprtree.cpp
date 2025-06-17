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
    else if (value == "==")
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
 * \brief Определить правильность расстановки двух множителей по алфавиту
 * \param [in] other - второй по порядку элемент
 * \return true, если порядок верный, false - иначе
 */
bool OperandOfExpr::isCurrentOrderOfMultipliers(const OperandOfExpr& other) const
{
    // Получить первый множитель, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы
    // Получить второй множитель, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы

    // Определить, соблюдается ли порядок: сначала числа, потом переменные, далее - выражения в скобках
    // Если типы множителей одинаковые
        // Определить, меньше ли первый множитель второго с учётом всех минусов, если их тип число
        // Определить, меньше ли первый множитель второго, если их тип переменная
        // Определить правильность расстановки множителей, если они есть выражения в скобках

    // Вернуть получившийся результат

    return false;
}
