/*
** EPITECH PROJECT, 2024
** Template
** File description:
** Tests_NumericalParsers
*/

#include "Library.hpp"

#include <gtest/gtest.h>

TEST(NumericalParsersTests_IsIntegerNumber, BasicAssertions)
{
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(""), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(" \t"), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber("a"), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber("+-"), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber("1"), true);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber("1 "), true);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(" 1"), true);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(" 1 "), true);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(" 1\t"), true);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(" 1\t "), true);
    EXPECT_EQ(Library::Utils::NumericalParsers::IsIntegerNumber(" 1\t a"), false);
}

TEST(NumericalParsersTests_ParseInt, BasicAssertions)
{
    int value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseInt(" 1\t 2", value), false);
}

TEST(NumericalParsersTests_ParseLong, BasicAssertions)
{
    long value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLong(" 1\t 2", value), false);
}
TEST(NumericalParsersTests_ParseUnsignedLong, BasicAssertions)
{
    unsigned long value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLong(" 1\t 2", value), false);
}
TEST(NumericalParsersTests_ParseLongLong, BasicAssertions)
{
    long long value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseLongLong(" 1\t 2", value), false);
}
TEST(NumericalParsersTests_ParseUnsignedLongLong, BasicAssertions)
{
    unsigned long long value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedLongLong(" 1\t 2", value), false);
}
TEST(NumericalParsersTests_ParseShort, BasicAssertions)
{
    short value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseShort(" 1\t 2", value), false);
}
TEST(NumericalParsersTests_ParseUnsignedShort, BasicAssertions)
{
    unsigned short value = 0;

    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort("", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" \t", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort("a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort("+-", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort("1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort("1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" 1", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" 1 ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" 1\t", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" 1\t ", value), true);
    EXPECT_EQ(value, 1);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" 1\t a", value), false);
    EXPECT_EQ(Library::Utils::NumericalParsers::ParseUnsignedShort(" 1\t 2", value), false);
}