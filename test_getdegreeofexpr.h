#ifndef TEST_GETDEGREEOFEXPR_H
#define TEST_GETDEGREEOFEXPR_H

#include <QObject>

class Test_getDegreeOfExpr : public QObject
{
    Q_OBJECT
public:
    explicit Test_getDegreeOfExpr(QObject *parent = nullptr);

public slots:
    void testGetDegreeOfExpr();
    void testGetDegreeOfExpr_data();
};

#endif // TEST_GETDEGREEOFEXPR_H
