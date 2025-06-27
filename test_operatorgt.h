/*!
* \file
* \brief Заголовочный файл класса Test_operatorGt для тестирования метода OperandOfExpr::operatorGt программы nequalityStandardizer.
*/

#ifndef TEST_OPERATORGT_H
#define TEST_OPERATORGT_H
#include "nodeofexprtree.h"
#include <QObject>
#include <QtTest/QtTest>

class Test_operatorGt : public QObject
{
    Q_OBJECT
public:
    explicit Test_operatorGt(QObject *parent = nullptr);

private slots:
    void testOperatorGt();
    void testOperatorGt_data();
};

#endif // TEST_OPERATORGT_H
