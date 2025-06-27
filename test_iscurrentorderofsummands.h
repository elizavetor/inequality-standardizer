/*!
* \file
* \brief Заголовочный файл класса Test_isCurrentOrderOfSummands для тестирования метода OperandOfExpr::isCurrentOrderOfSummands программы nequalityStandardizer.
*/

#ifndef TEST_ISCURRENTORDEROFSUMMANDS_H
#define TEST_ISCURRENTORDEROFSUMMANDS_H
#include "nodeofexprtree.h"
#include <QtTest/QtTest>
#include <QObject>

class Test_isCurrentOrderOfSummands : public QObject
{
    Q_OBJECT
public:
    explicit Test_isCurrentOrderOfSummands(QObject *parent = nullptr);

private slots:
    void testIsCurrentOrderOfSummands();
    void testIsCurrentOrderOfSummands_data();
};

#endif // TEST_ISCURRENTORDEROFSUMMANDS_H
