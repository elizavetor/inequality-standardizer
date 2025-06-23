#ifndef TEST_TREETOINFIX_H
#define TEST_TREETOINFIX_H

#include "nodeofexprtree.h"

#include <QObject>
#include <QtTest/QtTest>

class Test_treeToInfix : public QObject
{
    Q_OBJECT
public:
    explicit Test_treeToInfix(QObject *parent = nullptr);

private slots:
    void testTreeToInfix();
    void testTreeToInfix_data();
};

#endif // TEST_TREETOINFIX_H
