#ifndef FUNCTION_H
#define FUNCTION_H
#include "error.h"
#include "nodeofexprtree.h"

#include <QObject>

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


#endif // FUNCTION_H
