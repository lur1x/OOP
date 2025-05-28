#ifndef CRATIONAL_CRATIONAL_H
#define CRATIONAL_CRATIONAL_H

#include "Constants.h";

class CRational
{
public:
    CRational();
    CRational(const int value);
    CRational(const int numerator, const int denominator);

    int GetNumerator() const;
    int GetDenominator() const;

    double ToDouble() const;

    CRational operator+() const;
    CRational operator-() const;

    CRational operator+(const CRational& other) const;
    CRational operator+(const int value) const;
    friend CRational operator+(const int value, const CRational& rational);

    CRational operator-(const CRational& other) const;
    CRational operator-(const int value) const;
    friend CRational operator-(const int value, const CRational& rational);

    CRational& operator+=(const CRational& other);
    CRational& operator+=(const int value);

    CRational& operator-=(const CRational& other);
    CRational& operator-=(const int value);

    CRational operator*(const CRational& other) const;
    CRational operator*(const int value) const;
    friend CRational operator*(const int value, const CRational& rational);

    CRational operator/(const CRational& other) const;
    CRational operator/(const int value) const;
    friend CRational operator/(const int value, const CRational& rational);

    CRational& operator*=(const CRational& other);
    CRational& operator*=(const int value);

    CRational& operator/=(const CRational& other);
    CRational& operator/=(const int value);


    friend bool operator==(const CRational& lhs, const CRational& rhs);
    friend bool operator==(const CRational& lhs, int rhs);
    friend bool operator==(int lhs, const CRational& rhs);

    friend bool operator!=(const CRational& lhs, const CRational& rhs);
    friend bool operator!=(const CRational& lhs, int rhs);
    friend bool operator!=(int lhs, const CRational& rhs);

    bool operator<(const CRational& other) const;
    friend bool operator<(const CRational& lhs, int rhs);
    friend bool operator<(int lhs, const CRational& rhs);

    bool operator<=(const CRational& other) const;
    friend bool operator<=(const CRational& lhs, int rhs);
    friend bool operator<=(int lhs, const CRational& rhs);

    bool operator>(const CRational& other) const;
    friend bool operator>(const CRational& lhs, int rhs);
    friend bool operator>(int lhs, const CRational& rhs);

    bool operator>=(const CRational& other) const;
    friend bool operator>=(const CRational& lhs, int rhs);
    friend bool operator>=(int lhs, const CRational& rhs);

    friend std::ostream& operator<<(std::ostream& os, const CRational& rational);
    friend std::istream& operator>>(std::istream& is, CRational& rational);

private:
    int m_numerator;
    int m_denominator;

    CRational Normalize();
};

#endif //CRATIONAL_CRATIONAL_H
