#ifndef CMYSTACK_CMYSTACK_H
#define CMYSTACK_CMYSTACK_H

#include <stdexcept>

const std::string ERROR_STACK_IS_EMPTY = "Stack is empty";

template <typename T>

class CMyStack
{
public:

    CMyStack() = default;

    CMyStack(const CMyStack& other)
    {
        try
        {
            if (!other.IsEmpty())
            {
                Node* otherCurrent = other.m_top;
                Node* lastNewNode = nullptr;

                while (otherCurrent != nullptr)
                {
                    Node* newNode = new Node(otherCurrent->getData());

                    if (lastNewNode == nullptr)
                    {
                        m_top = newNode;
                    }
                    else
                    {
                        lastNewNode->setNext(newNode);
                    }

                    lastNewNode = newNode;
                    otherCurrent = otherCurrent->getNext();
                    m_size++;
                }
            }
        }
        catch (...)
        {
            Clear();
            throw;
        }
    }

    CMyStack& operator=(const CMyStack& other)
    {
        if (this != &other)
        {
            CMyStack temp(other);
            Swap(temp);
        }
        return *this;
    }

    CMyStack(CMyStack&& other) noexcept : m_top(other.m_top), m_size(other.m_size)
    {
        other.m_top = nullptr;
        other.m_size = 0;
    }

    CMyStack& operator=(CMyStack&& other) noexcept
    {
        if (this != &other)
        {
            Clear();
            m_top = other.m_top;
            m_size = other.m_size;

            other.m_top = nullptr;
            other.m_size = 0;
        }
        return *this;
    }

    ~CMyStack() noexcept
    {
        Clear();
    }

    void Push(const T& value)
    {
        Node* newNode = new Node(value, m_top);
        m_top = newNode;
        m_size++;
    }

    void Pop()
    {
        if (IsEmpty())
        {
            throw std::out_of_range(ERROR_STACK_IS_EMPTY);
        }

        Node* toDelete = m_top;
        m_top = m_top->getNext();
        delete toDelete;
        m_size--;
    }

    T& Top()
    {
        if (IsEmpty())
        {
            throw std::out_of_range(ERROR_STACK_IS_EMPTY);
        }
        return m_top->getData();
    }

    void Clear() noexcept
    {
        while (m_top != nullptr)
        {
            Node* toDelete = m_top;
            m_top = m_top->getNext();
            delete toDelete;
        }
        m_size = 0;
    }

    bool IsEmpty() const noexcept
    {
        return m_size == 0;
    }

    size_t GetSize() const noexcept
    {
        return m_size;
    }

    void Swap(CMyStack& other) noexcept
    {
        std::swap(m_top, other.m_top);
        std::swap(m_size, other.m_size);
    }

private:
    class Node
    {
    public:

        Node(const T& value, Node* nxt = nullptr) : data(value), next(nxt) {}

      /*  Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;*/

        T& getData()
        {
            return data;
        }
        const T& getData() const
        {
            return data;
        }

        Node* getNext() const
        {
            return next;
        }
        void setNext(Node* nxt)
        {
            next = nxt;
        }

    private:
    private:
        T data;
        Node* next;
    };

    Node* m_top = nullptr;
    size_t m_size = 0;
};


#endif //CMYSTACK_CMYSTACK_H
