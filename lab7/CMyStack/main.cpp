#include <iostream>
#include "CMyStack.h"

int main()
{
    CMyStack<int> intStack;

    for (int i = 1; i <= 5; ++i)
    {
        intStack.Push(i);
        std::cout << "Pushed: " << i << ", Top: " << intStack.Top() << "\n";
    }

    while (!intStack.IsEmpty())
    {
        std::cout << "Top: " << intStack.Top() << ", Size: " << intStack.GetSize() << "\n";
        intStack.Pop();
    }

    CMyStack<std::string> stringStack;
    stringStack.Push("First");
    stringStack.Push("Second");

    CMyStack<std::string> copiedStack = stringStack;
    std::cout << "Copied stack contents:\n";
    while (!copiedStack.IsEmpty())
    {
        std::cout << copiedStack.Top() << "\n";
        copiedStack.Pop();
    }

    return 0;
}