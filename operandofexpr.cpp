#include "nodeofexprtree.h"

/*!
 * \brief Перегрузка оператора больше для OperandOfExpr
 */
bool OperandOfExpr::operator>(const OperandOfExpr& other) const
{
    // Если сравниваются слагаемые
    if((parent != nullptr && (parent->type == PLUS || parent->type == BIN_MINUS))
        || (other.parent != nullptr && (other.parent->type == PLUS || other.parent->type == BIN_MINUS)))
    {
        // Получить результат сравнения слагаемых
        return !isCurrentOrderOfSummands(other);
    }
    // ИначеЕсли сравниваются множители
    else if((parent != nullptr && parent->type == MULTIPLICATION)
             || (other.parent != nullptr && other.parent->type == MULTIPLICATION))
    {
        // Получить список множителей
        return !isCurrentOrderOfMultipliers(other);
    }
    // ИначеЕсли сравниваются элементы с делителями
    else if((parent != nullptr && parent->type == DIVISION)
             || (other.parent != nullptr && other.parent->type == DIVISION))
    {
        if (parent != nullptr)
        {
            if (parent->type == DIVISION && (other.parent != nullptr && other.parent->type != DIVISION))
            {
                return true;
            }
        }
        else return false;
    }

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
    int missing_un_minuses_1 = operand->getNodeBySkippingUnaryMinus(&multiplier_1);

    // Получить второй множитель, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы
    NodeOfExprTree* multiplier_2 = nullptr;
    int missing_un_minuses_2 = other.operand->getNodeBySkippingUnaryMinus(&multiplier_2);

    // Определить, соблюдается ли порядок: сначала числа, потом переменные, далее - выражения в скобках
    if((multiplier_1->type == VAR && multiplier_2->type == NUM)
        || (isOperator(multiplier_1->value) && multiplier_2->type == VAR)
        || (isOperator(multiplier_1->value) && multiplier_2->type == NUM))
    {
        is_current_order = false;
    }
    // Если типы множителей одинаковые
    else if (multiplier_1->type == multiplier_2->type || (isOperator(multiplier_1->value) && isOperator(multiplier_2->value)))
    {
        // Определить, меньше ли первый множитель второго с учётом всех минусов, если их тип число
        if(multiplier_1->type == NUM)
        {
            bool is_negative_1 = missing_un_minuses_1 % 2 == 1;
            bool is_negative_2 = missing_un_minuses_2 % 2 == 1;

            if((is_negative_1 && is_negative_2 && multiplier_1->value < multiplier_2->value)
                ||  (!is_negative_1 && !is_negative_2 && multiplier_1->value > multiplier_2->value)
                || (!is_negative_1 && is_negative_2))
            {
                is_current_order = false;
            }
        }
        // Определить, меньше ли первый множитель второго, если их тип переменная
        else if(multiplier_1->type == VAR)
        {
            if(multiplier_1->value > multiplier_2->value) is_current_order = false;
        }
        // Определить правильность расстановки множителей, если они есть выражения в скобках
        else if (isOperator(multiplier_1->value))
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
    NodeOfExprTree* summand_1 = nullptr;
    int missing_un_minuses_1 = operand->getNodeBySkippingUnaryMinus(&summand_1);

    // Получить второе слагаемое, пропуская и посчитав все узлы, если они есть, типы которых унарные минусы
    NodeOfExprTree* summand_2 = nullptr;
    int missing_un_minuses_2 = other.operand->getNodeBySkippingUnaryMinus(&summand_2);

    // Получить список элементов каждого слагаемого
    QList<NodeOfExprTree*> elems_1 = summand_1->getLeavesOfTree();
    QList<NodeOfExprTree*> elems_2 = summand_2->getLeavesOfTree();

    // Определить, соблюдается ли порядок: сначала слагаемое с одинаковыми внутри себя именами переменных, потом - с различными, и вернуть результат, если порядок определился
    QList<NodeOfExprTree*> vars_1 = operand->getListOfVariableIDs(elems_1);
    QList<NodeOfExprTree*> vars_2 = other.operand->getListOfVariableIDs(elems_2);
    bool equal_vars_1 = areEqualVariableIDs(vars_1);
    bool equal_vars_2 = areEqualVariableIDs(vars_2);
    if(equal_vars_1 && !equal_vars_2)
    {
        return true;
    }
    else if (!equal_vars_1 && equal_vars_2)
    {
        return false;
    }

    // Получить степень каждого слагаемого
    int degree_of_summand_1 = summand_1->getDegreeOfExpr();
    int degree_of_summand_2 = summand_2->getDegreeOfExpr();
    // Определить, соблюдается ли порядок: сначала слагаемое с большей степенью переменных, и вернуть результат, если порядок определился
    if(degree_of_summand_1 > degree_of_summand_2)
    {
        return true;
    }
    if(degree_of_summand_1 < degree_of_summand_2)
    {
        return false;
    }


    // Определить, соблюдается ли порядок: по алфавиту, учитывая только имена переменные, и вернуть результат, если порядок определился
    int result = isCurentOrderOfListOfVariableIDs(vars_1, vars_2);
    if (result == 1 || result == 0)
    {
        return result;
    }

    // Определить, соблюдается ли порядок: от большего количества элементов слагаемого к меньшему, и вернуть результат, если порядок определился
    if(elems_1.size() > elems_2.size())
    {
        return true;
    }
    else if(elems_1.size() < elems_2.size())
    {
        return false;
    }

    // Определить, соблюдается ли порядок: от большего количества выражений в скобках в слагаемом к меньшему, и вернуть результат, если порядок определился
    int num_of_expr_in_parentheses_1 = summand_1->getNumOfParentheses();
    int num_of_expr_in_parentheses_2 = summand_2->getNumOfParentheses();
    if (num_of_expr_in_parentheses_1 > num_of_expr_in_parentheses_2)
    {
        return true;
    }
    else if (num_of_expr_in_parentheses_1 < num_of_expr_in_parentheses_2)
    {
        return false;
    }

    // Если слагаемые типа число
    if(summand_1->type == NUM && summand_2->type == NUM)
    {
        // Определить, соблюдается ли порядок: от большего числа к меньшему, и вернуть результат, если порядок определился
        bool is_negative_1 = (missing_un_minuses_1 + (parent->type == BIN_MINUS ? 1 : 0)) % 2 == 1;
        bool is_negative_2 = (missing_un_minuses_2 + (other.parent->type == BIN_MINUS ? 1 : 0)) % 2 == 1;

        if((is_negative_1 && is_negative_2 && summand_1->value < summand_2->value)
            ||  (!is_negative_1 && !is_negative_2 && summand_1->value > summand_2->value)
            || (!is_negative_1 && is_negative_2))
        {
            return true;
        }
        else if((is_negative_1 && is_negative_2 && summand_1->value > summand_2->value)
            ||  (!is_negative_1 && !is_negative_2 && summand_1->value < summand_2->value)
            || (is_negative_1 && !is_negative_2))
        {
            return false;
        }

    }

    // Вернуть, что порядок верный
    return true;
}

/*!
 * \brief Определить правильность расстановки двух выражений в скобках по алфавиту
 * \param [in] other - второй по порядку узел
 * \return true, если порядок верный, false - иначе
 */
bool OperandOfExpr::isCurrentOrderOfParenthesisedExpressions(const OperandOfExpr& other) const
{
    QList<OperandOfExpr> summands_1 = operand->getListOfNodesOfSamePrecedenceLevel();
    QList<OperandOfExpr> summands_2 = other.operand->getListOfNodesOfSamePrecedenceLevel();

    // Для каждой пары слагаемых выражений и повторять по минимальному кол-ву слагаемых из этих выражений
    int degree_of_current_summand_1 = 0;
    int degree_of_current_summand_2 = 0;
    int num_pairs = 0;
    summands_1.size() >= summands_2.size() ? num_pairs = summands_2.size() : num_pairs = summands_1.size();
    for(int i = 0; i < num_pairs; i++)
    {
        // Получить степень обоих слагаемых
        degree_of_current_summand_1 = summands_1[i].operand->getDegreeOfExpr();
        degree_of_current_summand_2 = summands_2[i].operand->getDegreeOfExpr();

        // Определить, соблюдается ли порядок: от большей степени переменной слагаемого к меньшей, и вернуть результат, если порядок определился
        if(degree_of_current_summand_1 > degree_of_current_summand_2)
            return true;
        else if (degree_of_current_summand_1 < degree_of_current_summand_2)
            return false;
    }

    // Получить списки элементов каждого выражения
    QList<NodeOfExprTree*> elems_1 = operand->getLeavesOfTree();
    QList<NodeOfExprTree*> elems_2 = other.operand->getLeavesOfTree();

    // Определить, соблюдается ли порядок: по алфавиту, учитывая только переменные
    QList<NodeOfExprTree*> vars_1 = operand->getListOfVariableIDs(elems_1);
    QList<NodeOfExprTree*> vars_2 = other.operand->getListOfVariableIDs(elems_2);
    int result = isCurentOrderOfListOfVariableIDs(vars_1, vars_2);

    // Вернуть результат, если порядок определился
    if (result == 1 || result == 0)
    {
        return result;
    }

    // Определить, соблюдается ли порядок: от большего количества переменных в выражении к меньшему, и вернуть результат, если порядок определился
    if(vars_1.size() > vars_2.size())
    {
        return true;
    }
    else if(vars_1.size() < vars_2.size())
    {
        return false;
    }

    // Определить, соблюдается ли порядок: от большего количества слагаемых к меньшему, и вернуть результат, если порядок определился
    if(summands_1.size() > summands_2.size())
    {
        return true;
    }
    else if(summands_1.size() < summands_2.size())
    {
        return false;
    }

    // Вернуть, что порядок верный
    return true;
}
