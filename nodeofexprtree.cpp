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
