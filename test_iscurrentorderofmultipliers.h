#ifndef TEST_ISCURRENTORDEROFMULTIPLIERS_H
#define TEST_ISCURRENTORDEROFMULTIPLIERS_H

#include "nodeofexprtree.h"
#include <QtTest/QtTest>

#include <QObject>

class Test_isCurrentOrderOfMultipliers : public QObject
{
    Q_OBJECT

private slots:
    void testIsCurrentOrderOfMultipliers();
    void testIsCurrentOrderOfMultipliers_data();
};

#endif // TEST_ISCURRENTORDEROFMULTIPLIERS_H
