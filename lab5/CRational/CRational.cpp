#include "CRational.h"

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
        throw 
    }
}