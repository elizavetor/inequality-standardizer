/*!
* \file
* \brief Заголовочный файл класса Test_isCurrentOrderOfParenthesisedExpressions для тестирования метода OperandOfExpr::isCurrentOrderOfParenthesisedExpressions программы nequalityStandardizer.
*/

#ifndef TEST_ISCURRENTORDEROFPARENTHESISEDEXPRESSIONS_H
#define TEST_ISCURRENTORDEROFPARENTHESISEDEXPRESSIONS_H
#include "nodeofexprtree.h"
#include <QtTest/QtTest>
#include <QObject>

class Test_isCurrentOrderOfParenthesisedExpressions : public QObject
{
    Q_OBJECT
public:
    explicit Test_isCurrentOrderOfParenthesisedExpressions(QObject *parent = nullptr);

private slots:
    void testIsCurrentOrderOfParenthesisedExpressions();
    void testIsCurrentOrderOfParenthesisedExpressions_data();
};

#endif // TEST_ISCURRENTORDEROFPARENTHESISEDEXPRESSIONS_H
