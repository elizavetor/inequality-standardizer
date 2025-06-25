#include "test_sortoperandsalphabetically.h"

Test_sortOperandsAlphabetically::Test_sortOperandsAlphabetically(QObject *parent)
    : QObject{parent}
{}

void Test_sortOperandsAlphabetically::testSortOperandsAlphabetically()
{
    QFETCH(NodeOfExprTree*, start_tree);
    QFETCH(NodeOfExprTree*, exp_final_tree);

    // Получить дерево
    NodeOfExprTree* real_final_tree = start_tree->sortOperandsAlphabetically();

    // Сравнить полученное дерево с ожидаемым
    QString error_message;
    QStringList path;
    QVERIFY2(compareTrees(exp_final_tree, real_final_tree, path, error_message), error_message.toUtf8());
}
