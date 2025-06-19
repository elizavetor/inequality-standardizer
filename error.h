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
    ErrorType type;         // тип ошибки
    int pos;                // позиция ошибки
    QString error_string;   // строка, содержащая ошибку

public:
    Error();
    Error(ErrorType type);
    Error(ErrorType type, int pos, QString error_token);

    /*!
     * \brief Получить сообщение об ошибке известного типа
     * \return строка, содержащая сообщение об ошибке
    */
    QString getErrorMessageFor();
};

#endif // ERROR_H
