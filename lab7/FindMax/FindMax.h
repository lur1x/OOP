#ifndef FINDMAX_FINDMAX_H
#define FINDMAX_FINDMAX_H

#include <vector>
#include <algorithm>
#include <cstring>

template <typename T>

bool FindMax(std::vector<T> const& arr, T& maxValue)
{
    if (arr.empty())
    {
        return false;
    }

    maxValue = *std::max_element(arr.begin(), arr.end());

    return true;
}

template <>
bool FindMax<const char *>(std::vector<const char*> const& arr,
                           const char*& maxValue)
{
    if (arr.empty())
    {
        return false;
    }

    maxValue = arr[0];
    for (const char* str : arr)
    {
        if (std::strcmp(str, maxValue) > 0)
        {
            maxValue = str;
        }
    }
    return true;
}

#endif //FINDMAX_FINDMAX_H
