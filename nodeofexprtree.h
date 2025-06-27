/*!
 * \file
 * \brief Заголовочный файл для класса узла дерева NodeOfExprTree, струкруры OperandOfExpr и функций программы inequalityStandardizer
 */

#ifndef NODEOFEXPRTREE_H
#define NODEOFEXPRTREE_H
#include <QObject>
#include "error.h"
#include <QSet>
#include <QList>
#include <QStack>

class NodeOfExprTree;

/*!
 * \brief Перечисление типов узла
 */
enum OperatorType{
    UNDEFINED,              //!< Неопределённый тип
    UN_MINUS,               //!< Унарный минус
    MULTIPLICATION,         //!< Умножение
    DIVISION,               //!< Деление
    PLUS,                   //!< Плюс
    BIN_MINUS,              //!< Бинарный минус
    EQUAL,                  //!< Знак равенства
    NOT_EQUAL,              //!< Знак неравенства
    GREATER,                //!< Больше
    LESS,                   //!< Меньше
    GREATER_OR_EQUAL,       //!< Больше или равно
    LESS_OR_EQUAL,          //!< Меньше или равно
    NUM,                    //!< Число
    VAR                     //!< Переменная
};

/*!
 * \brief Структура для хранения информации об операнде
 */
struct OperandOfExpr
{
    NodeOfExprTree* parent;     //!< родитель операнда
    NodeOfExprTree* operand;    //!< операнд
    bool is_first_elem;         //!< флаг: true - операнд есть первый элемент выражения (нет знака перед собой), false - иначе

    /*!
     * \brief Определить правильность расстановки двух множителей по алфавиту
     * \param [in] other - второй по порядку узел
     * \return true, если порядок верный, false - иначе
     */
    bool isCurrentOrderOfMultipliers(const OperandOfExpr& other) const;

    /*!
     * \brief Определить правильность расстановки двух слагаемых по алфавиту
     * \param [in] other - второй по порядку элемент
     * \return true, если порядок верный, false - иначе
     */
    bool isCurrentOrderOfSummands(const OperandOfExpr& other) const;

    /*!
     * \brief Определить правильность расстановки двух выражений в скобках по алфавиту
     * \param [in] other - второй по порядку узел
     * \return true, если порядок верный, false - иначе
     */
    bool isCurrentOrderOfParenthesisedExpressions(const OperandOfExpr& other) const;

    /*!
     * \brief Перегрузка оператора больше для OperandOfExpr
     */
    bool operator>(const OperandOfExpr& other) const;
};

/*!
 * \brief Класс для хранения информации об узле дерева
 */
class NodeOfExprTree
{
private:
    OperatorType type;                 //!< тип узла
    QString value;                     //!< значение узла
    NodeOfExprTree* left_operand;      //!< левый операнд узла
    NodeOfExprTree* right_operand;     //!< правый операнд узла

public:

    /*!
     * \brief Конструктор по умолчанию для класса NodeOfExprTree
     */
    NodeOfExprTree();

    /*!
     * \brief Конструктор с параметрами для класса NodeOfExprTree
     */
    NodeOfExprTree(QString _value, NodeOfExprTree* _left_operand = nullptr, NodeOfExprTree* _right_operand = nullptr);

    friend struct OperandOfExpr;

    /*!
     * \brief Вернуть значение узла
     * \return значение узла
     */
    QString getValue() const { return value; }

    /*!
     * \brief Вернуть левый операнд
     * \return указатель на левый операнд
     */
    NodeOfExprTree* getLeftOperand() const { return left_operand; }

    /*!
     * \brief Вернуть правый операнд
     * \return указатель на правый операнд
     */
    NodeOfExprTree* getRightOperand() const { return right_operand; }

    /*!
     * \brief Установить левый операнд
     */
    void setLeftOperand(NodeOfExprTree* _left_operand) { left_operand = _left_operand; }

    /*!
     * \brief Установить правый операнд
     */
    void setRightOperand(NodeOfExprTree* _right_operand) { right_operand = _right_operand; }

    /*!
     * \brief Определить, является ли текущий оператор симметричным
     * \return результат
     */
    bool isSymmetricOperator() {return (type == MULTIPLICATION || type == PLUS); }

    /*!
     * \brief Вернуть приоритетность оператора
     * \return тип узла (0-5 в зависимости от приоритета), -1 - ошибка
     */
    int getPrecedenceType();

    /*!
     * \brief Получить строку значения узла для инфикной записи
     * \return строка для инфикной записи
     */
    QString valueToStr();

    /*!
     * \brief Перегрузка оператора равенства для NodeOfExprTree
     */
    bool operator==(const NodeOfExprTree& other) const;

    /*!
     * \brief Перегрузка оператора неравенства для NodeOfExprTree
     */
    bool operator!=(const NodeOfExprTree& other) const { return !(*this == other); };

