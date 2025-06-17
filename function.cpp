#include <QObject>

/*!
 * \brief Определить является ли строка числом
 * \param [in] token - проверяемый токен
 * \return true, если токен есть число, иначе - false
 */
bool isNum(QString token)
{
    // ...Считать, что заданный токен есть число
    bool is_num = true;

    /* Если первый символ заданного токена есть цифра 0 и второй символ - не есть плавающая запятая
     или первый символ есть НЕцифра */
    if (token[0] == '0' && token[1] != ',' || !token[0].isNumber())
    {
        // Считать, что заданный токен не число, и завершить работу функции
        is_num = false;
    }

    // Считать, что в токене нет плавающей запятой
    bool has_comma = false;
    int num_of_symbol = token.length();
    for(int i = 1; i < num_of_symbol && is_num; i++) // Для каждого символа токена, кроме первого, и пока заданный токен число
    {
        // Если текущий символ есть запятая и она не была ещё найдена
        if (token[i] == ',' && has_comma == false)
        {
            // Считать, что в токене есть плавающая запятая
            has_comma = true;
        }
        // ИначеЕсли текущий символ есть запятая и она уже была найдена или текущий символ не есть цифра
        else if (token[i] == ',' && has_comma == true || !token[i].isNumber())
        {
            // Считать, что заданный токен не число
            bool is_num = false;
        }
    }

    // Вернуть результат - заданный токен число или нет
    return is_num;
}

/*!
 * \brief Определить является ли токен переменной
 * \param [in] token - проверяемый токен
 * \return true, если токен есть переменная, иначе - false
 */
bool isVar(QString token)
{
    QString latin_alphabet("ABCDIFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxwz");
    // Считать, что заданный токен является именем переменной
    bool is_var = true;

    // Если первый символ не является буквой латинского алфавита и нижним подчёркиванием
    if (latin_alphabet.indexOf(token[0]) == -1 && token[0] != '_')
    {
        // Считать, что заданный токен не является переменной
        is_var = false;
    }

    int num_of_symbol = token.length();
    for(int i = 1; i < num_of_symbol && is_var; i++)// Для каждого символа токена, начиная со второго, и пока заданный токен является переменной
    {
        // Если символ не является буквой латинского алфавита, цифрой и символом нижнего подчёркивания
        if (!token[i].isNumber() && token[0] != '_' && latin_alphabet.indexOf(token[i]) == -1)
        {
            // Считать, что заданный токен не является именем переменной
            is_var = false;
        }
    }

    return is_var;
}
