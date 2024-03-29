#include <gtest/gtest.h>
#include "Stack.hpp"

TEST(stack, basic) {
    Stack<int> a;
    for (int i = 0; i < 12; ++i) {
        a.push(i);
    }
    std::stringstream ss;
    for (int i = 0; i < 12; ++i) {
        ss << a.top() << " ";
        a.pop();
    }
    ASSERT_EQ(ss.str(), "11 10 9 8 7 6 5 4 3 2 1 0 ");
}

TEST(stack, another_type) {
    Stack<std::string> a;
    a.push(std::string("hi!"));
    ASSERT_EQ(a.top(), "hi!");
}

TEST(stack, empty) {
    Stack<int> a;
    ASSERT_THROW(a.top(), std::logic_error);
}

TEST(stack, copy_assignment) {
    Stack<int> a;
    a.push(5);
    a.push(-2);
    Stack<int> b;
    b = a;
    std::stringstream ssa, ssb;
    ssa << a.top() << " ";
    ssb << b.top() << " ";
    a.pop();
    b.pop();
    ssa << a.top();
    ssb << b.top();
    ASSERT_EQ(ssa.str(), ssb.str());
}

TEST(stack, copy_constructor) {
    Stack<int> a;
    a.push(45);
    a.push(23);
    Stack<int> b(a);
    std::stringstream ssa, ssb;
    ssa << a.top() << " ";
    ssb << b.top() << " ";
    a.pop();
    b.pop();
    ssa << a.top();
    ssb << b.top();
    ASSERT_EQ(ssa.str(), ssb.str());
}

TEST(stack, move_assignment) {
    Stack<int> a;
    a.push(45);
    a.push(23);
    Stack<int> b = a;
    Stack<int> c;
    c = std::move(a);
    std::stringstream ssc, ssb;
    ssc << c.top() << " ";
    ssb << b.top() << " ";
    c.pop();
    b.pop();
    ssc << c.top();
    ssb << b.top();
    ASSERT_EQ(ssc.str(), ssb.str());
}

TEST(stack, move_constructor) {
    Stack<int> a;
    a.push(45);
    a.push(23);
    Stack<int> b = a;
    Stack<int> c (std::move(a));
    std::stringstream ssc, ssb;
    ssc << c.top() << " ";
    ssb << b.top() << " ";
    c.pop();
    b.pop();
    ssc << c.top();
    ssb << b.top();
    ASSERT_EQ(ssc.str(), ssb.str());
}

TEST(stack, copy_cons_empty) {
    Stack<double> a;
    Stack<double> b(a);
    ASSERT_THROW(b.top(), std::logic_error);
}

TEST(stack, copy_assig_empty) {
    Stack<char> a;
    Stack<char> b;
    b = a;
    ASSERT_THROW(b.top(), std::logic_error);
}

TEST(stack_node, copy_assignment) {
    StackNode<int> a1, a2;
    a1.data = 15;
    a1.next = &a2;
    StackNode<int> b;
    b = a1;
    ASSERT_EQ((b.data == a1.data) && (b.next == a1.next), true);
}

TEST(stack_node, move_assignment) {
    StackNode<int> a1, a2;
    a1.data = 99;
    a1.next = &a2;
    StackNode<int> b = a1;
    StackNode<int> c;
    c = std::move(a1);
    ASSERT_EQ((b.data == c.data) && (b.next == c.next), true);
}

TEST(stack_node, copy_constructor) {
    StackNode<int> a1, a2;
    a1.data = 15;
    a1.next = &a2;
    StackNode<int> b(a1);
    ASSERT_EQ((b.data == a1.data) && (b.next == a1.next), true);
}

TEST(stack_node, move_constructor) {
    StackNode<int> a1, a2;
    a1.data = 99;
    a1.next = &a2;
    StackNode<int> b = a1;
    StackNode<int> c (std::move(a1));
    ASSERT_EQ((b.data == c.data) && (b.next == c.next), true);
}

TEST(memcheck, copy_assignment) {
    Stack<int> a, b;
    a.push(98);
    a.push(97);
    a.push(96);
    b.push(95);
    b.push(94);
    b.push(93);
    a = b;
    // tested with command
    // leaks -atExit -- cmake-build-debug/my-stack/tests
}