    /*!
     * \brief Получить узел, пропустив все унарные минусы и посчитав их кол-во
     * \param [in,out] node - искомый узел
     * \return кол-во пропущенных унарных минусов
     */
    int getNodeBySkippingUnaryMinus(NodeOfExprTree** node);

    /*!
     * \brief Перестроить дерево (не)равенства, перенеся все слагаемые после знака сравнения в левую часть (не)равенства (до знака сравнения)
     */
    void rearrangeForZeroComparison();

    /*!
     * \brief Расставить все элементы в дереве выражения по алфавиту, начиная с заданного узла
     * \return указатель на корень отсортированного дерева
     */
    NodeOfExprTree* sortOperandsAlphabetically();

    /*!
     * \brief Получить список операндов, родители которых одного приоритета, начиная с заданного корня
     * \return список операндов
     */
    QList<OperandOfExpr> getListOfNodesOfSamePrecedenceLevel();

    /*!
     * \brief Получить список операндов, родители которых одного приоритета, начиная с заданного узла, раскрывая скобки
     * \param [in] is_invert - флаг: true - значение заданного узла необходимо поменять на противоположный операнд, false - иначе
     * \return список операндов
     */
    QList<OperandOfExpr> getNodesOfSamePrecedenceWithParenthesesOpening(bool is_invert = false);

    /*!
     * \brief Построить дерево выражения по элементам в списке
     * \param [in] list - список
     * \return указатель на корень дерева
     */
    NodeOfExprTree* listToTree(QList<OperandOfExpr>& list);

    /*!
     * \brief Получить список элементов сортировки в дереве, начиная с заданного узла
     * \return список элементов сортировки
     */
    QList<OperandOfExpr> getSortedList();

    /*!
     * \brief Получить инфиксную запись выражения из дерева этого выражения
     * \param [in] is_first_elem - флаг: true - указанный узел является первым операндом родителя, false - иначе
     * \return строка инфиксной записи выражения
     */
    QString treeToInfix(bool is_first_elem = true);

    /*!
     * \brief Получить степень выражения
     * \return степень выражения
     */
    int getDegreeOfExpr();

    /*!
     * \brief Удалить дерево
     * \param [in] root - корень дерева
     */
    static void delTree(NodeOfExprTree* root);

    /*!
     * \brief Получить список листьев дерева, корнем которого является заданный узел
     * \return список листьев дерева
     */
    QList<NodeOfExprTree*> getLeavesOfTree();

    /*!
     * \brief Получить список имён переменных из списка листов дерева
     * \param [in] leaves - список элементов
     * \return спосок переменных
     */
    QList<NodeOfExprTree*> getListOfVariableIDs(QList<NodeOfExprTree*> leaves);

    /*!
     * \brief Определить кол-во выражений в скобках в текущем выражении
     * \return кол-во выражений в скобках
     */
    int getNumOfParentheses();
};

/*!
 * \brief Из постфиксной записи выражения получить дерево этого выражения
 * \param [in] expr － строка выражения в постфиксной записи
 * \param [out] errors － обнаруженные ошибки в постфиксной записи
 * \return указатель на корень построенного дерева
 */
NodeOfExprTree* postfixToTree(QString expr, QSet<Error>& errors);

/*!
 * \brief Определить является ли строка числом
 * \param [in] token - проверяемый токен
 * \return true, если токен есть число, иначе - false
 */
bool isNum(QString token);

/*!
 * \brief Определить является ли токен переменной
 * \param [in] token - проверяемый токен
 * \return true, если токен есть переменная, иначе - false
 */
bool isVar(QString token);

/*!
 * \brief Определить является ли токен оператором
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isOperator(QString token);

/*!
 * \brief Определить является ли токен оператором сравнения
 * \param [in] token - проверяемый токен
 * \return true, если токен есть оператор, иначе - false
 */
bool isComparisonOperator(QString token);

/*!
 * \brief Удалить узлы стека
 * \param [in] stack - стек
 */
void clearStackNodes(QStack<NodeOfExprTree*>& stack);

/*!
 * \brief Запустить все тесты
 */
void runTests();

/*!
 * \brief Определить правильность расстановки двух списков имён переменных по алфавиту
 * \param [in] var_1 - первый список имён переменных
 * \param [in] var_2 - второй список имён переменных
 * \return 1 - порядок верный, 0 - порядок неверный, -1 - списки одинаковы или порядок определить невозможно
 */
int isCurentOrderOfListOfVariableIDs(QList<NodeOfExprTree*> vars_1, QList<NodeOfExprTree*> vars_2);

/*!
 * \brief Определить, равны ли имена переменные в списке
 * \param [in] var - список переменных
 * \return true, если в списке одинаковые имена переменных, falst - иначе
 */
bool areEqualVariableIDs(QList<NodeOfExprTree*> vars);

/*!
 * \brief Получить список операторов сравнения строки
 * \return список операторов сравнения
 */
QStringList getListOfComparisonOperator(QString expr);

#endif // NODEOFEXPRTREE_H
