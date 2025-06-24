#include "testingfunctions.h"

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
    if (real_node != nullptr)
        path.append(real_node->getValue());
    else path.append("nullptr");

    // Если один из узлов пустой
    if (real_node == nullptr || exp_node == nullptr)
    {
        // Считать, что узлы неравны и вернут false
        if(exp_node == nullptr)
        {
            error_message += "\nThe real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: nullptr\n";
        }
        else
            error_message += "\nThe real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: " + exp_node->getValue() + "\n";

        return false;
    }

    // Если узлы различны
    if (*exp_node != *real_node)
    {
        // Считать, что узлы неравны и вернут false
        error_message += "\nThe real node at the end of the path does not match the expected node.\nPath: " + path.join(' ') + "\nExpected node: " + exp_node->getValue() + "\n";
        return false;
    }

    // Считать, что ошибка найдена, если левые или правые операнды полученного и ожидаемого узлов различны
    if (!compareTrees(exp_node->getLeftOperand(), real_node->getLeftOperand(), path, error_message) ||
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
    QSet<Error> missing_errors = exp_errors - errors;
    QSet<Error> unexpected_errors = errors - exp_errors;

    QString differences_in_errors; // Итоговая строка с отличиями во множествах ошибок

    if (!missing_errors.isEmpty() || !unexpected_errors.isEmpty())
    {
        // Записываем пропущенные ошибки
        if (!missing_errors.isEmpty())
        {
            differences_in_errors += "\nMissing errors:\n";

            QSet<Error>::const_iterator i1;
            for (i1 = missing_errors.constBegin(); i1 != missing_errors.constEnd(); i1++)
                differences_in_errors += i1->toString() + "\n";
        }

        // Записываем непредвиденные ошибки
        if (!unexpected_errors.isEmpty())
        {
            differences_in_errors += "\nUnexpected errors returned:\n";

            QSet<Error>::const_iterator i2;
            for (i2 = unexpected_errors.constBegin(); i2 != unexpected_errors.constEnd(); i2++)
                differences_in_errors += i2->toString() + "\n";
        }
    }

    return differences_in_errors;
}
