#ifndef TEST_SORTOPERANDSALPHABETICALLY_H
#define TEST_SORTOPERANDSALPHABETICALLY_H

#include "nodeofexprtree.h"

#include "testingfunctions.h"
#include <QObject>
#include <QtTest/QtTest>

class Test_sortOperandsAlphabetically : public QObject
{
    Q_OBJECT
public:
    explicit Test_sortOperandsAlphabetically(QObject *parent = nullptr);

private slots:
    void testSortOperandsAlphabetically();
    void testSortOperandsAlphabeticallyToInfix_data();
};

#endif // TEST_SORTOPERANDSALPHABETICALLY_H
