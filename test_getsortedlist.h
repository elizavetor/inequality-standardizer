#ifndef TEST_GETSORTEDLIST_H
#define TEST_GETSORTEDLIST_H

#include "nodeofexprtree.h"
#include <QtTest/QtTest>

#include <QObject>

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
