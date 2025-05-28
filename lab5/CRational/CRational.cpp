#include "CRational.h"
#include <numeric>
#include <cmath>
#include <stdexcept>
#include <iostream>

CRational::CRational() : m_numerator(0), m_denominator(1)
{
}

CRational::CRational(const int value) : m_numerator(value), m_denominator(1)
{
}

CRational::CRational(const int numerator, const int denominator)
{
    if (denominator == 0)
    {
        throw std::invalid_argument(DENOMINATOR_CANNOT_ZERO);
    }
    else
    {
        m_numerator = numerator;
        m_denominator = denominator;
        Normalize();
    }
}

CRational CRational::Normalize()
{
    if (m_numerator == 0)
    {
        m_numerator = 0;
        m_denominator = 1;
        return *this;
    }

    int sign = 1;
    if (m_denominator < 0)
    {
        sign = -sign;
        m_denominator = -m_denominator;
        m_numerator = -m_numerator;
    }

    const int gcd = std::gcd(std::abs(m_numerator), std::abs(m_denominator));

    m_numerator /= gcd;
    m_denominator /= gcd;

    return *this;
}

int CRational::GetNumerator()const
{
    return m_numerator;
}

int CRational::GetDenominator() const
{
    return m_denominator;
}

double CRational::ToDouble() const
{
    double result =  static_cast<double>(GetNumerator())/GetDenominator();
    return result;
}

CRational CRational::operator+() const
{
    return *this;
}

CRational CRational::operator-() const
{
    return CRational(-m_numerator, m_denominator);
}

CRational CRational::operator+(const CRational& other) const
{
    CRational result =  CRational(GetNumerator() * other.GetDenominator() + other.GetNumerator() * GetDenominator(),
                                  GetDenominator() * other.GetDenominator());
    return result.Normalize();
}

CRational CRational::operator+(const int value) const
{
    return *this + CRational(value);
}

CRational operator+(const int value, const CRational& rational)
{
    return CRational(value) + rational;
}

CRational CRational::operator-(const CRational& other) const
{
    CRational result =  *this + (-other);
    return result.Normalize();
}

CRational CRational::operator-(const int value) const
{
    return *this - CRational(value);
}

CRational operator-(const int value, const CRational& rational)
{
    return CRational(value) - rational;
}

CRational& CRational::operator+=(const CRational& other)
{
    *this = *this + other;
    return *this;
}

CRational& CRational::operator+=(const int value)
{
    *this = *this + CRational(value);
    return *this;
}

CRational& CRational::operator-=(const CRational& other)
{
    *this = *this - other;
    return *this;
}

CRational& CRational::operator-=(const int value)
{
    *this = *this - CRational(value);
    return *this;
}

CRational CRational::operator*(const CRational& other) const
{
    CRational result =  CRational(GetNumerator() * other.GetNumerator(),
                                  GetDenominator() * other.GetDenominator());
    return result.Normalize();
}

CRational CRational::operator*(const int value) const
{
    return  *this * CRational(value);
}

CRational operator*(const int value, const CRational& rational)
{
    return CRational(value) * rational;
}

CRational CRational::operator/(const CRational& other) const
{
    if (other.GetNumerator() == 0)
    {
        throw std::invalid_argument(DIVISION_ZERO_DETECTED);
    }

    CRational result(GetNumerator() * other.GetDenominator(),
                     GetDenominator() * other.GetNumerator());

    return result.Normalize();
}

CRational CRational::operator/(const int value) const
{
    return  *this / CRational(value);
}

CRational operator/(const int value, const CRational& rational)
{
    return CRational(value) / rational;
}

CRational& CRational::operator*=(const CRational& other)
{
    *this = *this * other;
    return *this;
}


CRational& CRational::operator*=(const int value)
{
    *this = *this * CRational(value);
    return *this;
}

CRational& CRational::operator/=(const CRational& other)
{
    *this = *this / other;
    return *this;
}

CRational& CRational::operator/=(const int value)
{
    *this = *this / CRational(value);
    return *this;
}

bool operator==(const CRational& lhs, const CRational& rhs)
{
    return lhs.GetNumerator() == rhs.GetNumerator() &&
           lhs.GetDenominator() == rhs.GetDenominator();
}

bool operator==(const CRational& lhs, int rhs)
{
    return lhs == CRational(rhs);
}

bool operator==(int lhs, const CRational& rhs)
{
    return CRational(lhs) == rhs;
}

bool operator!=(const CRational& lhs, const CRational& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const CRational& lhs, int rhs)
{
    return lhs != CRational(rhs);
}

bool operator!=(int lhs, const CRational& rhs)
{
    return CRational(lhs) != rhs;
}

bool CRational::operator<(const CRational& other) const
{
    return GetNumerator()* other.GetDenominator() < other.GetNumerator() * GetDenominator();
}

bool operator<(const CRational& lhs, int rhs)
{
    return lhs < CRational(rhs);
}

bool operator<(int lhs, const CRational& rhs)
{
    return CRational(lhs) < rhs;
}

bool CRational::operator<=(const CRational& other) const
{
    return *this < other || *this == other;
}

bool operator<=(const CRational& lhs, int rhs)
{
    return lhs <= CRational(rhs);
}

bool operator<=(int lhs, const CRational& rhs)
{
    return CRational(lhs) <= rhs;
}

bool CRational::operator>(const CRational& other) const
{
    return !(*this <= other);
}

bool operator>(const CRational& lhs, int rhs)
{
    return lhs > CRational(rhs);
}

bool operator>(int lhs, const CRational& rhs)
{
    return CRational(lhs) > rhs;
}

bool CRational::operator>=(const CRational& other) const
{
    return !(*this < other);
}
bool operator>=(const CRational& lhs, int rhs)
{
    return lhs >= CRational(rhs);
}

bool operator>=(int lhs, const CRational& rhs)
{
    return CRational(lhs) >= rhs;
}

std::ostream& operator<<(std::ostream& os, const CRational& rational)
{
    os << rational.GetNumerator() << "/" << rational.GetDenominator();
    return os;
}

std::istream& operator>>(std::istream& is, CRational& rational)
{
    int num;
    char sep;

    if (is >> num)
    {
        if (is.peek() == SEP)
        {
            is >> sep;
            int denom;
            if (is >> denom)
            {
                rational = CRational(num, denom);
            }
            else
            {
                is.setstate(std::ios::failbit);
            }
        }
        else
        {
            rational = CRational(num);
        }
    }
    else
    {
        is.setstate(std::ios::failbit);
    }

    return is;
}
