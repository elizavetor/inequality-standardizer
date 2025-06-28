/*!
* \file
* \brief Заголовочный файл класса Test_operatorGt для тестирования метода OperandOfExpr::operator> программы inequalityStandardizer.
*/

#ifndef TEST_OPERATORGT_H
#define TEST_OPERATORGT_H
#include "nodeofexprtree.h"
#include <QObject>
#include <QtTest/QtTest>

/*!
 * \brief Класс для тестирования метода OperandOfExpr::operator>
 */
class Test_operatorGt : public QObject
{
    Q_OBJECT
public:
    explicit Test_operatorGt(QObject *parent = nullptr);

private slots:
    void testOperatorGt();
    void testOperatorGt_data();
};

#endif // TEST_OPERATORGT_H
