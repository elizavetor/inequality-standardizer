#ifndef TEST_SORTOPERANDSALPHABETICALLY_H
#define TEST_SORTOPERANDSALPHABETICALLY_H

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
    void testSortOperandsAlphabetically_data();
};

#endif // TEST_SORTOPERANDSALPHABETICALLY_H
