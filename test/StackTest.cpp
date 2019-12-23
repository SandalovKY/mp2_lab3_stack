#include "TStack.h"
#include <gtest.h>

TEST(TStack, can_create_stack_with_positive_size)
{
	EXPECT_NO_THROW(TStack<int> s(5));
}

TEST(TStack, can_create_stack_with_zero_size)
{
	EXPECT_NO_THROW(TStack<int> s(0));
}

TEST(TStack, cant_create_stack_with_negative_size)
{
	EXPECT_ANY_THROW(TStack<int> s(-5));
}

TEST(TStack, can_create_stack_without_size)
{
	EXPECT_NO_THROW(TStack<int> s());
}

TEST(TStack, can_put_value_to_stack)
{
	TStack<int> s(5);
	EXPECT_NO_THROW(s.Put(5));
}

TEST(TStack, cant_put_value_if_stack_is_full)
{
	TStack<int> s(2);
	s.Put(1);
	s.Put(2);
	EXPECT_ANY_THROW(s.Put(3));
}

TEST(TStack, can_get_value_from_stack)
{
	TStack<int> s(5);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	EXPECT_NO_THROW(s.Get());
}

TEST(TStack, get_value_from_stack_right)
{
	TStack<int> s(5);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	EXPECT_EQ(s.Get(), 3);
}

TEST(TStack, cant_get_value_from_stack_with_zero_size)
{
	TStack<int> s(0);
	EXPECT_ANY_THROW(s.Get());
}

TEST(TStack, cant_get_value_from_empty_stack)
{
	TStack<int> s(5);
	EXPECT_ANY_THROW(s.Get());
}

TEST(TStack, can_know_top_element)
{
	TStack<int> s(5);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	EXPECT_NO_THROW(s.CheckLast());
}

TEST(TStack, cant_know_top_element_from_empty_stack)
{
	TStack<int> s(5);
	EXPECT_ANY_THROW(s.CheckLast());
}

TEST(TStack, cant_know_top_element_from_stack_with_zero_size)
{
	TStack<int> s(0);
	EXPECT_ANY_THROW(s.CheckLast());
}

TEST(TStack, top_element_give_right_value)
{
	TStack<int> s(5);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	EXPECT_EQ(s.CheckLast(), 3);
}

TEST(TStack, top_element_not_delete_value_from_stack)
{
	TStack<int> s(5);
	s.Put(1);
	s.Put(2);
	s.Put(3);
	s.CheckLast();
	EXPECT_EQ(s.Get(), 3);
}