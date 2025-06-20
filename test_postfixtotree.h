#ifndef TEST_POSTFIXTOTREE_H
#define TEST_POSTFIXTOTREE_H

#include "nodeofexprtree.h"

#include <QObject>
#include <QtTest/QtTest>

class Test_postfixToTree : public QObject
{
    Q_OBJECT
public:
    explicit Test_postfixToTree(QObject *parent = nullptr);

private slots:
    void testPostfixToTree();
    void testPostfixToTree_data();
};

/*!
 * \brief Сравнивает ожидаемое дерево с полученным и формирует сообщение о различиях
 * \param [in] exp_node - ожидаемое дерево
 * \param [in] real_node - полученное дерево
 * \param [in,out] path - путь проверки деревьев
 * \param [out] error_message - сообщение о различии
 * \return равны ли два дерева
 */
bool compareTrees(const NodeOfExprTree* exp_node, const NodeOfExprTree* real_node, QStringList& path, QString& error_message);
#endif // TEST_POSTFIXTOTREE_H
