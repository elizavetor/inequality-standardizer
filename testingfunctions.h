#ifndef TESTINGFUNCTIONS_H
#define TESTINGFUNCTIONS_H
#include "nodeofexprtree.h"
#include "error.h"

/*!
 * \brief Сравнивает ожидаемое дерево с полученным и формирует сообщение о различиях
 * \param [in] exp_node - ожидаемое дерево
 * \param [in] real_node - полученное дерево
 * \param [in,out] path - путь проверки деревьев
 * \param [out] error_message - сообщение о различии
 * \return равны ли два дерева
 */
bool compareTrees(const NodeOfExprTree* exp_node, const NodeOfExprTree* real_node, QStringList& path, QString& error_message);

/*!
 * \brief Сравнивает ожидаемое множество ошибок с полученным и формирует сообщение о различиях
 * \param [in] errors - множество полученных ошибок
 * \param [in] expErrors - множество ожидаемых ошибок
 * \return сообщение о различиях во множествах
 */
QString compareErrorSets(const QSet<Error>& errors, const QSet<Error>& exp_errors);



#endif // TESTINGFUNCTIONS_H
