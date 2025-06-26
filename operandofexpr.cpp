#include "nodeofexprtree.h"

/*!
 * \brief Перегрузка оператора больше для OperandOfExpr
 */
bool OperandOfExpr::operator>(const OperandOfExpr& other) const
{
    return false;
}

/*!
 * \brief Определить правильность расстановки двух множителей по алфавиту
 * \param [in] other - второй по порядку элемент
 * \return true, если порядок верный, false - иначе
 */
bool OperandOfExpr::isCurrentOrderOfMultipliers(const OperandOfExpr& other) const
{
    bool is_current_order = true;
    // Получить первый множитель, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы
    NodeOfExprTree* multiplier_1 = nullptr;
    int missing_un_minuses_1 = operand->getNodeBySkippingUnaryMinus(multiplier_1);

    // Получить второй множитель, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы
    NodeOfExprTree* multiplier_2 = nullptr;
    int missing_un_minuses_2 = other.operand->getNodeBySkippingUnaryMinus(multiplier_2);

    // Определить, соблюдается ли порядок: сначала числа, потом переменные, далее - выражения в скобках
    if((operand->type == VAR && other.operand->type == NUM)
        || (isOperator(operand->value) && other.operand->type == VAR)
        || (isOperator(operand->value) && other.operand->type == NUM))
    {
        is_current_order = false;
    }
    // Если типы множителей одинаковые
    else if (operand->type == other.operand->type || (isOperator(operand->value) && isOperator(other.operand->value)))
    {
        // Определить, меньше ли первый множитель второго с учётом всех минусов, если их тип число
        if(operand->type == NUM)
        {
            bool is_negative_1 = missing_un_minuses_1 % 2 == 1;
            bool is_negative_2 = missing_un_minuses_2 % 2 == 1;

            if((is_negative_1 && is_negative_2 && operand->value < other.operand->value)
                ||  (!is_negative_1 && !is_negative_2 && operand->value > other.operand->value)
                || (!is_negative_1 && is_negative_2))
            {
                is_current_order = false;
            }
        }
        // Определить, меньше ли первый множитель второго, если их тип переменная
        else if(operand->type == VAR)
        {
            if(operand->value > other.operand->value) is_current_order = false;
        }
        // Определить правильность расстановки множителей, если они есть выражения в скобках
        else if (isOperator(operand->value) && isOperator(other.operand->value))
        {
            is_current_order = isCurrentOrderOfParenthesisedExpressions(other);
        }
    }

    // Вернуть получившийся результат
    return is_current_order;
}

/*!
 * \brief Определить правильность расстановки двух слагаемых по алфавиту
 * \param [in] other - второй по порядку элемент
 * \return true, если порядок верный, false - иначе
 */
bool OperandOfExpr::isCurrentOrderOfSummands(const OperandOfExpr& other) const
{
    // Получить первое слагаемое, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы
    // Получить второе слагаемое, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы

    // Получить список элементов каждого слагаемого

    // Определить, соблюдается ли порядок: сначала слагаемое с одинаковыми внутри себя именами переменных, потом - с различными
    // Вернуть результат, если порядок определился

    // Получить степень каждого слагаемого
    // Определить, соблюдается ли порядок: сначала слагаемое с большей степенью переменных
    // Вернуть результат, если порядок определился

    // Определить, соблюдается ли порядок: по алфавиту, учитывая только имена переменные
    // Вернуть результат, если порядок определился

    // Определить, соблюдается ли порядок: от большего количества элементов слагаемого к меньшему
    // Вернуть результат, если порядок определился

    // Определить, соблюдается ли порядок: от большего количества выражений в скобках в слагаемом к меньшему
    // Вернуть результат, если порядок определился

    // Если слагаемые типа число
    // Определить, соблюдается ли порядок: от большего числа к меньшему
    // Вернуть результат, если порядок определился

    // Вернуть, что порядок верный

    return false;
}

/*!
 * \brief Определить правильность расстановки двух выражений в скобках по алфавиту
 * \param [in] other - второй по порядку узел
 * \return true, если порядок верный, false - иначе
 */
bool OperandOfExpr::isCurrentOrderOfParenthesisedExpressions(const OperandOfExpr& other) const
{
    // Для каждой пары слагаемых выражений и повторять по минимальному кол-ву слагаемых из этих выражений
    {
        // Получить степень обоих слагаемых

        // Определить, соблюдается ли порядок: от большей степени переменной слагаемого к меньшей
        // Вернуть результат, если порядок определился
    }

    // Получить списки элементов каждого выражения
    // Определить, соблюдается ли порядок: по алфавиту, учитывая только переменные
    // Вернуть результат, если порядок определился

    // Определить, соблюдается ли порядок: от большего количества переменных в выражении к меньшему
    // Вернуть результат, если порядок определился

    // Определить, соблюдается ли порядок: от большего количества слагаемых к меньшему
    // Вернуть результат, если порядок определился

    // Вернуть, что порядок верный
    return false;
}
