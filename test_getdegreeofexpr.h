/*!
* \file
* \brief Заголовочный файл класса Test_getDegreeOfExpr для тестирования метода NodeOfExprTree::getDegreeOfExpr программы nequalityStandardizer.
*/

#ifndef TEST_GETDEGREEOFEXPR_H
#define TEST_GETDEGREEOFEXPR_H
#include "nodeofexprtree.h"
#include <QObject>
#include <QtTest/QtTest>

class Test_getDegreeOfExpr : public QObject
{
    Q_OBJECT
public:
    explicit Test_getDegreeOfExpr(QObject *parent = nullptr);

private slots:
    void testGetDegreeOfExpr();
    void testGetDegreeOfExpr_data();
};

#endif // TEST_GETDEGREEOFEXPR_H
