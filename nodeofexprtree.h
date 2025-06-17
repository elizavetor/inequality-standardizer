#ifndef NODEOFEXPRTREE_H
#define NODEOFEXPRTREE_H

#include <QObject>

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
