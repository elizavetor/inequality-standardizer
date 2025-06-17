#ifndef NODEOFEXPRTREE_H
#define NODEOFEXPRTREE_H

#include <QObject>
#include "function.cpp"

class NodeOfExprTree;

enum OperatorType{
    UNDEFINED,
    UN_MINUS,
    MULTIPLICATION, DIVISION,
    PLUS, BIN_MINUS,
    EQUAL, NOT_EQUAL, GREATER, LESS, GREATER_OR_EQUAL, LESS_OR_EQUAL,
    NUM, VAR
};

struct OperandOfExpr
{
    NodeOfExprTree* parent;     // родитель операнда
    NodeOfExprTree* operand;    // операнд
    bool is_first_elem;         // флаг: true - операнд есть первый элемент выражения (нет знака перед собой), false - иначе
};

class NodeOfExprTree
{
private:
    OperatorType type;                 // тип узла
    QString value;                     // значение узла
    NodeOfExprTree* left_operand;      // левый операнд узла
    NodeOfExprTree* right_operand;     // правый операнд узла

public:
    NodeOfExprTree();
    NodeOfExprTree(QString _value, NodeOfExprTree* _left_operand = nullptr, NodeOfExprTree* _right_operand = nullptr);
};

#endif // NODEOFEXPRTREE_H
