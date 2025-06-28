/*!
* \file
* \brief Заголовочный файл класса Test_postfixToTree для тестирования функции postfixToTree программы inequalityStandardizer.
*/

#ifndef TEST_POSTFIXTOTREE_H
#define TEST_POSTFIXTOTREE_H
#include "testingfunctions.h"
#include <QObject>
#include <QtTest/QtTest>

/*!
 * \brief Класс для тестирования функции postfixToTree
 */
class Test_postfixToTree : public QObject
{
    Q_OBJECT
public:
    explicit Test_postfixToTree(QObject *parent = nullptr);

private slots:
    void testPostfixToTree();
    void testPostfixToTree_data();
};

#endif // TEST_POSTFIXTOTREE_H
