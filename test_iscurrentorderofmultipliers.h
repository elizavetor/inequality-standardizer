/*!
* \file
* \brief Заголовочный файл класса Test_isCurrentOrderOfMultipliers для тестирования метода OperandOfExpr::isCurrentOrderOfMultipliers программы nequalityStandardizer.
*/

#ifndef TEST_ISCURRENTORDEROFMULTIPLIERS_H
#define TEST_ISCURRENTORDEROFMULTIPLIERS_H
#include "nodeofexprtree.h"
#include <QtTest/QtTest>
#include <QObject>

class Test_isCurrentOrderOfMultipliers : public QObject
{
    Q_OBJECT

public:
    explicit Test_isCurrentOrderOfMultipliers(QObject *parent = nullptr);

private slots:
    void testIsCurrentOrderOfMultipliers();
    void testIsCurrentOrderOfMultipliers_data();
};

#endif // TEST_ISCURRENTORDEROFMULTIPLIERS_H
