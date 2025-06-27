/*!
* \file
* \brief Заголовочный файл класса Test_getListOfNodesOfSamePrecedenceLevel для тестирования метода NodeOfExprTree::getListOfNodesOfSamePrecedenceLevel программы nequalityStandardizer.
*/

#ifndef TEST_GETLISTOFNODESOFSAMEPRECEDENCELEVEL_H
#define TEST_GETLISTOFNODESOFSAMEPRECEDENCELEVEL_H
#include "testingfunctions.h"
#include <QtTest/QtTest>
#include <QObject>

class Test_getListOfNodesOfSamePrecedenceLevel : public QObject
{
    Q_OBJECT
public:
    explicit Test_getListOfNodesOfSamePrecedenceLevel(QObject *parent = nullptr);

private slots:
    void testGetListOfNodesOfSamePrecedenceLevel();
    void testGetListOfNodesOfSamePrecedenceLevel_data();
};

#endif // TEST_GETLISTOFNODESOFSAMEPRECEDENCELEVEL_H
