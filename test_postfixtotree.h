#ifndef TEST_POSTFIXTOTREE_H
#define TEST_POSTFIXTOTREE_H

#include "nodeofexprtree.h"

#include <QObject>
#include <QtTest/QtTest>

class Test_postfixToTree : public QObject
{
    Q_OBJECT
public:
    explicit Test_postfixToTree(QObject *parent = nullptr);

private slots:
    void testPostfixToTree();
    void testPostfixToTree_data();
};

#endif // TEST_POSTFIXTOTREE_H
