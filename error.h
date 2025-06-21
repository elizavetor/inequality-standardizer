#ifndef ERROR_H
#define ERROR_H
#include <QObject>

enum ErrorType{
    NO_DEFINED,
    NO_INPUT_FILE, NO_OUTPUT_FILE,
    INCORRECT_DELIMITER, NOT_ENOUGH_OPERANDS, MISSING_OPERATOR,
    INVALID_SEQUENCE, COMPARISON_OPERATOR_IN_PARENTHESES,
    NO_COMPARISON_OPERATOR, MULTIPLE_COMPARISON_OPERATORS
};

class Error
{
private:
    ErrorType type;              // тип ошибки
    int pos;                     // позиция ошибки
    QStringList error_strings;   // строка, содержащая ошибку

public:
    Error();
    Error(ErrorType _type, int _pos = -1, QStringList _error_strings = {});

    /*!
     * \brief Получить сообщение об ошибке известного типа
     * \return строка, содержащая сообщение об ошибке
    */
    QString getErrorMessageFor();

    /*!
     * \brief Метод для вывода информации об ошибке (для тестирования)
     * \return строка, содержащая информацию об объекте
     */
    QString toString() const;
};

#endif // ERROR_H
