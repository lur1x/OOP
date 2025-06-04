#include "gtest/gtest.h"
#include "CMyStack.h"

TEST(MyStackTest, DefaultConstructor)
{
    CMyStack<int> stack;
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.GetSize(), 0);
}


TEST(MyStackTest, PushAndTop)
{
    CMyStack<int> stack;
    stack.Push(10);
    EXPECT_FALSE(stack.IsEmpty());
    EXPECT_EQ(stack.GetSize(), 1);
    EXPECT_EQ(stack.Top(), 10);

    stack.Push(20);
    EXPECT_EQ(stack.GetSize(), 2);
    EXPECT_EQ(stack.Top(), 20);
}

TEST(MyStackTest, Pop)
{
    CMyStack<int> stack;
    stack.Push(10);
    stack.Push(20);

    stack.Pop();
    EXPECT_EQ(stack.GetSize(), 1);
    EXPECT_EQ(stack.Top(), 10);

    stack.Pop();
    EXPECT_TRUE(stack.IsEmpty());
}

TEST(MyStackTest, PopEmptyStack)
{
    CMyStack<int> stack;
    EXPECT_THROW(stack.Pop(), std::out_of_range);
}

TEST(MyStackTest, TopEmptyStack)
{
    CMyStack<int> stack;
    EXPECT_THROW(stack.Top(), std::out_of_range);
}

TEST(MyStackTest, Clear)
{
    CMyStack<int> stack;
    stack.Push(10);
    stack.Push(20);

    stack.Clear();
    EXPECT_TRUE(stack.IsEmpty());
    EXPECT_EQ(stack.GetSize(), 0);
    EXPECT_THROW(stack.Top(), std::out_of_range);
}

TEST(MyStackTest, CopyConstructor)
{
    CMyStack<int> original;
    original.Push(10);
    original.Push(20);

    CMyStack<int> copy(original);
    EXPECT_EQ(copy.GetSize(), 2);
    EXPECT_EQ(copy.Top(), 20);

    copy.Pop();
    EXPECT_EQ(copy.Top(), 10);
    EXPECT_EQ(original.Top(), 20);
}

TEST(MyStackTest, AssignmentOperator)
{
    CMyStack<int> original;
    original.Push(10);
    original.Push(20);

    CMyStack<int> copy;
    copy = original;
    EXPECT_EQ(copy.GetSize(), 2);
    EXPECT_EQ(copy.Top(), 20);

    copy.Pop();
    EXPECT_EQ(copy.Top(), 10);
    EXPECT_EQ(original.Top(), 20);
}

TEST(MyStackTest, SelfAssignment)
{
    CMyStack<int> stack;
    stack.Push(10);
    stack.Push(20);

    stack = stack;
    EXPECT_EQ(stack.GetSize(), 2);
    EXPECT_EQ(stack.Top(), 20);
}

TEST(MyStackTest, MoveConstructor)
{
    CMyStack<int> original;
    original.Push(10);
    original.Push(20);

    CMyStack<int> moved(std::move(original));
    EXPECT_EQ(moved.GetSize(), 2);
    EXPECT_EQ(moved.Top(), 20);
    EXPECT_TRUE(original.IsEmpty());
}

TEST(MyStackTest, MoveAssignment)
{
    CMyStack<int> original;
    original.Push(10);
    original.Push(20);

    CMyStack<int> moved;
    moved = std::move(original);
    EXPECT_EQ(moved.GetSize(), 2);
    EXPECT_EQ(moved.Top(), 20);
    EXPECT_TRUE(original.IsEmpty());
}

TEST(MyStackTest, Swap)
{
    CMyStack<int> stack1;
    stack1.Push(10);
    stack1.Push(20);

    CMyStack<int> stack2;
    stack2.Push(30);

    stack1.Swap(stack2);

    EXPECT_EQ(stack1.GetSize(), 1);
    EXPECT_EQ(stack1.Top(), 30);

    EXPECT_EQ(stack2.GetSize(), 2);
    EXPECT_EQ(stack2.Top(), 20);
}

TEST(MyStackTest, StringType)
{
    CMyStack<std::string> stack;
    stack.Push("hello");
    stack.Push("world");

    EXPECT_EQ(stack.GetSize(), 2);
    EXPECT_EQ(stack.Top(), "world");

    stack.Pop();
    EXPECT_EQ(stack.Top(), "hello");
}

TEST(MyStackTest, ExceptionSafety)
{
    CMyStack<int> original;
    original.Push(10);
    original.Push(20);

    try
    {
        throw std::runtime_error("test");
    }
    catch (...)
    {
        EXPECT_EQ(original.GetSize(), 2);
        EXPECT_EQ(original.Top(), 20);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}