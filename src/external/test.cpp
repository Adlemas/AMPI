#include "test.h"

Test::Test(int test1)
{
    this->test1 = test1;
}

int Test::GetTest()
{
    return this->test1;
}

void Test::SetTest(int value)
{
    this->test1 = value;
}