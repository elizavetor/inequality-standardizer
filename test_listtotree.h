#ifndef TEST_LISTTOTREE_H
#define TEST_LISTTOTREE_H

#include "nodeofexprtree.h"
#include <QtTest/QtTest>

#include <QObject>

class Test_listToTree : public QObject
{
    Q_OBJECT
public:
    explicit Test_listToTree(QObject *parent = nullptr);

private slots:
    void testListToTree();
    void testListToTree_data();
};

#endif // TEST_LISTTOTREE_H
