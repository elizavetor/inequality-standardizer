#ifndef NODEOFEXPRTREE_H
#define NODEOFEXPRTREE_H

#include <QObject>
#include "error.h"

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

    /*!
     * \brief Определить правильность расстановки двух множителей по алфавиту
     * \param [in] other - второй по порядку узел
     * \return true, если порядок верный, false - иначе
     */
    bool isCurrentOrderOfMultipliers(const OperandOfExpr& other) const;
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

    /*!
     * \brief Вернуть значение узла
     * \return значение узла
     */
    QString getValue() const { return value; }

    /*!
     * \brief Вернуть левый операнд
     * \return указатель на левый операнд
     */
    NodeOfExprTree* getLeftOperand() const { return left_operand; }

    /*!
     * \brief Вернуть правый операнд
     * \return указатель на правый операнд
     */
    NodeOfExprTree* getRightOperand() const { return right_operand; }

    /*!
     * \brief Перегрузка оператора равенства для NodeOfExprTree
     */
    bool operator==(const NodeOfExprTree& other) const;
};

/*!
 * \brief Из постфиксной записи выражения получить дерево этого выражения
 * \param [in] expr － строка выражения в постфиксной записи
 * \param [out] errors － обнаруженные ошибки в постфиксной записи
 * \return указатель на корень построенного дерева
 */
NodeOfExprTree* postfixToTree(QString expr, QSet<Error> errors);

/*!
 * \brief Определить является ли строка числом
 * \param [in] token - проверяемый токен
 * \return true, если токен есть число, иначе - false
 */
bool isNum(QString token);

/*!
 * \brief Определить является ли токен переменной
 * \param [in] token - проверяемый токен
 * \return true, если токен есть переменная, иначе - false
 */
bool isVar(QString token);

/*!
 * \brief Определить является ли токен оператором
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isOperator(QString token);

#endif // NODEOFEXPRTREE_H
