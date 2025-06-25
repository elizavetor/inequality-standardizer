#ifndef TEST_GETNODESOFSAMEPRECEDENCEWITHPARENTHESESOPENING_H
#define TEST_GETNODESOFSAMEPRECEDENCEWITHPARENTHESESOPENING_H

#include "testingfunctions.h"
#include <QtTest/QtTest>

#include <QObject>

class Test_getNodesOfSamePrecedenceWithParenthesesOpening : public QObject
{
    Q_OBJECT
public:
    explicit Test_getNodesOfSamePrecedenceWithParenthesesOpening(QObject *parent = nullptr);

private slots:
    void testGetNodesOfSamePrecedenceWithParenthesesOpening();
    void testGetNodesOfSamePrecedenceWithParenthesesOpening_data();
};

#endif // TEST_GETNODESOFSAMEPRECEDENCEWITHPARENTHESESOPENING_H
