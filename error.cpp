#include "error.h"

Error::Error()
{
    type = NO_DEFINED;
    pos = -1;
    error_strings = {};
}


Error::Error(ErrorType _type, int _pos, QStringList _error_strings)
{
    type = _type;
    pos = _pos;
    error_strings = _error_strings;
}

/*!
 * \brief Получить сообщение об ошибке известного типа
 * \return строка, содержащая сообщение об ошибке
 */
QString Error::getErrorMessageFor()
{
    QString message;
    switch (type) {
    case NO_INPUT_FILE:
        message = "Неверно указан файл с входными данными. Возможно, файл не существует.";
        break;
    case NO_OUTPUT_FILE:
        message = "Неверно указан файл для выходных данных. Возможно, указанного расположения не существует или нет прав на запись.";
        break;
    case INCORRECT_DELIMITER:
        message = "Некорректные разделители. Программа принимает на вход файлы из одной строки, в которой операции и операнды разделены пробелами.";
        break;
    case NOT_ENOUGH_OPERANDS:
        message = "Во входной строке пропущен операнд для операции «" + error_strings.join("», ") + "» (позиция " + QString::number(pos) + ").";
        break;
    case MISSING_OPERATOR:
        message = "Во входной строке пропущен знак операции для операнда «" + error_strings.join("», ") + "» (позиция " + QString::number(pos) + ").";
        break;
    case INVALID_SEQUENCE:
        message = "Некорректная последовательность постфиксной записи во входном файле: «" + error_strings.join("», ") + "» (позиция " + QString::number(pos) + ").";
        break;
    case COMPARISON_OPERATOR_IN_PARENTHESES:
        message = "Операция «" + error_strings.join("», ") + "» (позиция " + QString::number(pos) + ") не должна предшествовать никаким операциям.";
        break;
    case NO_COMPARISON_OPERATOR:
        message = "Отсутствует одна из операций сравнения «==», «>=», «<=». «>», «<», «!=» во входном (не)равенстве.";
        break;
    case MULTIPLE_COMPARISON_OPERATORS:
        message = "Найдено несколько операций сравнения: «" + error_strings.join("», ") + "». Во входном (не)равенстве должна быть только одна из операций сравнения «==», «>=», «<=». «>», «<», «!=».";
        break;
    case NO_DEFINED:
        message = "";
        break;
    default:
        break;
    }

    return message;
}
