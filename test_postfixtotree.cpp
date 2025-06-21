#include "test_postfixtotree.h"

Test_postfixToTree::Test_postfixToTree(QObject *parent)
    : QObject{parent}
{}

void Test_postfixToTree::testPostfixToTree()
{
    QFETCH(QString, postfix_notation);
    QFETCH(QSet<Error>, starting_errors);
    QFETCH(QSet<Error>, final_errors);
    QFETCH(NodeOfExprTree*, exp_tree);

    // Получить результат сравнения
    QSet<Error> real_errors = starting_errors;
    NodeOfExprTree* real_tree = postfixToTree(postfix_notation, real_errors);

    // Сравнить полученное дерево с ожидаемым
    QString error_message;
    QStringList path;
    QVERIFY2(compareTrees(exp_tree, real_tree, path, error_message), error_message.toUtf8());

    // Сравнить полученные ошибки с ожидаемыми
    QString differences_in_errors = compareErrorSets(real_errors, final_errors);
    QVERIFY2(differences_in_errors.isEmpty(), qPrintable(differences_in_errors));

}

void Test_postfixToTree::testPostfixToTree_data()
{
    // Добавить столбцы
    QTest::addColumn<QString>("postfix_notation");
    QTest::addColumn<QSet<Error>>("starting_errors");
    QTest::addColumn<QSet<Error>>("final_errors");
    QTest::addColumn<NodeOfExprTree*>("exp_tree");


    // 1. Только переменные
    QString postfix_notation = "a b +";

    QSet<Error> errors = {};

    NodeOfExprTree* a = new NodeOfExprTree("a");
    NodeOfExprTree* b = new NodeOfExprTree("b");
    NodeOfExprTree* a_plus_b = new NodeOfExprTree("+", a, b);

    QTest::newRow("Operation + with 2 var operand: a + b") << postfix_notation << errors << errors << a_plus_b;
}

/*!
 * \brief Сравнивает ожидаемое дерево с полученным и формирует сообщение о различиях
 * \param [in] exp_node - ожидаемое дерево
 * \param [in] real_node - полученное дерево
 * \param [in,out] path - путь проверки деревьев
 * \param [out] error_message - сообщение об различиях
 * \return равны ли два дерева
 */
bool compareTrees(const NodeOfExprTree* exp_node, const NodeOfExprTree* real_node, QStringList& path, QString& error_message)
{
    // Проверить текущие полученный и ожидаемый узлы...
    // Если узлы пустые
    if (real_node == nullptr && exp_node == nullptr)
    {
        // Считать, что узлы равны (вернут true)
        return true;
    }

    // Добавить текущий узел получившегося дерева в путь
    if (!path.isEmpty())
        path.append("->");
    if (exp_node != nullptr)
        path.append(real_node->getValue());
    else path.append("nullptr");

    // Если один из узлов пустой
    if (real_node == nullptr || exp_node == nullptr)
    {
        // Считать, что узлы неравны (вернут false)
        if(exp_node == nullptr)
        {
            error_message += "The real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: nullptr";
        }
        else
            error_message += "The real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: " + exp_node->getValue();

        return false;
    }

    // Если узлы различны
    if (*exp_node != *real_node)
    {
        // Считать, что узлы неравны (вернут false)
        error_message += "The real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: " + exp_node->getValue();
        return false;
    }

    // Считать, что ошибка найдена, если левые или правые операнды полученного и ожидаемого узлов различны
    if (!compareTrees(exp_node->getLeftOperand(), real_node->getRightOperand(), path, error_message) ||
        !compareTrees(exp_node->getRightOperand(), real_node->getRightOperand(), path, error_message))
    {
        return false;
    }

    // Удаление текущего узла из пути при отсутствии ошибок
    path.removeLast();
    if (!path.isEmpty())
        path.removeLast();

    return true;
}

/*!
 * \brief Сравнивает ожидаемое множество ошибок с полученным и формирует сообщение о различиях
 * \param [in] errors - множество полученных ошибок
 * \param [in] expErrors - множество ожидаемых ошибок
 * \return сообщение о различиях во множествах
 */
QString compareErrorSets(const QSet<Error>& errors, const QSet<Error>& exp_errors)
{
    // Получаем множества пропущенных и непредвиденных ошибок
    QSet<Error> missingErrors = exp_errors - errors;
    QSet<Error> unexpectedErrors = errors - exp_errors;

    QString differencesInErrors; // Итоговая строка с отличиями во множествах ошибок

    if (!missingErrors.isEmpty() || !unexpectedErrors.isEmpty())
    {
        // Записываем пропущенные ошибки
        if (!missingErrors.isEmpty())
        {
            differencesInErrors += "Missing errors:\n";

            QSet<Error>::const_iterator i1;
            for (i1 = missingErrors.constBegin(); i1 != missingErrors.constEnd(); i1++)
                differencesInErrors += i1->toString() + "\n";
        }

        // Записываем непредвиденные ошибки
        if (!unexpectedErrors.isEmpty())
        {
            differencesInErrors += "Unexpected errors returned:\n";

            QSet<Error>::const_iterator i2;
            for (i2 = unexpectedErrors.constBegin(); i2 != unexpectedErrors.constEnd(); i2++)
                differencesInErrors += i2->toString() + "\n";
        }
    }

    return differencesInErrors;
}
