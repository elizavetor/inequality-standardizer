/*!
* \file
* \brief Файл содержит реализацию функций для тестирования программы inequalityStandardizer.
*/

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

/*!
 * \brief Сравнивает ожидаемый список елементов с полученным и выводит сообщение об ошибке
 * \param [in] expr_list - ожидаемый список
 * \param [in] real_list - полученный список
 * \return строку ошибки
 */
QString compareListsOfNodes(QList<OperandOfExpr>& exp_list, QList<OperandOfExpr>& real_list)
{
    // Считать, что ошибок не найдено
    QString error = "";
    QStringList path = {};
    QString error_message = "";

    // Если кол-во элементов ожидаемого и полученного списков не совпадают
    if(exp_list.size() != real_list.size())
    {
        // Считать, что ошибка найдена
        error = "\nThe number of elements of the expected and received lists do not match\n";
    }

    for(int i = 0; i < real_list.size() && error == ""; i++) // Для каждой пары элементов спиской i-ого индекса и пока не найдена ошибка
    {
        // Если родители текущей пары не совпадают
        if(real_list[i].parent && exp_list[i].parent)
        {
            if(*real_list[i].parent != *exp_list[i].parent)
            {
                // Считать, что ошибка найдена
                error = "\nThe parents of the expected and received elements " + QString::number(i + 1) + " do not match\n";
                error += "Real parent: " + real_list[i].parent->getValue() + "\n";
                error += "Exp parent: " + exp_list[i].parent->getValue() + "\n";
            }
        }
        else if((real_list[i].parent == nullptr || exp_list[i].parent == nullptr) && !(real_list[i].parent == nullptr && exp_list[i].parent == nullptr))
        {
            error = "\nThe parents of the expected and received elements " + QString::number(i + 1) + " do not match\n";
            if(real_list[i].parent == nullptr)
            {
                error += "Real parent: nullptr\n";
                error += "Exp parent: " + exp_list[i].parent->getValue() + "\n";
            }
            else
            {
                error += "Real parent: " + real_list[i].parent->getValue() + "\n";
                error += "Exp parent: nullptr\n";
            }

        }
        // ИначеЕсли операнд текущего элемента не равен ожидаемому
        if(!compareTrees(exp_list[i].operand, real_list[i].operand, path, error_message))
        {
            // Считать, что ошибка найдена
            error = "\nWhen comparing the operands of the received and expected elements " + QString::number(i + 1) + ", the following error was found:" + error_message;
        }
        // ИначеЕсли значение флага первого элемента списка не равен ожидаемому
        if (real_list[i].is_first_elem != exp_list[i].is_first_elem)
        {
            // Считать, что ошибка найдена
            error = "\nThe values of the flags of the first element of the received and expected element " + QString::number(i + 1) + " do not match\n";
            error += "Real flag: ";
            real_list[i].is_first_elem == true ? error += "true\n" : error += "false\n";
            error += "Exp flag: ";
            exp_list[i].is_first_elem == true ? error += "true\n" : error += "false\n";
        }
    }

    // Вернуть ошибку
    return error;
}
