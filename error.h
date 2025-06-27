/*!
 * \file
 * \brief Заголовочный файл для класса ошибки Error
 */

#ifndef ERROR_H
#define ERROR_H
#include <QObject>

/*!
 * \brief Перечисление типов ошибок
 */
enum ErrorType{
    NO_DEFINED,                             //!< Неопределённый тип
    NO_INPUT_FILE,                          //!< Некорректный файл с входными данными
    NO_OUTPUT_FILE,                         //!< Некорректный файл для выходных данных
    INCORRECT_DELIMITER,                    //!< Некорректные разделители
    NOT_ENOUGH_OPERANDS,                    //!< Недостаточно операндов у оператора
    MISSING_OPERATOR,                       //!< Пропущен оператор для операнда
    INVALID_SEQUENCE,                       //!< Некорректная последовательнось
    COMPARISON_OPERATOR_IN_PARENTHESES,     //!< Операторы сравнения в скобках
    NO_COMPARISON_OPERATOR,                 //!< Отсутствуют операторы сравнения
    MULTIPLE_COMPARISON_OPERATORS           //!< Много операторов сравнения
};

/*!
 * \brief Класс для хранения информации об ошибках.
 */
class Error
{
private:
    ErrorType type;              //!< тип ошибки
    int pos;                     //!< позиция ошибки
    QStringList error_strings;   //!< строки, содержащие ошибку

public:

    /*!
     * \brief Конструктор по умолчанию для класса Error
     */
    Error();

    /*!
     * \brief Конструктор с параметрами для класса Error
     */
    Error(ErrorType _type, int _pos = -1, QStringList _error_strings = {});

    friend uint qHash(const Error &item, uint seed);

    /*!
     * \brief Получить сообщение об ошибке известного типа
     * \return строка, содержащая сообщение об ошибке
    */
    QString getErrorMessageFor() const;

    /*!
     * \brief Метод для вывода информации об ошибке (для тестирования)
     * \return строка, содержащая информацию об объекте
     */
    QString toString() const;

    /*!
     * \brief Перегрузка оператора равенства для Error
     */
    bool operator==(const Error& other) const;
};

/*!
 * \brief Хэш-функция для класса Error
 */
uint qHash(const Error &item, uint seed = 0);

#endif // ERROR_H
