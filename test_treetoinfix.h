/*!
* \file
* \brief Заголовочный файл класса Test_treeToInfix для тестирования метода NodeOfExprTree::treeToInfix программы nequalityStandardizer.
*/

#ifndef TEST_TREETOINFIX_H
#define TEST_TREETOINFIX_H
#include "nodeofexprtree.h"
#include <QObject>
#include <QtTest/QtTest>

/*!
 * \brief Класс для тестирования метода NodeOfExprTree::treeToInfix
 */
class Test_treeToInfix : public QObject
{
    Q_OBJECT
public:
    explicit Test_treeToInfix(QObject *parent = nullptr);

private slots:
    void testTreeToInfix();
    void testTreeToInfix_data();
};

#endif // TEST_TREETOINFIX_H
