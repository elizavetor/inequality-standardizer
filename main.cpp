/*!
* \file
* \brief Данный файл содержит главную функцию программы inequalityStandardizer.
*
* \mainpage Документация для программы "Inequality Standardizer"
Программа предназначена для приведения (не)равенства к единому виду, перенеся все слагаемые в левую часть и упорядочив их (а также множители) по алфавиту.
Для функционирования программы необходима операционная система Windows 7 или выше.
Программа разработана на языке С++ с использованием стандартных библиотек C++, библиотеки Qt и фреймворка Qt Creator.
Программа должна получать два аргумента командной строки: имя входного файла и имя выходного файла в формате (.txt),
или один аргумент командной строки для запуска модульных тестов: (--test).

Пример команды запуска программы:
* \code
./inequalityStandardizer.exe ./input.txt ./output.txt
* \endcode

* \author Гусева Елизавета
* \date 28 Июля 2025
* \version 1.0
*/

#include <QCoreApplication>
#include "nodeofexprtree.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>

/*!
 * \brief Главная функция программы inequalityStandardizer
 * \param [in] argc - количество переданных аргументов командной строки
 * \param [in] argv - переданные аргументы командной строки
 * \param [in] argv[0] - аргумент запуска программы
 * \param [in] argv[1] - путь к входному файлу (.txt) с выражением (или запрос запуска тестов)
 * \param [in] argv[2] - путь к выходному файлу (.txt) для вывода результата работы программы
 * \return 0 - программа завершилась успешно; 1 - была найдена ошибка
 */
int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Russian");

    QCoreApplication a(argc, argv);
    // Проверка аргументов командной строки
    if (argc == 2 && QString(argv[1]) == "--test") // Если передан запрос запуска тестов
    {
        runTests();
        return 0;
    }
    else if (argc != 3)
    {
        qDebug() << "Программа должна принимать три аргумента: <путь к программе> <путь к входному файлу> <путь к выходному файлу>";
        return 1;
    }

    // Получить строку постфиксной записи выражения из исходного файла
    QFile input_file(argv[1]);
    // Если найдена ошибка чтения
    if (!input_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        // Вывести сообщение об ошибке и завершить работу программы
        Error input_file_error(NO_INPUT_FILE);
        qDebug() << input_file_error.getErrorMessageFor();
        return 1;
    }
    QString postfix = input_file.readAll();
    input_file.close();

    // ...Считать список ошибок пустым
    QSet<Error> errors;
    QStringList comparison_operators = getListOfComparisonOperator(postfix);
    // Если в полученной строке нет операторов сравнения
    if(comparison_operators.isEmpty())
    {
        // Считать, что найдена ошибка NO_COMPARISON_OPERATOR, добавить её в список ошибок
        errors.insert(Error(NO_COMPARISON_OPERATOR));
    }
    // ИначеЕсли в полученной строке несколько операторов сравнения
    else if (comparison_operators.size() > 1)
    {
        // Считать, что найдена ошибка MULTIPLE_COMPARISON_OPERATORS, добавить её в список ошибок
        errors.insert(Error(MULTIPLE_COMPARISON_OPERATORS, -1, comparison_operators));
    }

    // Из постфиксной записи выражения получить дерево этого выражения
    NodeOfExprTree* tree = postfixToTree(postfix, errors);

    // Если найдены ошибки в построении дерева
    if(!errors.isEmpty())
    {
        // Вывести ошибки и завершить работу программы
        for (const Error& err : errors)
        {
            qDebug() << err.getErrorMessageFor();
        }
        return 1;
    }

    // Получить инфиксную запись выражения из дерева этого выражения
    QString infix_input_expr = tree->treeToInfix();

    // Вывести в выходной файл инфиксную запись выражения
    QFile output_file(argv[2]);
    // Если найдена ошибка записи
    if (!output_file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        // Вывести сообщение об ошибке и завершить работу программы
        Error output_file_error(NO_OUTPUT_FILE);
        qDebug() << output_file_error.getErrorMessageFor();
        NodeOfExprTree::delTree(tree);
        return 1;
    }
    QTextStream output(&output_file);
    output << infix_input_expr;

    // Перестроить дерево выражения, перенеся все слагаемые после знака сравнения в левую часть (не)равенства (до знака сравнения)
    tree->rearrangeForZeroComparison();

    // Отсортировать слагаемые и множители (не)равенства по алфавиту, начиная левого операнда корня дерева выражения
    tree->setLeftOperand(tree->getLeftOperand()->sortOperandsAlphabetically());

    // Из дерева выражения получить инфиксную запись этого выражения
    QString infix_output_expr = tree->treeToInfix();

    // Вывести в выходной файл инфиксную запись выражения
    output << "\n" << infix_output_expr;
    output_file.close();

    NodeOfExprTree::delTree(tree);
    return 0;
}
