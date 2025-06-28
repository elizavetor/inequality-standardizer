/*!
* \file
* \brief Заголовочный файл класса Test_listToTree для тестирования метода NodeOfExprTree::listToTree программы nequalityStandardizer.
*/

#ifndef TEST_LISTTOTREE_H
#define TEST_LISTTOTREE_H
#include "testingfunctions.h"
#include <QtTest/QtTest>
#include <QObject>

/*!
 * \brief Класс для тестирования метода NodeOfExprTree::listToTree
 */
class Test_listToTree : public QObject
{
    Q_OBJECT
public:
    explicit Test_listToTree(QObject *parent = nullptr);

private slots:
    void testListToTree();
    void testListToTree_data();
};

#endif // TEST_LISTTOTREE_H
