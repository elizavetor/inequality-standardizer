/*!
* \file
* \brief Заголовочный файл функций для тестирования программы inequalityStandardizer.
*/

#ifndef TESTINGFUNCTIONS_H
#define TESTINGFUNCTIONS_H
#include "nodeofexprtree.h"
#include "error.h"
#include <QObject>
#include <QSet>

/*!
 * \brief Сравнивает ожидаемое дерево с полученным и формирует сообщение о различиях
 * \param [in] exp_node - ожидаемое дерево
 * \param [in] real_node - полученное дерево
 * \param [in,out] path - путь проверки деревьев
 * \param [out] error_message - сообщение о различии
 * \return true, если равны два дерева, false - иначе
 */
bool compareTrees(const NodeOfExprTree* exp_node, const NodeOfExprTree* real_node, QStringList& path, QString& error_message);

/*!
 * \brief Сравнивает ожидаемое множество ошибок с полученным и формирует сообщение о различиях
 * \param [in] errors - множество полученных ошибок
 * \param [in] expErrors - множество ожидаемых ошибок
 * \return сообщение о различиях во множествах
 */
QString compareErrorSets(const QSet<Error>& errors, const QSet<Error>& exp_errors);

/*!
 * \brief Сравнивает ожидаемый список елементов с полученным и выводит сообщение об ошибке
 * \param [in] expr_list - ожидаемый список
 * \param [in] real_list - полученный список
 * \return сообщение об ошибке
 */
QString compareListsOfNodes(QList<OperandOfExpr>& exp_list, QList<OperandOfExpr>& real_list);

#endif // TESTINGFUNCTIONS_H
