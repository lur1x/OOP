#ifndef CRATIONAL_CRATIONAL_H
#define CRATIONAL_CRATIONAL_H

class CRational
{
public:
    // Конструирует рациональное число, равное нулю (0/1)
    CRational();

    // Конструирует рациональное число, равное value (value/1)
    CRational(const int value);

    // Конструирует рациональное число, равное numerator/denominator
    // Рациональное число должно храниться в нормализованном виде:
    // знаменатель положительный (числитель может быть отрицательным)
    // числитель и знаменатель не имеют общих делителей (6/8 => 3/4 и т.п.)
    // Если знаменатель равен нулю, должно конструироваться рациональное число, равное нулю,
    // либо должно быть выброшено исключение std::invalid_argument.
    CRational(const int numerator, const int denominator);

    // Возвращает числитель
    int GetNumerator() const;

    // Возвращает знаменатель (натуральное число)
    int GetDenominator() const;

    // Возвращает отношение числителя и знаменателя в виде числа double
    double ToDouble() const;

    // Прочие операторы согласно заданию
private:
    int m_numerator;
    int m_denominator;
};


#endif //CRATIONAL_CRATIONAL_H
