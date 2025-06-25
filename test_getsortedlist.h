#ifndef TEST_GETSORTEDLIST_H
#define TEST_GETSORTEDLIST_H

#include "testingfunctions.h"
#include <QObject>
#include <QtTest/QtTest>

class Test_getSortedList : public QObject
{
    Q_OBJECT
public:
    explicit Test_getSortedList(QObject *parent = nullptr);

private slots:
    void testGetSortedList();
    void testGetSortedList_data();
};

#endif // TEST_GETSORTEDLIST_H
